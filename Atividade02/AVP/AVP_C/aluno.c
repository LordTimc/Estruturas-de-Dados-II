#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/aluno.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"


/*---------------------------- Funções Arv Red Black ----------------------------*/

// =================================
// INSERCAO
// =================================

int inserir_no_aluno(Aluno **raiz, Aluno *novo_aluno){
    int inseriu = 0;

    if (*raiz == NULL)
    {
        *raiz = novo_aluno;
        inseriu = 1;
    }
    else if (strcasecmp(novo_aluno->nome, (*raiz)->nome) < 0)
        inseriu = inserir_no_aluno(&((*raiz)->esq), novo_aluno);
    else if (strcasecmp(novo_aluno->nome, (*raiz)->nome) > 0)
        inseriu = inserir_no_aluno(&((*raiz)->dir), novo_aluno);

    if (inseriu)
        balancear_RB_aluno(raiz);

    return inseriu;
}

int inserir_aluno(Aluno **raiz, Aluno *novo_aluno){
    int inseriu;
    inseriu = inserir_no_aluno(raiz, novo_aluno);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}

Aluno *aloca_aluno(char *nome_aluno, int mat, int codigo, int ano, int semestre){
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

    strcpy(aluno->nome, nome_aluno);
    aluno->matricula = mat;
    aluno->codigo_Curso = codigo;
    aluno->ano_Ingresso = ano;
    aluno->semestre_Ingresso = semestre;

    aluno->cor = RED;
    aluno->esq = NULL;
    aluno->dir = NULL;

    return aluno;
}

Aluno *cadastrar_aluno(){
    Aluno *novo_aluno = NULL;
    char *nome;
    int matricula = 0, codigo = 0, ano = 0, semestre = 0, cadastrou = 0;

    printf("Digite a matricula do aluno: ");
    matricula = digitar_int();
    
    if (matricula){
        printf("Digite o nome do aluno: ");
        nome = ler_string();

        if(nome != NULL){
            printf("Digite a codigo o curso do aluno: ");
            codigo = digitar_int();

            if(codigo != NULL){
                ano = digitar_int();

                if(ano != NULL){
                    semestre = digitar_int();

                    cadastrou = 1;
                }
            }
        }
    }

    if (cadastrou)
        novo_aluno = aloca_Aluno(nome, matricula, codigo, ano, semestre);
    else{
        if (nome != NULL)
            free(nome);
    }

    return novo_aluno;
}

void rotacao_esquerda_aluno(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacao_direita_aluno(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

int cor_aluno(Aluno *aluno){
    int cor;
    if (aluno == NULL)
        cor = BLACK;
    else
        cor = aluno->cor;
    return cor;
}

void trocar_cor_aluno(Aluno *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq != NULL)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir != NULL)
        raiz->dir->cor = !(raiz->dir->cor);
}

void balancear_RB_aluno(Aluno **raiz){
    if (*raiz != NULL){
        if (Cor_aluno((*raiz)->esq) == BLACK && Cor_aluno((*raiz)->dir) == RED)
            rotacao_esquerda_aluno(raiz);

        if (Cor_aluno((*raiz)->esq) == RED && Cor_aluno((*raiz)->esq->esq) == RED)
            rotacao_direita_aluno(raiz);

        if (Cor_aluno((*raiz)->esq) == RED && Cor_aluno((*raiz)->dir) == RED)
            trocar_cor_aluno(*raiz);
    }
}

// Função auxiliar para imprimir informações de uma aluno
void imprimir_aluno(Aluno *aluno){
    if (aluno != NULL){
        printf("------------------------\n");
        printf("NOME: %s\n", aluno->nome);
        printf("Matricula: %d\n", aluno->matricula);
        printf("Codigo do curso: %d\n", aluno->codigo_Curso);
        printf("Ano de ingresso: %d\n", aluno->ano_Ingresso);
        printf("Semestre de ingresso: %d\n", aluno->semestre_Ingresso);
        printf("------------------------\n");
    }
}