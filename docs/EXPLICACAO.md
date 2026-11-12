# Explicação do programa

## Continuidade da primeira etapa

A base consultada foi o repositório `luhsampaio39-sudo/Banco-Horizonte-INF101`, revisão `7e686ae2cef59f6b2f4819c48dad09fa1dc34d54`. Na Etapa 1, o programa principal usava variáveis para uma conta e o desafio repetia variáveis para cinco contas. A Etapa 2 resolve essa repetição por meio de arrays paralelos.

O programa mantém nome, CPF, tipo, saldo, situação, validações com `getline` e `istringstream`, formatação com duas casas e as operações de gestão da versão anterior. A continuidade é do código e das funcionalidades; não existe importação de dados entre execuções, pois ambas as etapas armazenam os dados somente em memória.

## Arrays paralelos

`numeroConta[i]`, `nomeCliente[i]`, `cpf[i]`, `tipoConta[i]`, `saldo[i]` e `contaAtiva[i]` pertencem à mesma conta. O índice `i` vai de zero até `quantidadeContas - 1`. As posições depois desse intervalo ainda não representam contas cadastradas.

`quantidadeContas` também indica a próxima posição livre. O contador só aumenta depois da validação de todos os dados. `MAX_CONTAS` limita o cadastro a 100 contas; não existe exclusão.

Para localizar uma conta, o programa percorre os números cadastrados com `for`. O índice começa em `-1`; se uma correspondência for encontrada, recebe a posição correta. Se continuar `-1`, a operação é recusada antes de qualquer acesso ao array usando esse índice.

O array adicional `saldoInicial` permite explicar a origem do saldo no extrato, sem confundir o valor de abertura com os depósitos posteriores.

## Histórico

Cada posição dos arrays `contaMovimentacao`, `tipoMovimentacao` e `valorMovimentacao` forma um registro: número da conta, código D/S e valor. `quantidadeMovimentacoes` é a próxima posição disponível e `MAX_MOVIMENTACOES` vale 500.

No depósito, aumenta-se o saldo e grava-se um registro D. No saque, verifica-se o saldo, diminui-se o valor e grava-se um registro S. O contador aumenta uma vez em cada caso.

Na transferência, todas as verificações acontecem primeiro: origem e destino existentes, ativos e diferentes; espaço para dois registros; valor válido; saldo suficiente; limite do saldo de destino. Somente depois o programa altera os dois saldos e registra S na origem e D no destino. O contador aumenta duas vezes. Assim, não existe débito sem crédito quando a validação recusa a operação.

Embora a tabela do PDF mencione o código T como possibilidade, a seção 2.5 especifica os dois registros S/D. Esta implementação segue esse exemplo. Por isso, o extrato informa que D e S também incluem transferências; os arrays solicitados não guardam a contraparte ou um identificador próprio de transferência.

## Entrada, laços e decisões

- `getline` lê a linha inteira e preserva nomes com espaços.
- `istringstream` converte a linha em número; a checagem do fim da linha impede aceitar `12abc` como `12`.
- `do while` repete cada pergunta até uma entrada válida e mantém o menu ativo até a opção 0.
- `for` procura contas, lista cadastros e percorre o histórico.
- `if` valida os dados e escolhe a operação.
- `continue` retorna ao começo do laço do menu depois de concluir ou recusar uma operação.
- `bool` representa a situação da conta e as validações; `char` representa D/S. Ambos constam dos arrays exigidos no PDF da Etapa 2.
- O fim da entrada encerra o processo sem executar uma operação ainda incompleta.

## Dinheiro

O tipo `double` foi mantido conforme o enunciado. `fixed` e `setprecision(2)` formatam a saída. Como frações decimais podem ter pequenas diferenças na representação binária, `round(valor * 100) / 100` normaliza o valor para centavos após as operações. A entrada valida a precisão monetária com uma tolerância numérica pequena e rejeita valores menores que um centavo nas movimentações. `isfinite` rejeita valores não finitos.

O limite técnico de R$ 1 bilhão evita trabalhar com valores monetários enormes, que prejudicariam a precisão de centavos. Não é implementado cheque especial, rendimento ou tarifa.

## Por que está tudo no main?

O PDF diz expressamente que funções próprias não são obrigatórias. Esta solução mantém as operações no `main()`, usando arrays, decisões e laços. Há um bloco compartilhado de busca e validação para evitar repetir a mesma lógica em cada opção. Não são usados `vector`, classes próprias, `struct`, ponteiros explícitos ou banco de dados.

Uma modularização futura poderia extrair as rotinas cadastrar, listar, consultar, depositar, sacar, transferir e exibir extrato para funções, passando os arrays e os contadores necessários. Isso é uma alternativa de organização, não uma funcionalidade ausente nesta entrega.
