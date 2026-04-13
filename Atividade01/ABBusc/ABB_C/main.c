#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ABB_H/usuarios.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/formaAssinat.h"
#include "../ABB_H/generos.h"
#include "../ABB_H/livros.h"

#include "../ABB_H/structs.h"
#include "../ABB_H/auxiliares.h"

void menu_das_opcoes(){
    printf("\n 1 - Cadastrar Assinantes\n");
    printf("\n 2 - Cadastrar Forma de Assinaturas\n");
    printf("\n 3 - Cadastrar Assinaturas\n");
    printf("\n 4 - Cadastrar Generos\n");
    printf("\n 5 - Cadastrar Livros\n");
    printf("\n 6 - Mostrar todos assinantes cadastrados\n");
    printf("\n 7 - Mostrar todas as assinaturas cadastrada\n");
    printf("\n 8 - Mostrar todas as assinaturas de um determinada forma\n");
    printf("\n 9 - Mostrar todas as formas cadastradas e seus respectivos valores mensais e anuais\n");
    printf("\n 10 - Mostrar todos os generos cadastrados\n");
    printf("\n 11 - Mostrar todos os generos assinados\n");
    printf("\n 12 - Mostrar todos os livros de um determinado gênero\n");
    printf("\n 13 - Mostrar data de vencimento de uma assinatura\n");
    printf("\n 14 - Remover uma assinatura dado o CPF do assinante\n");
    printf("\n 15 - Remover um assinante pelo CPF do assinante\n");
    printf("\n 0 - Finalizar tudo\n");
}

void menu(){
    
}