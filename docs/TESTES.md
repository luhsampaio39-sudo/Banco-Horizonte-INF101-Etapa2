# Testes executados

Verificação realizada em 28/10/2026, no ambiente Linux desta preparação. A execução no computador do laboratório ainda deve ser conferida pela aluna.

## Compilação

```bash
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror banco_horizonte.cpp -o banco_horizonte
```

Resultado: compilação concluída com sucesso, sem avisos nem erros.

## Testes automatizados

```bash
python3 tests/testar.py ./banco_horizonte
```

No Windows, use `python tests/testar.py ./banco_horizonte.exe` após compilar.

Os testes enviam entradas ao programa compilado e verificam respostas, saldos, extratos e recusas. O Python não faz parte da implementação bancária.

## Resultado

```text
OK 01 - Menu sem contas
OK 02 - Cadastro, listagem e consulta
OK 03 - Transferencia do exemplo do PDF
OK 04 - Deposito, saque e extrato
OK 05 - Saque e transferencia sem saldo
OK 06 - Busca de contas inexistentes
OK 07 - Transferencia para a mesma conta
OK 08 - Conta inativa bloqueia operacoes
OK 09 - Destino inativo e preservacao dos saldos
OK 10 - Alteracao de tipo independente
OK 11 - Validacoes no cadastro
OK 12 - Conta duplicada e mesmo CPF permitido
OK 13 - Menu e busca invalidos recuperam
OK 14 - Valores invalidos nao geram registros
OK 15 - Aritmetica de centavos e saque integral
OK 16 - Limite de saldo sem alteracao parcial
OK 17 - 100 contas e recusa da 101a
OK 18 - 500 registros e bloqueio de deposito e saque
OK 19 - Uma vaga nao permite transferencia e aceita deposito
OK 20 - Duas vagas permitem transferencia completa
OK 21 - Extratos filtram a conta e mantem a ordem
OK 22 - EOF no menu
OK 23 - EOF no cadastro
OK 24 - EOF na transferencia
OK 25 - EOF no valor
OK 26 - Nova execucao inicia sem dados

26 cenarios aprovados.
```

## Correspondência com o enunciado

| Exigência | Implementação / verificação |
|---|---|
| Até 100 contas com os seis arrays especificados | Declarações no início do main; cenário 17 |
| Até 500 movimentações com os três arrays especificados | Declarações no início do main; cenários 18 a 20 |
| Cadastrar, listar e consultar pelo número | Opções 1, 2 e 3; cenários 02, 06, 11 e 12 |
| Depósito e saque com registro e saldo suficiente | Opções 4 e 5; cenários 04, 05 e 14 |
| Transferência entre contas existentes e ativas | Opção 6; cenários 03, 06 a 09 |
| Valor positivo e saldo suficiente | Validação antes da alteração; cenários 05 e 14 |
| Dois registros e espaço para ambos | S na origem, D no destino; cenários 19 e 20 |
| Extrato filtrado por conta | Opção 7; cenário 21 |
| Dados somente em memória | Sem gravação de contas em arquivos; cenário 26 |
| Funções próprias opcionais | Operações organizadas diretamente no main |

Os cenários 22 a 25 verificam encerramento da entrada em pontos diferentes, sem efetivar uma movimentação incompleta. A aprovação dos testes documenta os casos executados; não substitui a demonstração nem assegura uma nota.
