# Codificador e Decodificador de Boletos Bancários (Padrão FEBRABAN / Banco do Brasil)

Este repositório contém a implementação em C++ de um sistema codificador e decodificador de boletos bancários, desenvolvido para a geração, validação e leitura de Códigos de Barras (44 posições) e Linhas Digitáveis (47 posições) segundo as especificações técnicas da FEBRABAN e o layout de Campo Livre do Banco do Brasil (código `001`).

---

## Funcionalidades

### 1. Codificador
* **Validação de Entrada:** Garante que todos os campos informados contenham apenas caracteres numéricos e respeitem o tamanho exato exigido pelo padrão bancário.
* **Montagem do Campo Livre (25 dígitos):** Suporta as quatro composições do Banco do Brasil:
  * **Convênio de 4 posições:** Convênio (4 dígitos) + Sequencial (7 dígitos) + Agência (4 dígitos) + Conta (8 dígitos) + Modalidade (2 dígitos).
  * **Convênio de 6 posições:** Convênio (6 dígitos) + Sequencial (5 dígitos) + Agência (4 dígitos) + Conta (8 dígitos) + Modalidade (2 dígitos).
  * **Convênio de 7 posições:** 6 Zeros fixos (`000000`) + Convênio (7 dígitos) + Complemento (10 dígitos) + Modalidade (2 dígitos).
  * **Nosso Número Livre (17 posições):** Convênio (6 dígitos) + Nosso Número (17 dígitos) + Modalidade fixa `21` (2 dígitos).
* **Cálculo de Dígitos Verificadores:**
  * **Módulo 11:** Calcula o Dígito Verificador Geral (5ª posição do código de barras).
  * **Módulo 10:** Calcula os dígitos verificadores dos três primeiros campos da Linha Digitável.
* **Geração Formatada:** Exibe o Código de Barras de 44 dígitos e a Linha Digitável de 47 dígitos formatada com pontos e espaços.

### 2. Decodificador
* **Leitura Flexível:** Aceita tanto o Código de Barras (44 dígitos) quanto a Linha Digitável (47 dígitos), removendo automaticamente pontos, espaços e tabulações.
* **Verificação de Integridade:** Recalcula e valida os dígitos verificadores (Módulo 10 e Módulo 11) antes de extrair os dados, emitindo alertas caso o código esteja corrompido.
* **Cálculo da Data de Vencimento:** Converte o fator de vencimento de 4 dígitos em uma data real (`DD/MM/AAAA`) utilizando a biblioteca `<ctime>`, com suporte aos dois ciclos da FEBRABAN:
  * **Ciclo 1:** Base em `07/10/1997` (até `21/02/2025`).
  * **Ciclo 2:** Base em `22/02/2025` (fator reiniciado em `1000`).
* **Formatação Monetária:** Converte o campo de valor de 10 dígitos para o formato em Reais (`R$ X,XX`).
* **Identificação Automática de Convênio:** Deduz o tipo de convênio a partir da modalidade (`21`) ou do prefixo de zeros (`000000`), solicitando confirmação do usuário apenas quando há ambiguidade estrutural entre os convênios de 4 e 6 posições.

---

## Estrutura do Código

O projeto foi modularizado em torno da estrutura `dadosDaLinha` e das seguintes funções principais:

| Componente / Função | Descrição |
| :--- | :--- |
| `struct dadosDaLinha` | Armazena os campos do boleto (banco, moeda, vencimento, valor, dados do convênio, código de barras e linha digitável). |
| `menu_principal()` | Gerencia o laço de repetição do menu interativo no terminal. |
| `dv_mod10()` / `dv_mod11()` | Implementam os algoritmos matemáticos da FEBRABAN para cálculo dos dígitos verificadores. |
| `ler_digitos()` | Função utilitária que valida o tamanho exato e garante que a entrada possua apenas dígitos de `0` a `9`. |
| `convenio()` | Coleta os dados específicos de acordo com a opção de convênio escolhida pelo usuário. |
| `montar_campo_livre()` | Concatena e valida os 25 dígitos do campo livre para a geração do boleto. |
| `obter_codigo_barras()` | Converte uma linha digitável de 47 dígitos em um código de barras de 44 dígitos e valida todos os DVs. |
| `recuperar_data()` | Calcula a data de vencimento no calendário a partir do fator numérico e do ciclo informado. |
| `codificador()` | Orquestra o fluxo de leitura, validação e geração do boleto. |
| `decodificador()` | Orquestra a limpeza da entrada, validação de segurança, extração dos campos e exibição do relatório. |

---

## Como Compilar e Executar

### Pré-requisitos e Compatibilidade
* Compilador C++ compatível com o padrão **C++11** ou superior (`g++` ou `clang++`):
  * **Linux:** O `g++` (GCC) já é o compilador padrão na maioria das distribuições.
  * **macOS:** Funciona nativamente com o *Xcode Command Line Tools* instalado (que mapeia o comando `g++` automaticamente para o `clang++`).
  * **Windows:** Compatível via MinGW, MSYS2 ou WSL (gerando automaticamente o executável `boleto.exe`).

### Passo a Passo no Terminal

1. Compile o arquivo-fonte (substitua `main.cpp` pelo nome real do arquivo no repositório, caso seja diferente):
   ```bash
   g++ -std=c++11 main.cpp -o boleto
   ```

2. Execute o programa:
   * **No Linux / macOS:**
     ```bash
     ./boleto
     ```
   * **No Windows (CMD / PowerShell):**
     ```cmd
     boleto.exe
     ```

---

## Caso de Teste (Exemplo de Uso)

### Teste no Codificador (Opção `1`)
* **Código do banco:** `001`
* **Código da moeda:** `9`
* **Vencimento:** `1000`
* **Valor:** `0000015099`
* **Tipo de convênio:** `3` (Convênio de 7 posições)
* **Convênio:** `1234567`
* **Complemento:** `0000000001`
* **Modalidade:** `19`

**Saída Esperada:**
* **Código de Barras:** `00199100000000150990000001234567000000000119`
* **Linha Digitável:** `00190.00009 01234.567004 00000.001192 9 10000000015099`

### Teste no Decodificador (Opção `2`)
* **Entrada:** `00190.00009 01234.567004 00000.001192 9 10000000015099`
* **Ciclo do vencimento:** `2`

**Saída Esperada:**
* **Banco:** `001` | **Moeda:** `9`
* **Fator de Vencimento:** `1000 (22/02/2025)`
* **Valor:** `R$ 150,99 (0000015099)`
* **Tipo de Convênio:** `07 posicoes`
* **Dados do Convênio:** `1234567`
* **Nosso Número:** `12345670000000001`
* **Complemento:** `0000000001` | **Modalidade:** `19`

---

## Autores

* **Erick Matheus da Silva Calixto**
* **Luana Camily Silva Mendonça**
