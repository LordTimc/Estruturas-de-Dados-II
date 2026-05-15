#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVP_H/structs.h"
#include "../AVP_H/disciplinas.h"
#include "../AVP_H/auxiliares.h"

// Função para alocar um novo curso
Disciplina *alocou_disciplina(int *codigo, char *nome, int *bloco, int *ch){

    // Inicializa novo ponteiro
    Disciplina *novo = (Disciplina*) malloc(sizeof(Disciplina));
    
    novo->cod_disciplina = codigo;
    strcpy(novo->nome, nome);
    novo->bloco = bloco;
    novo->carga_horaria = ch;

    novo->cor = RED;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

Disciplina *cadastrou_disciplina(){
    int cadastrou = 0;

    Disciplina *disciplina;
    int cod_displina;
    char *nome_displina;
    int bloco;
    int carga_horaria;

    disciplina = NULL;
    nome_displina = NULL;

    printf("Entre com o nome da nova disciplina: ");
    nome_displina = leitura_de_string();

    if(nome_displina != NULL){
        cadastrou = pega_cod(cod_displina);
        if(cadastrou){
            // Fazer a alocação de memória de disciplina
            disciplina = alocou_disciplina(cod_displina, nome_displina, bloco, carga_horaria);
        }
    }

    // Caso falhe
    if(!cadastrou){
        if(nome_displina != NULL){
            free(nome_displina);
        }
    }
    return disciplina;
}

int *inseriu_no_disciplina(Disciplina **raiz, Disciplina *novo){
    int inseriu = 0;

    if (raiz == NULL){
        *raiz = novo;
        inseriu = 1;
    }
    else if(novo < (*raiz)->cod_disciplina){
        inseriu = inserir_disciplina(&((*raiz)->esq), novo);
    }else{
        inseriu = inserir_disciplina(&((*raiz)->dir), novo);
    }

    if(inseriu){
        balancear_VP_disciplina(raiz);
    }

    return inseriu;
}

int inseriu_disciplina(Disciplina **raiz, Disciplina *nova){
    int sucesso = 0;

    sucesso = inseriu_no_disciplina(*raiz, nova);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return sucesso; 
}

void balancear_VP_disciplina(Disciplina **raiz){
    if(*raiz != NULL){
        if(cor_disciplina((*raiz)->dir) == RED && cor_disciplina((*raiz)->esq) == BLACK)
            rota_esq_disciplina(raiz);

        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->esq->esq) == RED)
            rota_dir_disciplina(raiz);
    
        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->dir) == RED)
            troca_cor_disciplina(*raiz);
    }
}