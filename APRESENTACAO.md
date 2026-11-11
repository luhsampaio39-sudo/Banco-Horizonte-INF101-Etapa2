# Roteiro para apresentar no laboratório

Compile `banco_horizonte.cpp` e execute. Os CPFs deste roteiro são fictícios, usados apenas para testar o formato.

## Demonstração principal

1. Escolha 2 antes de cadastrar: o programa informa que não há contas.
2. Escolha 1 e cadastre número **1001**, nome **Ana**, CPF **00000000000**, tipo **1**, saldo inicial **1000**.
3. Escolha 1 e cadastre número **1002**, nome **Bruno**, CPF **11111111111**, tipo **2**, saldo inicial **500**.
4. Escolha 2: mostre as duas contas. Explique que elas ocupam índices 0 e 1, apesar de seus números serem 1001 e 1002.
5. Escolha 3 e informe 1001: confira os dados.
6. Escolha 6, origem 1001, destino 1002 e valor 300. Esse é o exemplo do PDF.
7. Escolha 7 para 1001: saldo inicial 1000, registro S de 300, saldo atual **700**.
8. Escolha 7 para 1002: saldo inicial 500, registro D de 300, saldo atual **800**.
9. Escolha 4, conta 1001, valor 50. O saldo passa a **750**.
10. Escolha 5, conta 1002, valor 100. O saldo passa a **700**.
11. Escolha 5, conta 1001, valor 9999: o saque é recusado. Consulte o extrato e mostre que não foi criado registro da tentativa.
12. Escolha 10 para desativar 1002. Tente transferir de 1001 para 1002; o destino inativo é recusado antes de pedir o valor.
13. Escolha 10 para reativar 1002. Consulte e mostre que os dados foram preservados.
14. Escolha 9 para mudar o tipo de 1001 para 2. Consulte para conferir.
15. Escolha 0 para sair. Abra o programa novamente e liste as contas: os dados não persistem, como exige esta etapa.

## Perguntas que você precisa saber explicar

**O que conecta os dados de uma conta?** O mesmo índice nos arrays paralelos.

**Por que buscar pelo número?** O número é o identificador escolhido no cadastro. Ele não é necessariamente igual ao índice do array.

**Como impedir acesso fora dos arrays?** Verificando os limites antes de cadastrar ou registrar e percorrendo apenas posições abaixo dos contadores.

**Por que a transferência ocupa duas posições?** Ela produz uma saída na origem e uma entrada no destino. Se restar apenas uma vaga, toda a operação deve ser recusada.

**Como o extrato separa as contas?** Ele percorre as movimentações e imprime somente aquelas cujo número é igual ao da conta consultada.

**Por que o CPF é string?** Não é usado em contas matemáticas e pode começar com zero.

**Qual a diferença entre conta inativa e posição livre?** Uma conta inativa ainda está cadastrada, mantém seus dados e ocupa capacidade. Uma posição livre ainda não está no intervalo de contas cadastradas.

**Por que aparece saldo inicial separado?** O cadastro define o valor de abertura; as movimentações registram as operações posteriores.

**O programa grava arquivos?** Não. Arrays e contadores existem somente durante a execução. A persistência pertence à Etapa 3.

## Entrega

O PDF pede organização no GitHub e compartilhamento do link na planilha da disciplina, além da demonstração. Copie o endereço deste repositório para a planilha indicada no enunciado.
