#include <stdio.h>
#include <stdlib.h>
#include "arv23_curso.h"
Arv23_Curso *cria_no_CURSO(CURSO info, Arv23_Curso *esq, Arv23_Curso *cen) {
    Arv23_Curso *no = (Arv23_Curso *)malloc(sizeof(Arv23_Curso));
    if (no != NULL) { no->info1 = info; no->nInfo = 1; no->esq = esq; no->cen = cen; no->dir = NULL; }
    return no;
}
int eh_folha_CURSO(Arv23_Curso *no) { return (no != NULL && no->esq == NULL); }
Arv23_Curso *buscar_menor_CURSO(Arv23_Curso *no) {
    Arv23_Curso *at = no; while (at && at->esq) at = at->esq; return at;
}

CURSO *buscar_info_curso(Arv23_Curso *raiz, int codigo) {
    CURSO *ret = NULL;
    if (raiz != NULL) {
        if (raiz->info1.codigo == codigo) ret = &(raiz->info1);
        else if (raiz->nInfo == 2 && raiz->info2.codigo == codigo) ret = &(raiz->info2);
        else if (codigo < raiz->info1.codigo) ret = buscar_info_curso(raiz->esq, codigo);
        else if (raiz->nInfo == 1 || codigo < raiz->info2.codigo) ret = buscar_info_curso(raiz->cen, codigo);
        else ret = buscar_info_curso(raiz->dir, codigo);
    }
    return ret;
}
void adiciona_CURSO(Arv23_Curso **no, CURSO info, Arv23_Curso *sub) {
    Arv23_Curso *at = *no;
    if (info.codigo > at->info1.codigo) { at->info2 = info; at->dir = sub; }
    else { at->info2 = at->info1; at->info1 = info; at->dir = at->cen; at->cen = sub; }
    at->nInfo = 2;
}
Arv23_Curso *quebra_CURSO(Arv23_Curso **no, CURSO info, CURSO *sobe, Arv23_Curso *dir) {
    Arv23_Curso *at = *no; Arv23_Curso *maior = NULL;
    if (info.codigo > at->info2.codigo) { *sobe = at->info2; maior = cria_no_CURSO(info, at->dir, dir); at->nInfo=1; at->dir=NULL; }
    else if (info.codigo > at->info1.codigo) { *sobe = info; maior = cria_no_CURSO(at->info2, dir, at->dir); at->nInfo=1; at->dir=NULL; }
    else { *sobe = at->info1; maior = cria_no_CURSO(at->info2, at->cen, at->dir); at->info1 = info; at->cen = dir; at->nInfo=1; at->dir=NULL; }
    return maior;
}
int insere_rec_CURSO(Arv23_Curso **raiz, CURSO valor, CURSO *sobe, Arv23_Curso **maior) {
    int sucesso = 0; Arv23_Curso *at = *raiz;
    if (at == NULL) { *raiz = cria_no_CURSO(valor, NULL, NULL); *maior = NULL; sucesso = (*raiz != NULL); }
    else if (valor.codigo == at->info1.codigo || (at->nInfo == 2 && valor.codigo == at->info2.codigo)) { *maior = NULL; sucesso = 0; }
    else {
        if (eh_folha_CURSO(at)) {
            if (at->nInfo == 1) { adiciona_CURSO(raiz, valor, NULL); *maior = NULL; sucesso = 1; }
            else { *maior = quebra_CURSO(raiz, valor, sobe, NULL); sucesso = (*maior != NULL); }
        } else {
            Arv23_Curso **prox;
            if (valor.codigo < at->info1.codigo) prox = &(at->esq);
            else if (at->nInfo == 1 || valor.codigo < at->info2.codigo) prox = &(at->cen);
            else prox = &(at->dir);
            int suc_rec = insere_rec_CURSO(prox, valor, sobe, maior);
            if (*maior != NULL) {
                CURSO ch = *sobe; Arv23_Curso *nf = *maior; *maior = NULL;
                if (at->nInfo == 1) { adiciona_CURSO(raiz, ch, nf); sucesso = 1; }
                else { *maior = quebra_CURSO(raiz, ch, sobe, nf); sucesso = (*maior != NULL); }
            } else sucesso = suc_rec;
        }
    }
    return sucesso;
}

