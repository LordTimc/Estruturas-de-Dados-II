#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVL_H/structs.h"
#include "../AVL_H/usuarios.h"
#include "../AVL_H/auxiliares.h"
#include "../AVL_H/suporteAVL.h"

Usuario *aloca_assinante (char *cpf, char *nome, char *endereco, Data data_nascimento){ 
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));
    if (novo_usuario != NULL) {
        strcpy(novo_usuario->cpf, cpf);
        strcpy(novo_usuario->nome, nome);
        strcpy(novo_usuario->endereco, endereco);
        novo_usuario->nascimento = data_nascimento;
        
        novo_usuario->altura = 1;
        novo_usuario->esq = NULL;
        novo_usuario->dir = NULL;
    }
    return (novo_usuario);
}

Usuario *cadastrar_assinante(Usuario *usuario) {
    char cpf[12];
    char *nome = NULL;
    char *endereco = NULL; 
    Data nascimento;
    int cadastrou = 0; 

    printf("==== Informacoes do assinante ====");

    if(pega_cpf(cpf)){
        printf("\nDigite o nome: ");
        nome = leitura_de_string();
        
        if(nome != NULL){
            endereco = pega_endereco();    
            if(endereco != NULL && pega_data_nasci(&nascimento)){
                usuario = aloca_assinante(cpf, nome, endereco, nascimento);
                cadastrou = 1;
                free(nome);
                free(endereco);
            }
        }
    }
    if(!cadastrou){
        if(nome) free(nome);
        if(endereco) free(endereco);
    }
    return usuario;
}

int inserir_assinante(Usuario **raiz, Usuario *novo){
    if(*raiz == NULL) {
        *raiz = novo;
        return 1;
    }
    
    int inseriu = 0;
    if(strcmp(novo->cpf, (*raiz)->cpf) == 0){
        free(novo);
        return 0; 
    } else if(strcmp(novo->cpf, (*raiz)->cpf) < 0){
        inseriu = inserir_assinante(&(*raiz)->esq, novo);
    } else {
        inseriu = inserir_assinante(&(*raiz)->dir, novo);
    }
    
    if (!inseriu) return 0;

    // BALANCEAMENTO AVL
    (*raiz)->altura = 1 + maior(altura_usu((*raiz)->esq), altura_usu((*raiz)->dir));
    int fb = fb_usu(*raiz);

    if (fb > 1 && strcmp(novo->cpf, (*raiz)->esq->cpf) < 0)
        *raiz = rot_dir_usu(*raiz);
    else if (fb < -1 && strcmp(novo->cpf, (*raiz)->dir->cpf) > 0)
        *raiz = rot_esq_usu(*raiz);
    else if (fb > 1 && strcmp(novo->cpf, (*raiz)->esq->cpf) > 0) {
        (*raiz)->esq = rot_esq_usu((*raiz)->esq);
        *raiz = rot_dir_usu(*raiz);
    } else if (fb < -1 && strcmp(novo->cpf, (*raiz)->dir->cpf) < 0) {
        (*raiz)->dir = rot_dir_usu((*raiz)->dir);
        *raiz = rot_esq_usu(*raiz);
    }
    return inseriu; 
}

int mostrar_assinantes(Usuario *raiz) {
    int mostrou = 0;
    if (raiz != NULL) {
        mostrou = mostrar_assinantes(raiz->esq);
        printf("--------------------------------------------------\n");
        printf("CPF: %s\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("Endereco: %s\n", raiz->endereco);
        printf("Data de Nascimento: %02d/%02d/%04d\n", raiz->nascimento.dia, raiz->nascimento.mes, raiz->nascimento.ano);
        mostrou = mostrar_assinantes(raiz->dir);
        mostrou = 1;
    }
    return mostrou;
}

int no_sem_filho(Usuario *raiz){
    int eh_folha = 0;
    if(raiz != NULL){
        if(raiz->esq == NULL && raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}

Usuario *so_um_filho(Usuario *r){
    Usuario *no = NULL;
    if(r != NULL){
        if(r->esq == NULL && r->dir != NULL) no = r->dir;
        else if(r->esq != NULL && r->dir == NULL) no = r->esq;
    }
    return(no);
}

int dois_filhos(Usuario *r){
    return (r->esq != NULL && r->dir != NULL);
}

int remove_assinant(Usuario **r, char *cpf) {
    int removeu = 1;
    if (*r == NULL) return 0;

    if (strcmp(cpf, (*r)->cpf) < 0) {
        removeu = remove_assinant(&(*r)->esq, cpf);
    } else if (strcmp(cpf, (*r)->cpf) > 0) {
        removeu = remove_assinant(&(*r)->dir, cpf);
    } else {
        if ((*r)->esq == NULL || (*r)->dir == NULL) {
            Usuario *temp = (*r)->esq ? (*r)->esq : (*r)->dir;
            if (temp == NULL) {
                temp = *r;
                *r = NULL;
            } else {
                **r = *temp; 
            }
            free(temp);
        } else {
            Usuario *temp = (*r)->esq;
            while (temp->dir != NULL) temp = temp->dir;
            strcpy((*r)->cpf, temp->cpf);
            strcpy((*r)->nome, temp->nome);
            strcpy((*r)->endereco, temp->endereco);
            (*r)->nascimento = temp->nascimento;
            removeu = remove_assinant(&(*r)->esq, temp->cpf);
        }
    }

    if (*r == NULL) return removeu;

    // BALANCEAMENTO PÓS-REMOÇÃO AVL
    (*r)->altura = 1 + maior(altura_usu((*r)->esq), altura_usu((*r)->dir));
    int fb = fb_usu(*r);

    if (fb > 1 && fb_usu((*r)->esq) >= 0)
        *r = rot_dir_usu(*r);
    else if (fb > 1 && fb_usu((*r)->esq) < 0) {
        (*r)->esq = rot_esq_usu((*r)->esq);
        *r = rot_dir_usu(*r);
    } else if (fb < -1 && fb_usu((*r)->dir) <= 0)
        *r = rot_esq_usu(*r);
    else if (fb < -1 && fb_usu((*r)->dir) > 0) {
        (*r)->dir = rot_dir_usu((*r)->dir);
        *r = rot_esq_usu(*r);
    }

    return removeu;
}

void liberar_arvore_usuario(Usuario *raiz){
    if (raiz != NULL) {
        liberar_arvore_usuario(raiz->esq);
        liberar_arvore_usuario(raiz->dir);
        free(raiz);
    }
}