#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ctype.h>
#include <stdbool.h>
#include "../ABB_H/structs.h"
#include "../ABB_H/auxiliares.h"

char *leitura_de_string(){
    char buffer[256], *string;
    string = NULL;

    // se a leitura de texto do teclado for diferente de nulo
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        //então remova o \n do final da string e coloque \0
        buffer[strcspn(buffer, "\n")] = 0; // o 0 (zero) aqui é o mesmo que \0
        int inicio_string = 0;

        // buffer[i] significa que enquanto nao chegou no fim da string E
        // o caractere é espaço ou tab, incremente i (ou seja, o inicio da string)
        while (buffer[inicio_string] && (buffer[inicio_string] == ' ' || buffer[inicio_string] == '\t'))
            inicio_string++;

        // se o buffer[i] não estiver no final da string
        if(buffer[inicio_string] != '\0'){
            // j aponta para o ultimo caractere valido da string
            int fim_string = strlen(buffer) - 1;
            // enquanto j não chegar ao inicio útil da string E o caractere for espaço OU tab, decremente j (ou seja, volta uma posiçao)
            while(fim_string >= inicio_string && (buffer[fim_string] == ' ' || buffer[fim_string] == '\t'))
                fim_string--;
            // coloca o fim da string (\0) logo após o último caractere válido 
            buffer[fim_string + 1] = '\0';
            string = strdup(buffer + inicio_string); // ignora os espaço do começo da string
            // depois strdup a aloca memoria
            // depois string copia string limpa
        }
    }
    return (string);
}

void limpa_dados_buffer(){
    while(getchar() != '\n');
}

// ---------- Data de Nascimento --------

// essa função vai pegar a data de hoje
void pegar_data_de_hoje (data_nasci *data_hoje){
    //pega o tempo atual em segundos desde 1970
    time_t agora = time(NULL);
    struct tm * time = localtime(&agora); // converte esse tempo para uma struct tm com dia, mes, ano, hora, minutos, segundos, etc...
    data_hoje->dia = time->tm_mday; 
    data_hoje->mes = time->tm_mon + 1; //ficará sendo 1 até 12 meses
    data_hoje->ano = time->tm_year + 1900; // ano desde 1900
}

// Essa função verifica os dias atuais
int dias_de_um_mes(int mes, int ano){
    int dias;

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        dias = 30;
    else if (mes == 2)
        dias = 28;
    else
        dias = 31;

    return dias;
}

// Essa função verifica se a data é válida
int verificar_data(data_nasci *data){
    data_nasci data_de_hoje;
    pegar_data_de_hoje(&data_de_hoje);

    int valida = 1;

    if(data->mes < 1 || data->mes > 12)
        valida = 0;
    else if(data->dia < 1 || data->dia > dias_de_um_mes(data->mes, data->ano))
        valida = 0;
    else if(data->ano < 1900 || data->ano > data_de_hoje.ano)
        valida = 0;
    else if(data->ano == data_de_hoje.ano){
        if(data->mes > data_de_hoje.mes)
            valida = 0;
        else if(data->mes == data_de_hoje.mes && data->dia > data_de_hoje.dia)
            valida = 0;
    }

    return valida;
}

// Função para ler a string da informação
int ler_string_info(char *buffer, int tam){
    // Se NÃO deu certo, recebe 0
    int deu_certo = 0;
    if (fgets(buffer, tam, stdin)){
        // se strchr leu até o final da linha, retorne um ponteiro. 
        // SE NÂO leu, retorne NULL. 
        // Basicamente, vai limpar os dados do buffer caso tenha extrapolado o espaço reservado para aquele ponteiro.
        if(strchr(buffer, '\n') == NULL)
            limpa_dados_buffer();
        else{
            buffer[strcspn(buffer, "\n")] = '\0';
            // Se deu certo, recebe 1
            deu_certo = 1;
        }
    }
    return deu_certo;
}

// Essa função converte a data digitada pelo usuario
// no formato esperado (**/**/****)
int converte_data(const char *entrada, data_nasci *data){
    // Esse função tenta interpretar a string como uma data nesse formato
    return sscanf(entrada, "%2d/%2d/%4d", &data->dia, &data->mes, &data->ano) == 3;
    // Por fim, se conseguiu ler exatamente 3 valores, returna 1 (verdadeiro).
}

// Essa função printa se a data informada deu errado
int validar_data_com_mensagem(data_nasci *data){
    int deu_certo = 1;
    if(!verificar_data(data)){
        limpa_dados_buffer();
        printf("Erro! Data de Nascimento invalida.\n");
        deu_certo = 0;
    }
    return deu_certo;
}

// Essa função pega a data de nascimento do usuário (assinante)
int pega_data_nasci(data_nasci *data_usuario){
    
    char dados_nasci[12];
    int nasci_valido = 0;

    do {
        printf("Entre com os dados da data de nascimento nesse formato (dd/mm/aaaa): ");
        int leu = ler_string_info(dados_nasci, sizeof(dados_nasci));

        if(leu){
            
            int convertido = converte_data(dados_nasci, data_usuario);

            if(convertido){
                nasci_valido = validar_data_com_mensagem(data_usuario);
            }else {
                printf("Erro nos dados! Formato inadequado.\n");
            }
        } else{
            printf("Erro na leitura!\n");
        }
    } while(nasci_valido == 0);
    return nasci_valido;
}

// ------ cpf ----------

// A função valida se o for cpf tiver 11 números, retornando 1 se verdade
int cpf_eh_valido(const char *cpf){
    int valido = 0;

    // se o cpf nao for nulo e tiver 11 caracteres
    if (cpf && strlen(cpf) == 11){
        // assume que tudo é valido
        valido = 1; 

        for (int i = 0; i < 11 && valido; i++){
            if (!isdigit(cpf[i])){
                // se algum caractere não for dígito, então deixa de ser valido
                valido = 0;
            }
        }
    } 
        
    return valido;
}

int pega_cpf(char *cpf){
    
    char dados_cpf[12];
    int cpf_valido = 0;

    do {
        printf("Entre com os dados do cpf nesse formato (xxxxxxxxxxx): ");
        int leu = ler_string_info(dados_cpf, sizeof(dados_cpf));

        if(leu){
            if(cpf_eh_valido(dados_cpf)){
                strcpy(cpf, dados_cpf);
                cpf_valido = 1;
            }else {
                printf("Erro no CPF! O CPF tem que possuir 11 digitos e que sejam numeros.\n");
            }
        } else{
            printf("Erro na leitura!\n");
        }
    } while(!cpf_valido); // enquanto o cpf_valido for igual a zero
    return cpf_valido;
}