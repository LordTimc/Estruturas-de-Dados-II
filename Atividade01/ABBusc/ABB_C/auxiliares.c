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