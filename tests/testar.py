"""Testes de terminal. Execute: python tests/testar.py caminho_do_executavel"""
import re
import subprocess
import sys
from pathlib import Path

EXECUTAVEL = str(Path(sys.argv[1]).resolve()) if len(sys.argv) > 1 else ''
if not EXECUTAVEL:
    raise SystemExit('Uso: python tests/testar.py caminho_do_executavel')
TOTAL = 0

def rodar(linhas):
    resultado = subprocess.run([EXECUTAVEL], input='\n'.join(map(str, linhas)) + '\n',
                               text=True, capture_output=True, timeout=10)
    assert resultado.returncode == 0, resultado.stderr
    assert not resultado.stderr, resultado.stderr
    return resultado.stdout

def cadastrar(numero, saldo=0, nome='Cliente Teste', cpf='00000000000', tipo=1):
    return [1, numero, nome, cpf, tipo, saldo]

def verificar(nome, linhas, presentes=(), ausentes=(), saldos=None):
    global TOTAL
    saida = rodar(linhas)
    for texto in presentes:
        assert texto in saida, (nome, texto, saida[-3000:])
    for texto in ausentes:
        assert texto not in saida, (nome, texto)
    if saldos is not None:
        encontrados = re.findall(r'Saldo atual: R\$ ([0-9]+\.[0-9]{2})', saida)
        assert encontrados == saldos, (nome, encontrados, saldos)
    TOTAL += 1
    print(f'OK {TOTAL:02d} - {nome}')
    return saida

base = cadastrar(1001, 1000, 'Ana') + cadastrar(1002, 500, 'Bruno', tipo=2)
verificar('Menu sem contas', [2,3,4,5,6,7,8,9,10,0], ['Nenhuma conta cadastrada.'])
verificar('Cadastro, listagem e consulta', base+[2,3,1001,3,1002,0],
          ['Total de contas: 2','Titular: Ana','Titular: Bruno','Tipo: Poupanca'], saldos=['1000.00','500.00'])
verificar('Transferencia do exemplo do PDF', base+[6,1001,1002,300,7,1001,7,1002,0],
          ['1 | S | R$ 300.00','1 | D | R$ 300.00'], saldos=['700.00','700.00','800.00'])
verificar('Deposito, saque e extrato', cadastrar(1)+[4,1,100.50,5,1,40.25,7,1,0],
          ['1 | D | R$ 100.50','2 | S | R$ 40.25','Total de movimentacoes da conta: 2'],
          saldos=['100.50','60.25','60.25'])
verificar('Saque e transferencia sem saldo', base+[5,1001,1000.01,6,1001,1002,1001,7,1001,7,1002,0],
          ['Saldo insuficiente.','Nenhuma movimentacao nesta conta.'], saldos=['1000.00','500.00'])
verificar('Busca de contas inexistentes', base+[3,999,4,999,5,999,6,999,6,1001,999,7,999,0],
          ['Conta nao encontrada.','Conta de destino nao encontrada.'], saldos=[])
verificar('Transferencia para a mesma conta', base+[6,1001,1001,7,1001,0],
          ['Escolha duas contas diferentes.','Nenhuma movimentacao nesta conta.'], saldos=['1000.00'])
verificar('Conta inativa bloqueia operacoes', base+[10,1001,4,1001,5,1001,6,1001,7,1001,8,1001,9,1001,3,1001,10,1001,8,1001,0],
          ['Conta inativa.','Saldo indisponivel:','Conta ativada.'], saldos=['1000.00'])
verificar('Destino inativo e preservacao dos saldos', base+[10,1002,6,1001,1002,10,1002,8,1001,8,1002,0],
          ['Conta de destino inativa.'], saldos=['1000.00','500.00'])
verificar('Alteracao de tipo independente', base+[9,1001,2,3,1001,9,1002,1,3,1002,0],
          ['Tipo: Poupanca','Tipo: Corrente'], saldos=['1000.00','500.00'])
verificar('Validacoes no cadastro', [1,0,-2,'abc','1.5','1abc',1,'','   ','Maria Silva','123','abcdefghijk','01234567890',3,'2x',2,-1,'nan','inf','1e309','12.345','1,50',12.34,3,1,0],
          ['Numero invalido','O nome nao pode ficar vazio','Informe exatamente 11','Tipo invalido','Saldo invalido','CPF: 01234567890'], saldos=['12.34'])
