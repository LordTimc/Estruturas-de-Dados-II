#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVP_H/structs.h"
#include "../AVP_H/cursos.h"
#include "../AVP_H/auxiliares.h"

Curso *inserir_curso(Curso *raiz, int valor){
    int inseriu = 0;

    if (raiz == NULL){
        Curso *novo = (Curso*) malloc(sizeof(Curso));
        if(novo == NULL){
            free(novo);
            inseriu = 0;
        }
        novo->cod_curso = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        
        inseriu = 1;
    }

    if(valor == raiz->cod_curso)
        inseriu = 0;
    else if(valor < raiz->cod_curso){
        raiz->esq = inserir_curso(raiz->esq, valor);
    }else{
        raiz->dir = inserir_curso(raiz->dir, valor);
    }
    if(cor(raiz->dir) == RED && cor(raiz->esq) == BLACK)
        raiz = rota_esq(raiz);

    if(cor(raiz->esq) == RED && cor(raiz->esq->esq) == RED)
        raiz = rota_dir(raiz);
    
    if(cor(raiz->esq) == RED && cor(raiz->dir) == RED)
        troca_cor(raiz);
    
    return inseriu;
}

int insere_ArvVP(Arv_Cursos *raiz, int valor){
    int sucesso = 0;

    *raiz = inserir_curso (*raiz, valor);
    if((*raiz) != NULL){
        (*raiz).raiz->cor = BLACK;
        sucesso = 1;
    }

    return sucesso; 
}