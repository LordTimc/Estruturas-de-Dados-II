#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVL_H/structs.h"
#include "../AVL_H/usuarios.h"
#include "../AVL_H/assinaturas.h"
#include "../AVL_H/auxiliares.h"
#include "../AVL_H/suporteAVL.h"

Assinatura* alocar_assinatura(){
    Assinatura *novo = (Assinatura*) malloc(sizeof(Assinatura));
    if (novo != NULL) {
        strcpy(novo->cpf_usuario, "");
        novo->codigo_forma = 0;
        novo->valor = 0.0;
        novo->altura = 1; 
        novo->esq = NULL;
        novo->dir = NULL;
    } else {
        printf("Erro! Falha na alocacao de memoria para Assinatura.\n");
    }
    return novo; 
}

void cadastrar_assinatura(Assinatura **r){
    char cpf_aux[12];
    int cadastrou = 0;
    Assinatura *novo_no = NULL;

    printf("\n--- Nova Assinatura ---\n");

    if (pega_cpf(cpf_aux)) {
        novo_no = alocar_assinatura();
        if (novo_no != NULL) {
            strcpy(novo_no->cpf_usuario, cpf_aux);
            printf("Digite o codigo da forma de assinatura: ");
            novo_no->codigo_forma = num_inteiro();

            printf("Data de Inicio da assinatura:\n");
            if (pega_data(&novo_no->data_assinatura)) {
                printf("Data de Vencimento da assinatura:\n");
                if (pega_data(&novo_no->data_vencimento)) {
                    printf("Valor da Assinatura: ");
                    novo_no->valor = num_decimal();
                    cadastrou = 1;
                }
            }
        }
    }

    if (cadastrou) {
        if (inserir_assinatura(r, novo_no)) {
            printf("Assinatura realizada com sucesso!\n");
        } else {
            printf("Erro: Nao foi possivel inserir na arvore.\n");
        }
    } else {
        if (novo_no != NULL) free(novo_no);
        printf("Cadastro cancelado ou dados invalidos.\n");
    }
}

int inserir_assinatura(Assinatura **raiz, Assinatura *novo){
    int inseriu = 1;

    if (*raiz == NULL) {
        *raiz = novo;
    }else{
        if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) == 0){
            printf("Aviso: Assinatura ja existente para o CPF %s.\n", novo->cpf_usuario);
            free(novo);
        } else if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) < 0){
            inseriu = inserir_assinatura(&(*raiz)->esq, novo);
        } else {
            inseriu = inserir_assinatura(&(*raiz)->dir, novo);
        }
    }

    if (!inseriu) return 0;

    // BALANCEAMENTO AVL
    (*raiz)->altura = 1 + maior(altura_ass((*raiz)->esq), altura_ass((*raiz)->dir));
    int fb = fb_ass(*raiz);

    if (fb > 1 && strcmp(novo->cpf_usuario, (*raiz)->esq->cpf_usuario) < 0)
        *raiz = rot_dir_ass(*raiz);
    else if (fb < -1 && strcmp(novo->cpf_usuario, (*raiz)->dir->cpf_usuario) > 0)
        *raiz = rot_esq_ass(*raiz);
    else if (fb > 1 && strcmp(novo->cpf_usuario, (*raiz)->esq->cpf_usuario) > 0) {
        (*raiz)->esq = rot_esq_ass((*raiz)->esq);
        *raiz = rot_dir_ass(*raiz);
    } else if (fb < -1 && strcmp(novo->cpf_usuario, (*raiz)->dir->cpf_usuario) < 0) {
        (*raiz)->dir = rot_dir_ass((*raiz)->dir);
        *raiz = rot_esq_ass(*raiz);
    }

    return inseriu; 
}

void mostrar_assinaturas(Assinatura *raiz){
    if (raiz != NULL) {
        mostrar_assinaturas(raiz->esq);
        printf("\n-------------------------------------------");
        printf("\nCPF do Assinante: %s", raiz->cpf_usuario);
        printf("\nCodigo da Forma:  %d", raiz->codigo_forma);
        printf("\nData Assinatura:  %02d/%02d/%04d", raiz->data_assinatura.dia, raiz->data_assinatura.mes, raiz->data_assinatura.ano);
        printf("\nData Vencimento:  %02d/%02d/%04d\n", raiz->data_vencimento.dia, raiz->data_vencimento.mes, raiz->data_vencimento.ano);
        printf("\nValor:            R$ %.2f", raiz->valor);
        printf("\n-------------------------------------------");
        mostrar_assinaturas(raiz->dir);
    }
}

int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf){
    int encontrou = 0;
    if (raiz != NULL) {
        if (strcmp(cpf, raiz->cpf_usuario) == 0) {
            printf("--------------------------------------------------\n");
            printf("Assinante CPF: %s\n", raiz->cpf_usuario);
            printf("\nData Vencimento:  %02d/%02d/%04d\n", raiz->data_vencimento.dia, raiz->data_vencimento.mes, raiz->data_vencimento.ano);
            printf("--------------------------------------------------\n");
            encontrou = 1; 
        } else if (strcmp(cpf, raiz->cpf_usuario) < 0) {
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->esq, cpf);
        } else {
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->dir, cpf);
        }
    }
    return encontrou;
}