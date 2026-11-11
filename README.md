# Banco Horizonte — Etapa 2

Sistema de Registro e Gestão de Contas Bancárias, desenvolvido em C++ para **INF101 — Programação de Computadores I**, do **Centro Universitário de Viçosa — UNIVIÇOSA**.

- **Aluna:** Luisa Dias Sampaio Sumam Silva.
- **Professores:** Anderson R. Lamas e Vanderlea Queiroz.
- **Entrega prevista:** 11/11/2026; demonstração no laboratório nessa data ou, conforme o enunciado, em 04/11/2026.
- **Primeira etapa:** [Banco-Horizonte-INF101](https://github.com/luhsampaio39-sudo/Banco-Horizonte-INF101).

Esta é a continuação da primeira etapa em um projeto separado. A identificação Banco Horizonte, os campos cadastrais, a validação das entradas e as operações de gestão foram mantidos. Os conjuntos de variáveis individuais foram substituídos por arrays, com capacidade para 100 contas, e foi incluído um histórico de 500 movimentações.

## Arquivos

| Arquivo | Finalidade |
|---|---|
| `banco_horizonte.cpp` | Programa completo da segunda etapa, com um único `main()` |
| `docs/EXPLICACAO.md` | Explicação dos arrays, regras e decisões do projeto |
| `docs/APRESENTACAO.md` | Roteiro de demonstração para o laboratório |
| `docs/TESTES.md` | Comando de teste e resultados efetivamente obtidos |
| `tests/testar.py` | Testes automatizados opcionais, externos ao programa C++ |

## Compilar e executar

Use um compilador com suporte a C++11 ou superior. O programa usa apenas a biblioteca padrão. Em uma IDE, crie um projeto de console C++ e adicione **somente `banco_horizonte.cpp`** como arquivo-fonte.

Windows, com GCC/MinGW disponível no terminal:

```powershell
g++ -std=c++11 -Wall -Wextra -Wpedantic banco_horizonte.cpp -o banco_horizonte.exe
.\banco_horizonte.exe
```

Linux, com GCC instalado:

```bash
g++ -std=c++11 -Wall -Wextra -Wpedantic banco_horizonte.cpp -o banco_horizonte
./banco_horizonte
```

O Python só é necessário para executar os testes opcionais; não é necessário para usar o banco. Use ponto nos valores monetários: `150.50`.

## Menu

| Opção | Operação |
|---|---|
| 1 | Cadastrar conta |
| 2 | Listar todas as contas cadastradas |
| 3 | Consultar uma conta pelo número |
| 4 | Depositar |
| 5 | Sacar |
| 6 | Transferir entre duas contas |
| 7 | Exibir extrato |
| 8 | Verificar saldo — continuidade da Etapa 1 |
| 9 | Alterar tipo — continuidade da Etapa 1 |
| 10 | Ativar/desativar — continuidade da Etapa 1 |
| 0 | Sair |

As sete primeiras opções correspondem às funcionalidades obrigatórias do PDF. O número de saída mudou de 6 para 0, pois a opção 6 agora realiza transferências.

## Regras

- Número da conta: inteiro positivo e único; a busca usa o número, não a posição no array.
- Nome: não pode estar vazio ou conter somente espaços/tabulações.
- CPF: texto com exatamente 11 algarismos. A validação verifica o formato, não os dígitos verificadores. O mesmo CPF pode ter mais de uma conta.
- Tipo: 1 = corrente; 2 = poupança. Toda nova conta começa ativa.
- Valores em reais com precisão de centavos; saldo inicial pode ser zero, movimentações devem ser de pelo menos R$ 0,01.
- Para manter os cálculos com `double` em uma faixa controlada, cada saldo e valor informado é limitado a R$ 1.000.000.000,00. Esse é um limite técnico adicional do projeto, não uma exigência do PDF.
- Depósitos, saques, transferências, saldo, extrato e alteração de tipo exigem conta ativa. Ambas as contas de uma transferência precisam estar ativas e ser diferentes.
- A consulta cadastral, listagem e ativação/desativação continuam disponíveis para contas inativas. O saldo fica oculto na consulta cadastral de conta inativa, preservando a regra da Etapa 1.
- Desativar uma conta preserva saldo, cadastro e histórico, e não libera posição no array.
- O saldo inicial é apresentado separadamente no extrato. Ele não consome uma movimentação: os registros são gerados pelos depósitos, saques e transferências realizados após o cadastro.
- Saques e transferências não podem ultrapassar o saldo de origem.
- Depósito registra `D`; saque registra `S`; transferência registra `S` na origem e `D` no destino, conforme o exemplo da seção 2.5 do PDF. Os valores gravados são positivos; o código indica a direção.
- A capacidade do histórico é global: 500 registros somando todas as contas. Transferências consomem dois. Quando falta espaço, a operação inteira é recusada antes de alterar saldos.
- O extrato mostra somente os registros da conta consultada, na ordem de realização, com saldo inicial e saldo atual.

**Os dados existem somente em memória. Ao fechar o programa, são perdidos. Não há arquivos de contas, autenticação nem integração com bancos reais. A persistência fica para a Etapa 3.**

## Verificação

Compilação verificada com `-std=c++11 -Wall -Wextra -Wpedantic -Werror`, sem avisos. Os 26 cenários automatizados passaram. Veja [TESTES](docs/TESTES.md).

Antes da entrega, execute o programa também no computador do laboratório e estude o [roteiro de apresentação](docs/APRESENTACAO.md).