int insere_23_CURSO(Arv23_Curso **raiz, CURSO valor) {
    int sucesso = 0; CURSO sobe; Arv23_Curso *maior = NULL;
    if (raiz != NULL) {
        sucesso = insere_rec_CURSO(raiz, valor, &sobe, &maior);
        if (maior != NULL) {
            Arv23_Curso *nova = cria_no_CURSO(sobe, *raiz, maior);
            if (nova) *raiz = nova; else sucesso = 0;
        }
    }
    return sucesso;
}

// ==== DELEÇÃO CURSO ====
StatusRemocao redist_esq(Arv23_Curso **ptr, Arv23_Curso *pai, Arv23_Curso *irm, int pos) {
    Arv23_Curso *f = *ptr; CURSO desce;
    if(pos==1){ desce=pai->info1; pai->info1=irm->info2; }else{ desce=pai->info2; pai->info2=irm->info2; }
    f->info1 = desce; f->nInfo=1; f->esq=irm->dir; f->cen=(f->esq?f->esq:f->cen); f->dir=NULL;
    irm->nInfo=1; irm->dir=NULL; return OK;
}
StatusRemocao redist_dir(Arv23_Curso **ptr, Arv23_Curso *pai, Arv23_Curso *irm, int pos) {
    Arv23_Curso *f = *ptr; CURSO desce;
    if(pos==0){ desce=pai->info1; pai->info1=irm->info1; }else{ desce=pai->info2; pai->info2=irm->info1; }
    f->info1 = desce; f->nInfo=1; f->esq=(f->esq?f->esq:f->cen); f->cen=irm->esq; f->dir=NULL;
    irm->info1=irm->info2; irm->nInfo=1; irm->esq=irm->cen; irm->cen=irm->dir; irm->dir=NULL; return OK;
}
StatusRemocao fundir_esq(Arv23_Curso **ptr, Arv23_Curso *pai, Arv23_Curso *irm, int pos) {
    Arv23_Curso *f = *ptr; CURSO desce; StatusRemocao st = OK;
    Arv23_Curso *rem = (f->esq?f->esq:f->cen);
    if(pai->nInfo==1){ desce=pai->info1; pai->nInfo=0; st=UNDERFLOW; }
    else{ if(pos==1){ desce=pai->info1; pai->info1=pai->info2; }else desce=pai->info2; pai->nInfo=1; }
    irm->info2=desce; irm->nInfo=2; irm->dir=rem;
    if(pos==1){pai->cen=pai->dir; pai->dir=NULL;} else pai->dir=NULL;
    if(st==UNDERFLOW){pai->cen=NULL; pai->dir=NULL;}
    free(f); return st;
}
StatusRemocao fundir_dir(Arv23_Curso **ptr, Arv23_Curso *pai, Arv23_Curso *irm, int pos) {
    Arv23_Curso *f = *ptr; CURSO desce; StatusRemocao st = OK;
    Arv23_Curso *rem = (f->esq?f->esq:f->cen);
    if(pai->nInfo==1){ desce=pai->info1; pai->nInfo=0; st=UNDERFLOW; }
    else{ if(pos==0){ desce=pai->info1; pai->info1=pai->info2; }else desce=pai->info2; pai->nInfo=1; }
    irm->info2=irm->info1; irm->info1=desce; irm->nInfo=2; irm->dir=irm->cen; irm->cen=irm->esq; irm->esq=rem;
    if(pos==0){pai->esq=pai->cen; pai->cen=pai->dir; pai->dir=NULL;} else{pai->cen=pai->dir; pai->dir=NULL;}
    if(st==UNDERFLOW){pai->cen=NULL; pai->dir=NULL;}
    free(f); return st;
}
StatusRemocao under_CURSO(Arv23_Curso **ptr, Arv23_Curso *pai) {
    StatusRemocao st = OK; Arv23_Curso *f = *ptr;
    if(f==NULL || f->nInfo>0) st = OK;
    else if(pai==NULL) st = UNDERFLOW;
    else {
        Arv23_Curso *ie=NULL, *id=NULL; int p = -1;
        if(pai->esq==f){ p=0; id=pai->cen; }
        else if(pai->cen==f){ p=1; ie=pai->esq; if(pai->nInfo==2) id=pai->dir; }
        else { p=2; ie=pai->cen; }
        if(id && id->nInfo==2) st = redist_dir(ptr, pai, id, p);
        else if(ie && ie->nInfo==2) st = redist_esq(ptr, pai, ie, p);
        else if(id && id->nInfo==1) st = fundir_dir(ptr, pai, id, p);
        else if(ie && ie->nInfo==1) st = fundir_esq(ptr, pai, ie, p);
        else st = NAO_FOI_POSSIVEL_T_UNDERFLOW;
    } return st;
}
StatusRemocao rem_rec_CURSO(Arv23_Curso **ptr, int cod) {
    StatusRemocao st = OK; Arv23_Curso *at = *ptr;
    if(!at) st = INFO_NAO_ENCONTRADA;
    else {
        Arv23_Curso **prox=NULL; int achou=0, ind=-1;
        if(cod==at->info1.codigo){ achou=1; ind=0; }
        else if(at->nInfo==2 && cod==at->info2.codigo){ achou=1; ind=1; }
        else if(cod<at->info1.codigo) prox=&(at->esq);
        else if(at->nInfo==1 || cod<at->info2.codigo) prox=&(at->cen);
        else prox=&(at->dir);

        if(achou){
            if(eh_folha_CURSO(at)){
                if(at->nInfo==2){ if(ind==0) at->info1=at->info2; at->nInfo=1; st=OK; }
                else{ at->nInfo=0; st=UNDERFLOW; }
            } else {
                Arv23_Curso *suc=NULL, **psub=NULL;
                if(ind==0){ suc=buscar_menor_CURSO(at->cen); psub=&(at->cen); }
                else{ suc=buscar_menor_CURSO(at->dir); psub=&(at->dir); }
                if(!suc) st=SUCESSOR_NAO_ENCONTRADO;
                else {
                    CURSO vs = suc->info1;
                    if(ind==0) at->info1=vs; else at->info2=vs;
                    StatusRemocao sr = rem_rec_CURSO(psub, vs.codigo);
                    if(sr==UNDERFLOW) st = under_CURSO(psub, at); else st=sr;
                }
            }
        } else {
            StatusRemocao sr = rem_rec_CURSO(prox, cod);
            if(sr==UNDERFLOW) st=under_CURSO(prox, at); else st=sr;
        }
    } return st;
}

StatusRemocao remover_23_CURSO(Arv23_Curso **raiz, int codigo) {
    StatusRemocao st = OK;
    if(!raiz || !*raiz) st = ARVORE_VAZIA;
    else {
        st = rem_rec_CURSO(raiz, codigo);
        if(*raiz && (*raiz)->nInfo==0){
            Arv23_Curso *ant = *raiz; *raiz = ant->esq?ant->esq:ant->cen; free(ant); st=OK;
        }
    } return st;
}

void imprime_23_em_ordem_CURSO(Arv23_Curso *raiz) {
    if (raiz != NULL) {
        imprime_23_em_ordem_CURSO(raiz->esq);
        printf("Curso [%d]: %s (Blocos: %d | Semanas: %d)\n", raiz->info1.codigo, raiz->info1.nome, raiz->info1.qtd_blocos, raiz->info1.semanas);
        imprime_23_em_ordem_CURSO(raiz->cen);
        if (raiz->nInfo == 2) {
            printf("Curso [%d]: %s (Blocos: %d | Semanas: %d)\n", raiz->info2.codigo, raiz->info2.nome, raiz->info2.qtd_blocos, raiz->info2.semanas);
            imprime_23_em_ordem_CURSO(raiz->dir);
        }
    }
}
