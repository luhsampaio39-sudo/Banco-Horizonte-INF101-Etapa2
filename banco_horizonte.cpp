#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const int MAX_CONTAS = 100;
    const int MAX_MOVIMENTACOES = 500;
    const double LIMITE_SALDO = 1000000000.00;

    int numeroConta[MAX_CONTAS] = {};
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS] = {};
    double saldo[MAX_CONTAS] = {};
    bool contaAtiva[MAX_CONTAS] = {};
    double saldoInicial[MAX_CONTAS] = {};
    int quantidadeContas = 0;

    int contaMovimentacao[MAX_MOVIMENTACOES] = {};
    char tipoMovimentacao[MAX_MOVIMENTACOES] = {};
    double valorMovimentacao[MAX_MOVIMENTACOES] = {};
    int quantidadeMovimentacoes = 0;

    int opcao = -1;
    string entrada;
    bool entradaValida;
    cout << fixed << setprecision(2);

    do {
        cout << "\n========================================\n"
             << "             BANCO HORIZONTE\n"
             << "          INF101 - ETAPA 2\n"
             << "========================================\n"
             << "1 - Cadastrar conta\n"
             << "2 - Listar contas\n"
             << "3 - Consultar conta\n"
             << "4 - Depositar\n"
             << "5 - Sacar\n"
             << "6 - Transferir\n"
             << "7 - Exibir extrato\n"
             << "8 - Verificar saldo\n"
             << "9 - Alterar tipo da conta\n"
             << "10 - Ativar/Desativar conta\n"
             << "0 - Sair\n";

        do {
            cout << "Escolha: ";
            if (!getline(cin, entrada)) return 0;
            istringstream leitura(entrada);
            entradaValida = static_cast<bool>(leitura >> opcao);
            if (entradaValida) {
                leitura >> ws;
                entradaValida = leitura.eof() && opcao >= 0 && opcao <= 10;
            }
            if (!entradaValida) cout << "Opcao invalida. Digite de 0 a 10.\n";
        } while (!entradaValida);

        if (opcao == 0) {
            cout << "Banco Horizonte encerrado. Dados em memoria descartados.\n";
            break;
        }

        if (opcao == 1) {
            if (quantidadeContas == MAX_CONTAS) {
                cout << "Limite de 100 contas atingido.\n";
                continue;
            }
            int indice = quantidadeContas;
            do {
                cout << "Numero da nova conta: ";
                if (!getline(cin, entrada)) return 0;
                istringstream leitura(entrada);
                entradaValida = static_cast<bool>(leitura >> numeroConta[indice]);
                if (entradaValida) {
                    leitura >> ws;
                    entradaValida = leitura.eof() && numeroConta[indice] > 0;
                }
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroConta[indice]) entradaValida = false;
                }
                if (!entradaValida) cout << "Numero invalido ou ja cadastrado.\n";
            } while (!entradaValida);
            do {
                cout << "Nome do titular: ";
                if (!getline(cin, nomeCliente[indice])) return 0;
                entradaValida = nomeCliente[indice].find_first_not_of(" \t\r") != string::npos;
                if (!entradaValida) cout << "O nome nao pode ficar vazio.\n";
            } while (!entradaValida);
            do {
                cout << "CPF (11 digitos, sem pontuacao): ";
                if (!getline(cin, cpf[indice])) return 0;
                entradaValida = cpf[indice].size() == 11;
                for (char digito : cpf[indice]) {
                    if (digito < '0' || digito > '9') entradaValida = false;
                }
                if (!entradaValida) cout << "Informe exatamente 11 digitos numericos.\n";
            } while (!entradaValida);
            do {
                cout << "Tipo (1 = Corrente; 2 = Poupanca): ";
                if (!getline(cin, entrada)) return 0;
                istringstream leitura(entrada);
                entradaValida = static_cast<bool>(leitura >> tipoConta[indice]);
                if (entradaValida) {
                    leitura >> ws;
                    entradaValida = leitura.eof() && (tipoConta[indice] == 1 || tipoConta[indice] == 2);
                }
                if (!entradaValida) cout << "Tipo invalido. Digite 1 ou 2.\n";
            } while (!entradaValida);
            do {
                cout << "Saldo inicial (ponto nos centavos): R$ ";
                if (!getline(cin, entrada)) return 0;
                istringstream leitura(entrada);
                entradaValida = static_cast<bool>(leitura >> saldo[indice]);
                if (entradaValida) {
                    leitura >> ws;
                    entradaValida = leitura.eof() && isfinite(saldo[indice])
                        && saldo[indice] >= 0 && saldo[indice] <= LIMITE_SALDO;
                }
                if (entradaValida) {
                    entradaValida = fabs(saldo[indice] * 100 - round(saldo[indice] * 100)) < 0.0001;
                }
                if (!entradaValida) cout << "Saldo invalido. Use de 0 a 1000000000, com ate 2 casas decimais.\n";
            } while (!entradaValida);
            saldo[indice] = round(saldo[indice] * 100) / 100;
            saldoInicial[indice] = saldo[indice];
            contaAtiva[indice] = true;
            quantidadeContas++;
            cout << "Conta cadastrada com sucesso e ativada.\n";
            continue;
        }

        if (quantidadeContas == 0) {
            cout << "Nenhuma conta cadastrada. Use a opcao 1.\n";
            continue;
        }
        if (opcao == 2) {
            cout << "\n--- CONTAS CADASTRADAS ---\n";
            for (int i = 0; i < quantidadeContas; i++) {
                cout << "Conta: " << numeroConta[i] << " | Titular: " << nomeCliente[i]
                     << " | Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca")
                     << " | " << (contaAtiva[i] ? "Ativa" : "Inativa") << '\n';
            }
            cout << "Total de contas: " << quantidadeContas << '\n';
            continue;
        }

        int numero = 0;
        do {
            cout << (opcao == 6 ? "Numero da conta de origem: " : "Numero da conta: ");
            if (!getline(cin, entrada)) return 0;
            istringstream leitura(entrada);
            entradaValida = static_cast<bool>(leitura >> numero);
            if (entradaValida) {
                leitura >> ws;
                entradaValida = leitura.eof() && numero > 0;
            }
            if (!entradaValida) cout << "Informe um numero inteiro positivo.\n";
        } while (!entradaValida);
        int indice = -1;
        for (int i = 0; i < quantidadeContas; i++) {
            if (numeroConta[i] == numero) indice = i;
        }
        if (indice == -1) {
            cout << "Conta nao encontrada.\n";
            continue;
        }
        if (opcao == 3) {
            cout << "\n--- DADOS DA CONTA ---\n"
                 << "Numero: " << numeroConta[indice] << '\n'
                 << "Titular: " << nomeCliente[indice] << '\n'
                 << "CPF: " << cpf[indice] << '\n'
                 << "Tipo: " << (tipoConta[indice] == 1 ? "Corrente" : "Poupanca") << '\n'
                 << "Situacao: " << (contaAtiva[indice] ? "Ativa" : "Inativa") << '\n';
            if (contaAtiva[indice]) cout << "Saldo atual: R$ " << saldo[indice] << '\n';
            else cout << "Saldo indisponivel: ative a conta para consultar.\n";
            continue;
        }
        if (opcao == 10) {
            contaAtiva[indice] = !contaAtiva[indice];
            cout << (contaAtiva[indice] ? "Conta ativada.\n" : "Conta desativada.\n");
            continue;
        }
        if (!contaAtiva[indice]) {
            cout << "Conta inativa. Ative-a antes desta operacao.\n";
            continue;
        }
        if (opcao == 8) {
            cout << "Saldo atual: R$ " << saldo[indice] << '\n';
            continue;
        }
        if (opcao == 9) {
            int novoTipo = 0;
            do {
                cout << "Novo tipo (1 = Corrente; 2 = Poupanca): ";
                if (!getline(cin, entrada)) return 0;
                istringstream leitura(entrada);
                entradaValida = static_cast<bool>(leitura >> novoTipo);
                if (entradaValida) {
                    leitura >> ws;
                    entradaValida = leitura.eof() && (novoTipo == 1 || novoTipo == 2);
                }
                if (!entradaValida) cout << "Tipo invalido. Digite 1 ou 2.\n";
            } while (!entradaValida);
            tipoConta[indice] = novoTipo;
            cout << "Tipo da conta atualizado.\n";
            continue;
        }
        if (opcao == 7) {
            cout << "\n--- EXTRATO DA CONTA " << numeroConta[indice] << " ---\n"
                 << "Titular: " << nomeCliente[indice] << '\n'
                 << "Saldo inicial: R$ " << saldoInicial[indice] << '\n'
                 << "D = entrada/deposito; S = saida/saque (incluem transferencias).\n";
            int total = 0;
            for (int i = 0; i < quantidadeMovimentacoes; i++) {
                if (contaMovimentacao[i] == numeroConta[indice]) {
                    total++;
                    cout << total << " | " << tipoMovimentacao[i] << " | R$ "
                         << valorMovimentacao[i] << '\n';
                }
            }
            if (total == 0) cout << "Nenhuma movimentacao nesta conta.\n";
            cout << "Total de movimentacoes da conta: " << total << '\n'
                 << "Saldo atual: R$ " << saldo[indice] << '\n';
            continue;
        }

        int destino = -1;
        if (opcao == 6) {
            do {
                cout << "Numero da conta de destino: ";
                if (!getline(cin, entrada)) return 0;
                istringstream leitura(entrada);
                entradaValida = static_cast<bool>(leitura >> numero);
                if (entradaValida) {
                    leitura >> ws;
                    entradaValida = leitura.eof() && numero > 0;
                }
                if (!entradaValida) cout << "Informe um numero inteiro positivo.\n";
            } while (!entradaValida);
            for (int i = 0; i < quantidadeContas; i++) {
                if (numeroConta[i] == numero) destino = i;
            }
            if (destino == -1) {
                cout << "Conta de destino nao encontrada.\n";
                continue;
            }
            if (destino == indice) {
                cout << "Escolha duas contas diferentes.\n";
                continue;
            }
            if (!contaAtiva[destino]) {
                cout << "Conta de destino inativa.\n";
                continue;
            }
        }
        int registrosNecessarios = (opcao == 6 ? 2 : 1);
        if (quantidadeMovimentacoes + registrosNecessarios > MAX_MOVIMENTACOES) {
            cout << "Historico sem espaco. Operacao cancelada; saldos preservados.\n";
            continue;
        }
        double valor = 0;
        do {
            cout << "Valor (ponto nos centavos): R$ ";
            if (!getline(cin, entrada)) return 0;
            istringstream leitura(entrada);
            entradaValida = static_cast<bool>(leitura >> valor);
            if (entradaValida) {
                leitura >> ws;
                entradaValida = leitura.eof() && isfinite(valor) && valor > 0 && valor <= LIMITE_SALDO;
            }
            if (entradaValida) {
                entradaValida = fabs(valor * 100 - round(valor * 100)) < 0.0001;
                entradaValida = entradaValida && round(valor * 100) >= 1;
            }
            if (!entradaValida) cout << "Valor invalido. Use de 0.01 a 1000000000, com ate 2 casas decimais.\n";
        } while (!entradaValida);
        valor = round(valor * 100) / 100;
        if (opcao != 4 && valor > saldo[indice]) {
            cout << "Saldo insuficiente. Operacao cancelada.\n";
            continue;
        }
        int recebedor = (opcao == 4 ? indice : destino);
        if (recebedor != -1 && saldo[recebedor] + valor > LIMITE_SALDO) {
            cout << "Limite de saldo excedido. Operacao cancelada.\n";
            continue;
        }
        if (opcao == 4) saldo[indice] = round((saldo[indice] + valor) * 100) / 100;
        else saldo[indice] = round((saldo[indice] - valor) * 100) / 100;
        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
        tipoMovimentacao[quantidadeMovimentacoes] = (opcao == 4 ? 'D' : 'S');
        valorMovimentacao[quantidadeMovimentacoes] = valor;
        quantidadeMovimentacoes++;

        if (opcao == 6) {
            saldo[destino] = round((saldo[destino] + valor) * 100) / 100;
            contaMovimentacao[quantidadeMovimentacoes] = numeroConta[destino];
            tipoMovimentacao[quantidadeMovimentacoes] = 'D';
            valorMovimentacao[quantidadeMovimentacoes] = valor;
            quantidadeMovimentacoes++;
            cout << "Transferencia realizada com sucesso.\n";
        } else if (opcao == 4) cout << "Deposito realizado com sucesso.\n";
        else cout << "Saque realizado com sucesso.\n";
        cout << "Saldo atual: R$ " << saldo[indice] << '\n';
    } while (opcao != 0);
    return 0;
}