verificar('Conta duplicada e mesmo CPF permitido', cadastrar(1)+[1,1,2,'Outro Titular','00000000000',1,0,2,0],
          ['Numero invalido ou ja cadastrado.','Total de contas: 2'])
verificar('Menu e busca invalidos recuperam', cadastrar(1)+['abc','1.2','3abc',11,-1,8,'abc',0,'1x',1,0],
          ['Opcao invalida.','Informe um numero inteiro positivo.'], saldos=['0.00'])
verificar('Valores invalidos nao geram registros', cadastrar(1)+[4,1,0,-1,'abc','nan','inf','1e309','0.001','0.00000001','1,25','2x',1.25,7,1,0],
          ['Valor invalido.','Total de movimentacoes da conta: 1'], saldos=['1.25','1.25'])
verificar('Aritmetica de centavos e saque integral', cadastrar(1,0.30)+[5,1,0.10,5,1,0.20,8,1,0], saldos=['0.20','0.00','0.00'])
verificar('Limite de saldo sem alteracao parcial', cadastrar(1,1000000000)+cadastrar(2,100)+[4,1,0.01,6,2,1,1,7,1,7,2,0],
          ['Limite de saldo excedido.','Nenhuma movimentacao nesta conta.'], saldos=['1000000000.00','100.00'])
cem = sum((cadastrar(i) for i in range(1,101)), [])
verificar('100 contas e recusa da 101a', cem+[1,2,3,100,0], ['Limite de 100 contas atingido.','Total de contas: 100','Numero: 100'], saldos=['0.00'])
cheio = cadastrar(1)+[4,1,1]*500
saida = verificar('500 registros e bloqueio de deposito e saque', cheio+[4,1,5,1,7,1,0],
          ['Historico sem espaco.','Total de movimentacoes da conta: 500','500 | D | R$ 1.00'])
assert re.findall(r'Saldo atual: R\$ ([0-9.]+)', saida)[-1] == '500.00'
quase = cadastrar(1,1000)+cadastrar(2)+[4,1,1]*499
saida = verificar('Uma vaga nao permite transferencia e aceita deposito', quase+[6,1,2,7,1,7,2,4,2,1,7,2,0],
          ['Historico sem espaco.','Total de movimentacoes da conta: 499','Total de movimentacoes da conta: 1'],
          ['Transferencia realizada com sucesso.'])
assert re.findall(r'Saldo atual: R\$ ([0-9.]+)', saida)[-4:] == ['1499.00','0.00','1.00','1.00']
saida = verificar('Duas vagas permitem transferencia completa', cadastrar(1,1000)+cadastrar(2)+[4,1,1]*498+[6,1,2,300,4,2,7,1,7,2,0],
          ['Transferencia realizada com sucesso.','Historico sem espaco.','499 | S | R$ 300.00','1 | D | R$ 300.00'])
assert re.findall(r'Saldo atual: R\$ ([0-9.]+)', saida)[-3:] == ['1198.00','1198.00','300.00']
saida = verificar('Extratos filtram a conta e mantem a ordem', base+[4,1001,10,4,1002,20,6,1001,1002,30,7,1001,7,1002,0])
ana = saida.split('--- EXTRATO DA CONTA 1001 ---')[1].split('========================================')[0]
bruno = saida.split('--- EXTRATO DA CONTA 1002 ---')[1].split('========================================')[0]
assert '1 | D | R$ 10.00' in ana and '2 | S | R$ 30.00' in ana and 'R$ 20.00' not in ana
assert '1 | D | R$ 20.00' in bruno and '2 | D | R$ 30.00' in bruno and 'R$ 10.00' not in bruno
for nome, dados in [('EOF no menu', []),('EOF no cadastro',[1,1,'Ana']),('EOF na transferencia',base+[6,1001,1002]),('EOF no valor',base+[4,1001])]:
    verificar(nome, dados, ausentes=['Transferencia realizada com sucesso.','Deposito realizado com sucesso.'])
verificar('Nova execucao inicia sem dados', [2,0], ['Nenhuma conta cadastrada.'])
print(f'\n{TOTAL} cenarios aprovados.')
