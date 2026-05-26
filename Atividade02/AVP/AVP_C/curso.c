#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/curso.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"

int inserir_no_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = 0;

    if (*raiz == NULL)
    {
        *raiz = novo_curso;
        inseriu = 1;
    }
    else if (novo_curso->cod_curso < (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->esq), novo_curso);
    else if (novo_curso->cod_curso > (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->dir), novo_curso);

    if (inseriu)
        balancear_RB_curso(raiz);

    return inseriu;
}

int inserir_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = inserir_no_curso(raiz, novo_curso);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}

Curso *aloca_curso(int cod, char *nome, int qtd_blocos, int semanas){
    Curso *curso = (Curso *)malloc(sizeof(Curso));

    if (curso != NULL)
    {
        curso->cod_curso = cod;
        strcpy(curso->nome, nome);

        curso->quantidade_blocos = qtd_blocos;
        curso->semanas_por_disciplina = semanas;

        curso->raiz_disciplinas = NULL;

        curso->cor = RED;
        curso->esq = NULL;
        curso->dir = NULL;
        curso->pai = NULL;
    }

    return curso;
}

Curso *cadastrar_curso(){
    Curso *novo = NULL;
    char *nome;
    int cod, blocos, semanas;
    int ok = 1;

    printf("Digite o codigo do curso: ");
    cod = digitar_int();

    printf("Digite o nome do curso: ");
    nome = ler_string();

    if (nome == NULL)
        ok = 0;

    if (ok){
        printf("Digite a quantidade de blocos: ");
        blocos = digitar_int();

        printf("Digite semanas por disciplina: ");
        semanas = digitar_int();
    }

    if (ok)
        novo = aloca_curso(cod, nome, blocos, semanas);
    else if (nome != NULL)
        free(nome);

    return novo;
}

void rotacao_esquerda_curso(Curso **raiz){
    Curso *aux = (*raiz)->dir;

    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacao_direita_curso(Curso **raiz){
    Curso *aux = (*raiz)->esq;

    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

int cor_aluno(Curso *curso){
    int cor;
    if (curso == NULL)
        cor = BLACK;
    else
        cor = curso->cor;
    return cor;
}

void trocar_cor_curso(Curso *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir)
        raiz->dir->cor = !(raiz->dir->cor);
}

void balancear_RB_curso(Curso **raiz){
    if (*raiz != NULL){
        if (cor_curso((*raiz)->esq) == BLACK && cor_curso((*raiz)->dir) == RED)
            rotacao_esquerda_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->esq->esq) == RED)
            rotacao_direita_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->dir) == RED)
            trocar_cor_curso(*raiz);
    }
}