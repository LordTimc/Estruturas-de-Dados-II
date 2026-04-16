#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <ctype.h>
#include <stdbool.h>

#include "../AVL_H/structs.h"
#include "../AVL_H/auxiliares.h"

char *leitura_de_string(){
    char buffer[256], *string;
    string = NULL;
    if(fgets(buffer, sizeof(buffer), stdin) != NULL){
        buffer[strcspn(buffer, "\n")] = 0; 
        int inicio_string = 0;
        while (buffer[inicio_string] && (buffer[inicio_string] == ' ' || buffer[inicio_string] == '\t'))
            inicio_string++;
        if(buffer[inicio_string] != '\0'){
            int fim_string = strlen(buffer) - 1;
            while(fim_string >= inicio_string && (buffer[fim_string] == ' ' || buffer[fim_string] == '\t'))
                fim_string--;
            buffer[fim_string + 1] = '\0';
            string = strdup(buffer + inicio_string); 
        }
    }
    return (string);
}

void limpa_dados_buffer(){
    while(getchar() != '\n');
}

void pegar_data_de_hoje (Data *data_hoje){
    time_t agora = time(NULL);
    struct tm * time = localtime(&agora); 
    data_hoje->dia = time->tm_mday; 
    data_hoje->mes = time->tm_mon + 1; 
    data_hoje->ano = time->tm_year + 1900; 
}

int dias_de_um_mes(int mes, int ano){
    int dias;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) dias = 30;
    else if (mes == 2) dias = 28;
    else dias = 31;
    return dias;
}

int verificar_data(Data *data){
    Data data_de_hoje;
    pegar_data_de_hoje(&data_de_hoje);
    int valida = 1;
    if(data->mes < 1 || data->mes > 12) valida = 0;
    else if(data->dia < 1 || data->dia > dias_de_um_mes(data->mes, data->ano)) valida = 0;
    else if(data->ano < 1900 || data->ano > data_de_hoje.ano) valida = 0;
    else if(data->ano == data_de_hoje.ano){
        if(data->mes > data_de_hoje.mes) valida = 0;
        else if(data->mes == data_de_hoje.mes && data->dia > data_de_hoje.dia) valida = 0;
    }
    return valida;
}

int ler_string_info(char *buffer, int tam){
    int deu_certo = 0;
    if (fgets(buffer, tam, stdin)){
        if(strchr(buffer, '\n') == NULL)
            limpa_dados_buffer();
        else{
            buffer[strcspn(buffer, "\n")] = '\0';
            deu_certo = 1;
        }
    }
    return deu_certo;
}

int converte_data(const char *entrada, Data *data){
    return sscanf(entrada, "%2d/%2d/%4d", &data->dia, &data->mes, &data->ano) == 3;
}

int validar_data_com_mensagem(Data *data){
    int deu_certo = 1;
    if(!verificar_data(data)){
        // limpa_dados_buffer(); -> Removido pois pode travar a tela esperando Enter
        printf("Erro! Data invalida.\n");
        deu_certo = 0;
    }
    return deu_certo;
}

int pega_data_nasci(Data *data_usuario){
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
            printf("Erro na leitura da data de nascimento!\n");
        }
    } while(!nasci_valido); 
    return nasci_valido;
}

int pega_data(Data *data_usuario){
    char dados[12];
    int valido = 0;
    do {
        printf("Entre com os dados da data nesse formato (dd/mm/aaaa): ");
        int leu = ler_string_info(dados, sizeof(dados));
        if(leu){
            int convertido = converte_data(dados, data_usuario);
            if(convertido){
                valido = validar_data_com_mensagem(data_usuario);
            }else {
                printf("Erro nos dados! Formato inadequado.\n");
            }
        } else{
            printf("Erro na leitura da data!\n");
        }
    } while(!valido); 
    return valido;
}

int cpf_eh_valido(const char *cpf){
    int valido = 0;
    if (cpf && strlen(cpf) == 11){
        valido = 1; 
        for (int i = 0; i < 11 && valido; i++){
            if (!isdigit(cpf[i])){
                valido = 0;
            }
        }
    } 
    return valido;
}

int pega_cpf(char *cpf){
    char dados_cpf[15];
    int cpf_valido = 0;
    do {
        printf("Entre com o CPF (11 digitos numericos): ");
        int leu = ler_string_info(dados_cpf, sizeof(dados_cpf));
        if(leu){
            if(cpf_eh_valido(dados_cpf)){
                strcpy(cpf, dados_cpf);
                cpf_valido = 1;
            }else {
                printf("Erro! O CPF deve possuir exatamente 11 digitos numericos.\n");
            }
        } else{
            printf("Erro na leitura do cpf!\n");
        }
    } while(!cpf_valido); 
    return cpf_valido;
}

int endereco_eh_valido(const char *ender){
    return (ender && strlen(ender) > 0);
}

char *pega_endereco() {
    char *ender = NULL;
    do {
        printf("Entre com o nome da rua: ");
        ender = leitura_de_string();
        if (ender != NULL) {
            if (endereco_eh_valido(ender)) {
                return ender; 
            } else {
                printf("Erro! O endereco nao pode ser vazio.\n");
                free(ender); 
            }
        } else {
            printf("Erro na leitura do endereco\n");
        }
    } while (1);
}

int num_eh_valido(const char *num){
    int valido = 0;
    if (num && strlen(num) == 2){
        valido = 1; 
        for (int i = 0; i < strlen(num) && valido; i++){
            if (!isdigit(num[i])){
                valido = 0;
            }
        }
    }  
    return valido;
}

int pega_isbn(char *codigo){
    char dados_isbn[5];
    int isbn_valido = 0;
    do {
        printf("Entre com o codigo do isbn nesse formato (xx): ");
        int leu = ler_string_info(dados_isbn, sizeof(dados_isbn));
        if(leu){
            if(num_eh_valido(dados_isbn)){
                strcpy(codigo, dados_isbn);
                isbn_valido = 1;
            }else {
                printf("Erro! O codigo tem que possuir 2 digitos numericos.\n");
            }
        } else{
            printf("Erro na leitura do codigo do isbn!\n");
        }
    } while(!isbn_valido); 
    return isbn_valido;
}

int num_inteiro(){
    int inteiro = 0;
    while (scanf("%d", &inteiro) != 1 || inteiro < 0)
    {
        printf("Numero invalido. Digite novamente: ");
        limpa_dados_buffer();
    }
    limpa_dados_buffer();
    return inteiro;
}

float num_decimal(){
    float decimal = 0;
    while (scanf("%f", &decimal) != 1 || decimal < 0)
    {
        printf("Numero invalido. Digite novamente: ");
        limpa_dados_buffer();
    }
    limpa_dados_buffer();
    return decimal;
}