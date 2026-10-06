#include <iostream>
#include <string>
using namespace std;

// A estrutura de dados do código de barras foi criada através de uma struct
struct dadosDaLinha {
    string banco;
    string moeda;
    string vencimento;
    string valor;
    string convenio;
    string dadosConvenio;
};

int codigo_banco(){
    return 0;
}

int digitoVerificador(string bloco) {
    int somaTotal = 0;
    int multiplicador = 2;

    for (int i = bloco.length() - 1; i >= 0; i--) {    
        int num = bloco[i] - '0';
        int resultado = num * multiplicador;

        if (resultado > 9)
        {
            resultado = resultado - 9;
        }

        if (multiplicador == 2)
        {
            multiplicador = 1;
        } else {
            multiplicador = 2;
        }

        somaTotal = somaTotal + resultado;        
    }

    int resto = somaTotal % 10;
    int digitoFinal = 10 - resto;

    if(digitoFinal == 10){
        digitoFinal = 0;
    }

    return digitoFinal;
}

int main() {
    while (opcao != 0)
    {
        cout << "Digite 1 para codificar ou 2 para decodificar: " << endl;
        cin >> opcao;

        if (opcao == 1)
        {
            codificador();
        }
        else if (opcao == 2)
        {
            decodificador();
        }
        else if (opcao == 0)
        {
            cout << "Encerrando o programa..." << endl;
        }
        else
        {
            cout << "Numero invalido!" << endl;
        }
    }
    return 0;
}