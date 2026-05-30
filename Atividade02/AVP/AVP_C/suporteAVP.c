#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVP_H/structs.h"
#include "../AVP_H/suporteAVP.h"

// ========================
// ALUNO
// ========================

// ROTACOES

// Realiza rotação à esquerda na árvore
void rotacao_esq_aluno(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

// Realiza rotação à direita na árvore
void rotacao_dir_aluno(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}


// CONTROLE DAS CORES

// Retorna a cor do nó
// Se o nó for NULL, considera como preto
int cor_aluno(Aluno *aluno){
    int cor;
    if (aluno == NULL)
        cor = BLACK;
    else
        cor = aluno->cor;
    return cor;
}

// Inverte a cor do nó e de seus filhos
void troca_cor_aluno(Aluno *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq != NULL)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir != NULL)
        raiz->dir->cor = !(raiz->dir->cor);
}

// BALANCEAMENTO

// Realiza o balanceamento da árvore rubro-negra após inserção ou remoção
void balancea_VP_aluno(Aluno **raiz){
    if (*raiz != NULL){
        if (cor_aluno((*raiz)->esq) == BLACK && cor_aluno((*raiz)->dir) == RED)
            rotacao_esq_aluno(raiz);

        if (cor_aluno((*raiz)->esq) == RED && cor_aluno((*raiz)->esq->esq) == RED)
            rotacao_dir_aluno(raiz);

        if (cor_aluno((*raiz)->esq) == RED && cor_aluno((*raiz)->dir) == RED)
            troca_cor_aluno(*raiz);
    }
}


// ========================
// CURSO
// ========================

// ROTACOES

// Realiza rotação à esquerda na árvore
void rotacao_esq_curso(Curso **raiz){
    Curso *aux = (*raiz)->dir;

    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

// Realiza rotação à direita na árvor
void rotacao_dir_curso(Curso **raiz){
    Curso *aux = (*raiz)->esq;

    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

// CONTROLE DAS CORES

// Retorna a cor do nó
// Se o nó for NULL, considera como preto
int cor_curso(Curso *curso){
    int cor;
    if (curso == NULL)
        cor = BLACK;
    else
        cor = curso->cor;
    return cor;
}

// Inverte a cor do nó e de seus filhos
void troca_cor_curso(Curso *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir)
        raiz->dir->cor = !(raiz->dir->cor);
}

// BALANCEAMENTO

// Realiza o balanceamento da árvore rubro-negra após inserção ou remoção
void balancea_VP_curso(Curso **raiz){
    if (*raiz != NULL){
        if (cor_curso((*raiz)->esq) == BLACK && cor_curso((*raiz)->dir) == RED)
            rotacao_esq_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->esq->esq) == RED)
            rotacao_dir_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->dir) == RED)
            troca_cor_curso(*raiz);
    }
}

// ========================
// DISPLINAS
// ========================

// ROTAÇÕES

// Realiza rotação à esquerda na árvore
void rotacao_esq_disciplina(Disciplina **raiz){
    Disciplina *aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

// Realiza rotação à direita na árvore
void rotacao_dir_disciplina(Disciplina **raiz){
    Disciplina *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

// CONTROLE DE CORES

// Retorna a cor do nó
// Se o nó for NULL, considera como preto
int cor_disciplina(Disciplina *aluno){
    int cor;
    if (aluno == NULL)
        cor = BLACK;
    else
        cor = aluno->cor;
    return cor;
}

// Inverte a cor do nó e de seus filhos
void troca_cor_disciplina(Disciplina *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq != NULL)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir != NULL)
        raiz->dir->cor = !(raiz->dir->cor);
}

// BALANCEAMENTO

// Realiza o balanceamento da árvore rubro-negra após inserção ou remoção
void balancea_VP_disciplina(Disciplina **raiz){
    if(*raiz != NULL){
        if(cor_disciplina((*raiz)->dir) == RED && cor_disciplina((*raiz)->esq) == BLACK)
            rotacao_esq_disciplina(raiz);

        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->esq->esq) == RED)
            rotacao_dir_disciplina(raiz);
    
        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->dir) == RED)
            troca_cor_disciplina(*raiz);
    }
}