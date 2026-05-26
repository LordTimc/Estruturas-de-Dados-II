#include <stdio.h>
#include <stdlib.h>
#include "arv23_aluno.h"
Arv23_Aluno *cria_no_ALUNO(ALUNO info, Arv23_Aluno *esq, Arv23_Aluno *cen) {
    Arv23_Aluno *no = (Arv23_Aluno *)malloc(sizeof(Arv23_Aluno));
    if (no) { no->info1 = info; no->nInfo = 1; no->esq = esq; no->cen = cen; no->dir = NULL; }
    return no;
}
int eh_folha_ALUNO(Arv23_Aluno *no) { return (no != NULL && no->esq == NULL); }
void adiciona_ALUNO(Arv23_Aluno **no, ALUNO info, Arv23_Aluno *sub) {
    Arv23_Aluno *at = *no;
    if (info.matricula > at->info1.matricula) { at->info2 = info; at->dir = sub; }
    else { at->info2 = at->info1; at->info1 = info; at->dir = at->cen; at->cen = sub; }
    at->nInfo = 2;
}
Arv23_Aluno *quebra_ALUNO(Arv23_Aluno **no, ALUNO info, ALUNO *sobe, Arv23_Aluno *dir) {
    Arv23_Aluno *at = *no; Arv23_Aluno *maior = NULL;
    if (info.matricula > at->info2.matricula) { *sobe = at->info2; maior = cria_no_ALUNO(info, at->dir, dir); at->nInfo=1; at->dir=NULL; }
    else if (info.matricula > at->info1.matricula) { *sobe = info; maior = cria_no_ALUNO(at->info2, dir, at->dir); at->nInfo=1; at->dir=NULL; }
    else { *sobe = at->info1; maior = cria_no_ALUNO(at->info2, at->cen, at->dir); at->info1 = info; at->cen = dir; at->nInfo=1; at->dir=NULL; }
    return maior;
}
int insere_rec_ALUNO(Arv23_Aluno **raiz, ALUNO valor, ALUNO *sobe, Arv23_Aluno **maior) {
    int sucesso = 0; Arv23_Aluno *at = *raiz;
    if (at == NULL) { *raiz = cria_no_ALUNO(valor, NULL, NULL); *maior = NULL; sucesso = (*raiz != NULL); }
    else if (valor.matricula == at->info1.matricula || (at->nInfo == 2 && valor.matricula == at->info2.matricula)) { *maior = NULL; sucesso = 0; }
    else {
        if (eh_folha_ALUNO(at)) {
            if (at->nInfo == 1) { adiciona_ALUNO(raiz, valor, NULL); *maior = NULL; sucesso = 1; }
            else { *maior = quebra_ALUNO(raiz, valor, sobe, NULL); sucesso = (*maior != NULL); }
        } else {
            Arv23_Aluno **prox;
            if (valor.matricula < at->info1.matricula) prox = &(at->esq);
            else if (at->nInfo == 1 || valor.matricula < at->info2.matricula) prox = &(at->cen);
            else prox = &(at->dir);
            int suc_rec = insere_rec_ALUNO(prox, valor, sobe, maior);
            if (*maior != NULL) {
                ALUNO ch = *sobe; Arv23_Aluno *nf = *maior; *maior = NULL;
                if (at->nInfo == 1) { adiciona_ALUNO(raiz, ch, nf); sucesso = 1; }
                else { *maior = quebra_ALUNO(raiz, ch, sobe, nf); sucesso = (*maior != NULL); }
            } else sucesso = suc_rec;
        }
    }
    return sucesso;
}

int insere_23_ALUNO(Arv23_Aluno **raiz, ALUNO valor) {
    int sucesso = 0; ALUNO sobe; Arv23_Aluno *maior = NULL;
    if (raiz != NULL) {
        sucesso = insere_rec_ALUNO(raiz, valor, &sobe, &maior);
        if (maior != NULL) {
            Arv23_Aluno *nova = cria_no_ALUNO(sobe, *raiz, maior);
            if (nova) *raiz = nova; else sucesso = 0;
        }
    }
    return sucesso;
}
