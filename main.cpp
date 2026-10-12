#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// A estrutura de dados do código de barras foi criada através de uma struct
struct dadosDaLinha {
    string banco;
    string moeda;
    string vencimento;
    string valor;
    string tipo_convenio;
    string dados_convenio;

    string sequencial;
    string agencia;
    string conta;
    string modalidade;
    string complemento;

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
bool validar_banco(const string& banco) {
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

// Lê um campo com a quantidade de dígitos indicada.
// Repete a leitura até que a entrada tenha o tamanho correto e somente números.
string ler_digitos(int quantidade, const string& mensagem) {
    string entrada;

    while (true) {
        cout << mensagem;
        cin >> entrada;

        if (entrada.size() != quantidade) {
            cout << "Erro: informe exatamente " << quantidade << " digitos." << endl;
            continue;
        }

        bool apenas_digitos = true;

        for (int i = 0; i < entrada.size(); i++) {
            if (entrada[i] < '0' || entrada[i] > '9') {
                apenas_digitos = false;
                break;
            }
        }

        if (!apenas_digitos) {
            cout << "Erro: digite somente numeros de 0 a 9." << endl;
            continue;
        }

        return entrada;
    }
}

//validando o tamanho e os caracteres de entrada do decodificador
bool validar_entrada_decodificador(const string& entrada) {
    
    if (entrada.size() != 44 && entrada.size() != 47) {
        cout << "alerta vermelho: informe 44 ou 47 digitos." << endl;
        return false;
    }

    for (char caractere : entrada) {
        if (caractere < '0' || caractere > '9') {
            cout << "alerta vermelho: digite apenas numeros." << endl;
            return false;
        }
    }

    return true;
}

//conferindo o DV e codigo de barras
string obter_codigo_barras(const string& entrada) {

        if(!validar_entrada_decodificador(entrada)) {
            return "";
        }

        string codigo;

        if (entrada.size() == 47) {
        // Confere os tres DVs da linha digitavel.
        int dv1 = dv_mod10(entrada.substr(0, 9));
        int dv2 = dv_mod10(entrada.substr(10, 10));
        int dv3 = dv_mod10(entrada.substr(21, 10));

        if (dv1 != entrada[9] - '0' || dv2 != entrada[20] - '0' || dv3 != entrada[31] - '0') {

            cout << "alerta vermelho: DV da linha digitavel incorreto."  << endl;
            return "";
        }

        // Banco/moeda + DV geral + fator/valor + campo livre.
        codigo = entrada.substr(0, 4) + entrada.substr(32, 1) + entrada.substr(33, 14) + entrada.substr(4, 5) + entrada.substr(10, 10) + entrada.substr(21, 10);
        } else {
        // A entrada ja e um codigo de barras de 44 digitos.
            codigo = entrada;
        }

        // Retira o DV geral, que esta na quinta posicao.
        string sem_dv = codigo.substr(0, 4) + codigo.substr(5);

        int dv_calculado = dv_mod11(sem_dv);
        int dv_informado = codigo[4] - '0';

        if (dv_calculado != dv_informado) {
            cout << "alerta vermelho: DV geral incorreto." << endl;
            return "";
        }
        return codigo;
    }

// Converte o fator de vencimento em uma data, conforme o ciclo informado.
// A biblioteca <ctime> ajusta os dias, meses e anos automaticamente.
string recuperar_data(const string& fator, int ciclo) {
    int numero = stoi(fator);

    if (numero == 0) {
        return "Sem vencimento";
    }

    tm data = {};

    data.tm_hour = 12;
    data.tm_isdst = -1;

    if (ciclo == 1) {
    // Base antiga: 07/10/1997.
        data.tm_year = 1997 - 1900;
        data.tm_mon = 10 - 1;
        data.tm_mday = 7 + numero;
    } else if (ciclo == 2 && numero >= 1000) {
        // Base nova: fator 1000 em 22/02/2025.
        data.tm_year = 2025 - 1900;
        data.tm_mon = 2 - 1;
        data.tm_mday = 22 + numero - 1000;

    } else {
        cout << "alerta vermelho: ciclo invalido para este fator."  << endl;
        return "";
    }

    // A biblioteca converte os dias excedentes em meses e anos.
    if (mktime(&data) == static_cast<time_t>(-1)) {
        cout << "alerta vermelho: data fora do intervalo da biblioteca."  << endl;
        return "";
    }

    char resultado[11];

    if (strftime(resultado, sizeof(resultado), "%d/%m/%Y", &data) == 0) {
        cout << "alerta vermelho: nao foi possivel formatar a data." << endl;
        return "";
    }

    return string(resultado);
}

// Funcao para identificar o tipo de convenio, validar os dados informados
// e armazenar as informacoes correspondentes na estrutura dadosDaLinha.
void convenio(dadosDaLinha &dados) {
    int opcao = 0;

    while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4) {

        cout << "\n--- TIPO DE CONVENIO ---" << endl;
        cout << "1 - Convenio de 4 posicoes" << endl;
        cout << "2 - Convenio de 5 posicoes" << endl;
        cout << "3 - Convenio de 7 posicoes" << endl;
        cout << "4 - Nosso numero livre de 17 posicoes" << endl;
        cout << "Escolha uma opcao: ";

        cin >> opcao;

        if (opcao < 1 || opcao > 4) {
            cout << "Alerta Vermelho: opcao invalida." << endl;
        }
    }
    if (opcao == 1) {
        dados.tipo_convenio = "04";
        dados.dados_convenio = ler_digitos(4, "Digite o convenio (4 digitos): ");
        dados.sequencial = ler_digitos(7, "Digite o sequencial (7 digitos): ");
        dados.agencia = ler_digitos(4, "Digite a agencia (4 digitos): ");
        dados.conta = ler_digitos(8, "Digite a conta (8 digitos): ");
        dados.modalidade = ler_digitos(2, "Digite a modalidade (2 digitos): ");

    } else if (opcao == 2) {
        dados.tipo_convenio = "05";
        dados.dados_convenio = ler_digitos(5, "Digite o convenio (5 digitos): ");
        cout << "Alerta Amarelo: falta confirmar a composicao " << "do campo livre para o convenio de 5 posicoes." << endl;

    } else if (opcao == 3) {
        dados.tipo_convenio = "07";
        dados.dados_convenio = ler_digitos(7, "Digite o convenio (7 digitos): ");
        dados.complemento = ler_digitos(10, "Digite o complemento (10 digitos): ");
        dados.modalidade = ler_digitos(2, "Digite a modalidade (2 digitos): ");

    } else {
        dados.tipo_convenio = "17";
        dados.dados_convenio = ler_digitos(6, "Digite o convenio (6 digitos): ");
        dados.nosso_numero = validar_nosso_numero();
        dados.modalidade = "21";
        }
    cout << "\nValidacao dos campos concluida." << endl;
}

// Monta o campo livre de 25 dígitos conforme o tipo de convênio.
// Reúne os dados na ordem correspondente e verifica o tamanho final.
string montar_campo_livre(const dadosDaLinha &dados) {
    string campo_livre;

    if (dados.tipo_convenio == "04") {
        // Convenio de 4 posicoes: 4 + 7 + 4 + 8 + 2 = 25
        campo_livre = dados.dados_convenio + dados.sequencial + dados.agencia + dados.conta + dados.modalidade;
    }
    else if (dados.tipo_convenio == "05") {
        // A composicao para 5 posicoes ainda precisa ser confirmada.
        cout << "Composicao do convenio de 5 posicoes pendente." << endl;
        return "";
    }
    else if (dados.tipo_convenio == "07") {
        // Convenio de 7 posicoes: 6 zeros + 7 + 10 + 2 = 25
        campo_livre = "000000"+ dados.dados_convenio + dados.complemento + dados.modalidade;
    }
    else if (dados.tipo_convenio == "17") {
        // Nosso Numero livre: convenio de 6 + NN de 17 + modalidade 21
        campo_livre = dados.dados_convenio + dados.nosso_numero + dados.modalidade;
    }
    else {
        cout << "Tipo de convenio invalido." << endl;
        return "";
    }

    if (campo_livre.length() != 25) {
        cout << "Erro: campo livre deve ter 25 digitos." << endl;
        return "";
    }

    return campo_livre;
}

//CODIFICADOR
void codificador() {
    cout << "\n--- CODIFICADOR ---" << endl;

    dadosDaLinha dados;

    dados.banco = codigo_banco();

    if (!validar_banco(dados.banco)) {
        cout << "Alerta Vermelho: Codigo de banco invalido." << endl;
        return;
    }

    dados.moeda = ler_digitos(1, "Digite o codigo da moeda (1 digito): ");

    dados.vencimento = ler_digitos(4, "Digite o vencimento (4 digitos): ");

    dados.valor = ler_digitos(10, "Digite o valor (no maximo 10 digitos, sem virgualas): ");   

    convenio(dados);

    cout << "\nBanco: " << dados.banco << endl;
    cout << "Tipo de convenio: " << dados.tipo_convenio << endl;
    cout << "Dados do convenio: " << dados.dados_convenio << endl;

    if (dados.tipo_convenio == "17") {
        cout << "Nosso numero: " << dados.nosso_numero << endl;
    }

    cout << "Validacao concluida." << endl;

    string campo_livre = montar_campo_livre(dados);

    if (campo_livre.empty()) {
        cout << "Nao foi possivel montar o campo livre." << endl;
    return;
    }

    cout << "Campo livre: " << campo_livre << endl;

    string base_codigo = dados.banco + dados.moeda + dados.vencimento + dados.valor + campo_livre;
    
    string dv11_calculado = to_string(dv_mod11(base_codigo));

    dados.codigo_barras = dados.banco + dados.moeda + dv11_calculado + dados.vencimento + dados.valor + campo_livre;

    cout << "\n>>> CODIGO DE BARRAS GERADO: " << dados.codigo_barras << endl;

    //Linha digitável
    string bloco_1 = dados.banco + dados.moeda + campo_livre.substr(0, 5);
    string dv1 = to_string(dv_mod10(bloco_1));
    string campo_1 = bloco_1.substr(0, 5) + "." + bloco_1.substr(5, 4) + dv1;
    
    string bloco_2 = campo_livre.substr(5, 10);
    string dv2 = to_string(dv_mod10(bloco_2));
    string campo_2 = bloco_2.substr(0, 5) + "." + bloco_2.substr(5, 5) + dv2;

    string bloco_3 = campo_livre.substr(15, 10);
    string dv3 = to_string(dv_mod10(bloco_3));
    string campo_3 = bloco_3.substr(0, 5) + "." + bloco_3.substr(5, 5) + dv3;

    string campo_4 = dv11_calculado;

    string campo_5 = dados.vencimento + dados.valor;

    dados.linha_digitavel = campo_1 + " " + campo_2 + " " + campo_3 + " " + campo_4 + " " + campo_5;

    cout << ">>> LINHA DIGITAVEL GERADA: " << dados.linha_digitavel << endl;
}

//DECODIFICADOR
//testar 
void decodificador() {

    cout << "Digite o codigo de barras (44) ou a linha digitavel (47): ";

    string entrada;

    // Le a linha inteira, incluindo pontos e espacos.
    if (!getline(cin >> ws, entrada)) {
        cout << "alerta vermelho: faltam dados de entrada." << endl;
        return;
    }

    // Remove a formatacao da linha digitavel.
    string numeros;

    for (char caractere : entrada) {
        if (caractere != '.' && caractere != ' ' && caractere != '\t') {
            numeros += caractere;
        }
    }

    // Cria a variavel que guarda os dados.
    dadosDaLinha dados;

    dados.codigo_barras = obter_codigo_barras(numeros);

    if (dados.codigo_barras.empty()) {
        return;
    }

    // Daqui em diante, trabalhamos com o codigo de 44 digitos.
    string codigo = dados.codigo_barras;
    
    dados.banco = codigo.substr(0, 3);
    dados.moeda = codigo.substr(3, 1);
    dados.vencimento = codigo.substr(5, 4);
    dados.valor = codigo.substr(9, 10);

    string campo_livre = codigo.substr(19, 25);

    dados.modalidade = campo_livre.substr(23, 2);

    // O manual fornecido define o campo livre do Banco do Brasil.
    if (dados.banco != "001" || dados.moeda != "9") {
        cout << "alerta vermelho: campo livre suportado apenas para banco 001 e moeda 9." << endl;
        return;
    }

    // Modalidade 21 identifica o nosso numero livre de 17 posicoes.
    if (dados.modalidade == "21") {
        
        dados.tipo_convenio = "17";

        dados.dados_convenio = campo_livre.substr(0, 6);
        dados.nosso_numero = campo_livre.substr(6, 17);

    } else if (campo_livre.substr(0, 6) == "000000") {
        // Convenio de sete posicoes: seis zeros iniciais.
        dados.tipo_convenio = "07";

        dados.dados_convenio = campo_livre.substr(6, 7);
        dados.complemento = campo_livre.substr(13, 10);

        dados.nosso_numero = dados.dados_convenio + dados.complemento;

        if (stoi(dados.dados_convenio) < 1000000) {
            cout << "alerta vermelho: convenio 07 incompativel com o manual." << endl;
            return;
        }

    } else {
        // Os convenios 04 e 06 nao podem ser diferenciados
        // apenas pelos digitos do codigo.
        cout << "Tipo do convenio (04 ou 06, conforme o manual): ";

        if (!(cin >> dados.tipo_convenio)) {
            cout << "alerta vermelho: faltou o tipo do convenio." << endl;
            return;
        }

        int tamanho;

        if (dados.tipo_convenio == "04") {
            tamanho = 4;
        } else if (dados.tipo_convenio == "06") {
            tamanho = 6;
        } else {
            cout << "alerta vermelho: informe 04 ou 06 o manual nao define 05." << endl;
            return;
        }

        dados.dados_convenio = campo_livre.substr(0, tamanho);

        dados.sequencial = campo_livre.substr(tamanho, 11 - tamanho);

        dados.agencia = campo_livre.substr(11, 4);
        dados.conta = campo_livre.substr(15, 8);
        dados.nosso_numero = campo_livre.substr(0, 11);
    }

    if (stoi(dados.dados_convenio) == 0) {
        cout << "alerta vermelho: convenio nao pode ser zero." << endl;
        return;
    }

}

int main() {
    menu_principal();

    return 0;
}