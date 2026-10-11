
#include <iostream>
#include <string>
using namespace std;

// A estrutura de dados do código de barras foi criada através de uma struct

struct dadosDaLinha {
    string banco;
    string moeda;
    string vencimento;
    string valor;
    string tipo_convenio;
    string dados_convenio;
    string nosso_numero;
    string codigo_barras;
    string linha_digitavel;
};

// Declaração das funções
void codificador();
void decodificador();

// Função para exibir o menu e ler a opção do usuário
int menu_principal() {
    int opcao = -1;

    while (opcao != 0) {
        cout << "\nDigite 1 para codificar:" << endl;
        cout << "Digite 2 para decodificar:" << endl;
        cout << "Digite 0 para sair:" << endl;
        cin >> opcao;

        if (opcao == 1) {
            codificador();
        } else if (opcao == 2) {
            decodificador();
        } else if (opcao == 0) {
            cout << "Encerrando o programa..." << endl;
        } else {
            cout << "Numero invalido!" << endl;
        }
    }

    return opcao;
}

// Função para ler o código do banco
string codigo_banco() {
    string banco;

    cout << "Digite o codigo do banco: ";
    cin >> banco;

    return banco;
}

// Função para validar a quantidade de dígitos do banco
bool validar_banco(string banco) {
    if (banco.size() != 3) {
        return false;
    }

    for (int i = 0; i < banco.size(); i++) {
        if (banco[i] < '0' || banco[i] > '9') {
            return false;
        }
    }

    return true;
}

// Função para validar o tamanho do nosso número livre e os caracteres
string validar_nosso_numero() {
    string nosso_numero;
    bool valido = false;

    while (!valido) {
        cout << "Digite o nosso numero livre (17 digitos): ";
        cin >> nosso_numero;

        if (nosso_numero.size() != 17) {
            cout << "Alerta Vermelho: O nosso numero deve ter exatamente 17 digitos." << endl;
        } else {
            bool apenas_digitos = true;

            for (int i = 0; i < nosso_numero.size(); i++) {
                if (nosso_numero[i] < '0' || nosso_numero[i] > '9') {
                    apenas_digitos = false;
                    break;
                }
            }

            if (!apenas_digitos) {
                cout << "Alerta Amarelo: Digite apenas numeros de 0 a 9." << endl;
            } else {
                valido = true;
            }
        }
    }

    return nosso_numero;
}

// DIGITO VERIFICADOR - MÓDULO 10
// Calcula o dígito verificador usando o módulo 10
int dv_mod10(string bloco) {
    int somaTotal = 0;
    int multiplicador = 2;

    for (int i = bloco.length() - 1; i >= 0; i--) {
        int num = bloco[i] - '0';
        int resultado = num * multiplicador;

        if (resultado > 9) {
            resultado = resultado - 9;
        }

        if (multiplicador == 2) {
            multiplicador = 1;
        } else {
            multiplicador = 2;
        }

        somaTotal = somaTotal + resultado;
    }

    int resto = somaTotal % 10;
    int digitoFinal = 10 - resto;

    if (digitoFinal == 10) {
        digitoFinal = 0;
    }

    return digitoFinal;
}

// DIGITO VERIFICADOR - MÓDULO 11
// Calcula o dígito verificador usando o módulo 11
int dv_mod11(string bloco) {
    int somaTotal = 0;
    int multiplicador = 2;

    for (int i = bloco.length() - 1; i >= 0; i--) {
        int num = bloco[i] - '0';
        int resultado = num * multiplicador;

        somaTotal = somaTotal + resultado;

        multiplicador = multiplicador + 1;

        if (multiplicador > 9) {
            multiplicador = 2;
        }
    }

    int resto = somaTotal % 11;
    int digitoFinal = 11 - resto;

    if (digitoFinal == 0 || digitoFinal == 10 || digitoFinal == 11) {
        digitoFinal = 1;
    }

    return digitoFinal;
}

// Função provisória do codificador
void codificador() {
    cout << "\n--- CODIFICADOR ---" << endl;

    string banco = codigo_banco();

    if (validar_banco(banco)) {
        cout << "Banco: " << banco << endl;

        string nosso_numero = validar_nosso_numero();
        cout << "Nosso numero: " << nosso_numero << endl;

        cout << "Validacao concluida. A montagem do codigo de barras ainda sera implementada." << endl;
    } else {
        cout << "Alerta Vermelho: Codigo de banco invalido." << endl;
    }
}

// Função provisória do decodificador
void decodificador() {
    cout << "\n--- DECODIFICADOR ---" << endl;
    cout << "Funcao ainda em desenvolvimento." << endl;
}

int main() {
    menu_principal();

    return 0;
}