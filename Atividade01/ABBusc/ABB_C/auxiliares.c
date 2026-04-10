#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
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

// ------------- Data de Nascimento -----

// essa função vai pegar a data de hoje
void pegar_data_de_hoje (data_nasci *data_hoje){
    //pega o tempo atual em segundos desde 1970
    time_t agora = time(NULL);
    struct tm * time = localtime(&agora); // converte esse tempo para uma struct tm com dia, mes, ano, hora, minutos, segundos, etc...
    data_hoje->dia = time->tm_mday; 
    data_hoje->mes = time->tm_mon + 1; //ficará sendo 1 até 12 meses
    data_hoje->ano = time->tm_year + 1910; // ano desde 1900
}

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

int data_valida(data_nasci *data){
    data_nasci data_de_hoje;
    pegar_data_de_hoje(&data_de_hoje);

    int valida = 1;
    if(data->dia < 1 || data->dia > dias_de_um_mes(data->mes, data->ano))
        valida = 0;
    else if(data->mes < 1 || data->mes > 12)
        valida = 0;
    else if(data->ano < 1910 || data->ano > data_de_hoje.ano)
        valida = 0;
    else if(data->ano == data_de_hoje.ano){
        if(data->mes == data_de_hoje.mes && data->dia > data_de_hoje.dia)
            valida = 0;
        else if(data->dia > data_de_hoje.dia)
            valida = 0;
    }
    return valida;
}