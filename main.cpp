#include <iostream>
#include <string>
using namespace std;

// A estrutura de dados do código de barras foi criada através de uma struct

//Acho que seria legal fazer uma classe para o codificador
struct dadosDaLinha {
    string banco;
    string moeda;
    string vencimento;
    string valor;
    string convenio;
    string dadosConvenio;
};
// Vamos começar pelo codificador

//função para ler o codigo do banco
string codigo_banco(){
    string banco;
    cout<< "Digite o codigo do banco";
    cin>> banco;
    return banco;
}
//função para validar a quantidade de digitos do banco
bool validar_banco(){
    if(banco.size() != 3){
        return false;
    }
    for(int i = 0; i < banco.size(); i++){
        if(banco[i] < '0' || banco[i] > '9'){
        return false;
        }
    }
    return true;
}

// preciso de comentarios para entender o que foi feito
#if 0
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
#endif

int main() {

    // validando o codigo do banco e chamando funções
    string banco = codigo_banco();

    if(validar_banco(string banco)){
        cout << "Banco: " << banco <<endl;
    }else{
        cout << "Alerta Vermelho: Codigo de banco invalido";
    }


    //Não irei editar, pois não sei do que se trata.
    //Comentei para não atrapalhar na minha implementação
    
    #if 0 // serve para dizer ao pré-processador do c++ para ignorar todo o cod até encontrar o #endif
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
    #endif

    return 0;

}