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
// Vamos começar pelo codificador -- Concordo, mas antes temos que codificar o módulo 11 (digito verificador)

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

//DIGITO VERIFICADOR - MÓDULO 10
//A função abaixo define o cálculo do digito verificador, de acordo com o módulo 10, seguindo as regras da Febraban.
int dv_mod10(string bloco) {
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

//DIGITO VERIFICADOR - MÓDULO 11
//A função abaixo define o cálculo do digito verificador, de acordo com o módulo 11, seguindo as regras da Febraban.
int dv_mod11(string bloco){
    int somaTotal = 0;
    int multiplicador = 2;

    for(int i = bloco.length() - 1; i >= 0; i--){
        int num = bloco[i] - '0';
        int resultado = num * multiplicador;        

        somaTotal = somaTotal + resultado;

        multiplicador = multiplicador + 1;

        if(multiplicador > 9){
            multiplicador = 2;
        }    

        int resto = somaTotal % 11;
        int digitoFinal = 11 - resto;

        if(digitoFinal == 0 || digitoFinal == 10 || digitoFinal == 11){
            digitoFinal = 1;
        }

        return digitoFinal;
    }

}



int main() {

    // validando o codigo do banco e chamando funções
    string banco = codigo_banco();

    if(validar_banco(string banco)){
        cout << "Banco: " << banco <<endl;
    }else{
        cout << "Alerta Vermelho: Codigo de banco invalido";
    }


    //Não irei editar, pois não sei do que se trata. -- Não precisa editar, você não ficou com essa parte.
    //Comentei para não atrapalhar na minha implementação -- Foi só um menu de interação pro usuário final, esse menu tem que ter, não atrapalharia a sua implementação diretamente.
    
    //Variável criada para armazenar a opção que o usuário vai querer: codificar ou decodificar;
 /*   int opcao = -1;
    //Laço de chamada da entrada do usuário, nele o usuário vai dizer se quer codificar ou decodificar o código
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
    
*/
    return 0;
}