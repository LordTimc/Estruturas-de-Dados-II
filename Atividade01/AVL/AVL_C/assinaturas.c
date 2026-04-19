#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVL_H/structs.h"
#include "../AVL_H/assinantes.h"
#include "../AVL_H/assinaturas.h"
#include "../AVL_H/auxiliares.h"
#include "../AVL_H/suporteAVL.h"

Assinatura* alocar_assinatura(){
    Assinatura *novo = (Assinatura*) malloc(sizeof(Assinatura));
    if (novo != NULL) {
        strcpy(novo->cpf_assinante, "");
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
            strcpy(novo_no->cpf_assinante, cpf_aux);
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
        if(strcmp(novo->cpf_assinante, (*raiz)->cpf_assinante) == 0){
            printf("Aviso: Assinatura ja existente para o CPF %s.\n", novo->cpf_assinante);
            free(novo);
            inseriu = 0;
        } else if(strcmp(novo->cpf_assinante, (*raiz)->cpf_assinante) < 0){
            inseriu = inserir_assinatura(&(*raiz)->esq, novo);
        } else {
            inseriu = inserir_assinatura(&(*raiz)->dir, novo);
        }
    }

    // Apenas balanceia se uma nova inserção realmente ocorreu
    if (inseriu) {
        *raiz = balancear_ass(*raiz);
    }

    return inseriu; 
}

void mostrar_assinaturas(Assinatura *raiz){
    if (raiz != NULL) {
        mostrar_assinaturas(raiz->esq);
        printf("\n-------------------------------------------");
        printf("\nCPF do Assinante: %s", raiz->cpf_assinante);
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
        if (strcmp(cpf, raiz->cpf_assinante) == 0) {
            printf("--------------------------------------------------\n");
            printf("Assinante CPF: %s\n", raiz->cpf_assinante);
            printf("\nData Vencimento:  %02d/%02d/%04d\n", raiz->data_vencimento.dia, raiz->data_vencimento.mes, raiz->data_vencimento.ano);
            printf("--------------------------------------------------\n");
            encontrou = 1; 
        } else if (strcmp(cpf, raiz->cpf_assinante) < 0) {
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->esq, cpf);
        } else {
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->dir, cpf);
        }
    }
    return encontrou;
}


Assinatura* buscar_assinatura(Assinatura *raiz, char *cpf) {
    Assinatura *encontrado = NULL; 

    if (raiz != NULL) {
        if (strcmp(cpf, raiz->cpf_assinante) == 0) {
            encontrado = raiz;
        } else if (strcmp(cpf, raiz->cpf_assinante) < 0) {
            encontrado = buscar_assinatura(raiz->esq, cpf);
        } else {
            encontrado = buscar_assinatura(raiz->dir, cpf);
        }
    }
    
    return encontrado;
}


// --- Funções Auxiliares de Assinatura ---
int eh_folha_assinatura(Assinatura *raiz) {
    int eh_folha = 0;
    if (raiz != NULL) {
        if (raiz->esq == NULL && raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}

Assinatura *so_um_filho_assinatura(Assinatura *r) {
    Assinatura *no = NULL;
    if (r != NULL) {
        if (r->esq == NULL && r->dir != NULL) no = r->dir;
        else if (r->esq != NULL && r->dir == NULL) no = r->esq;
    }
    return no;
}

int dois_filhos_assinatura(Assinatura *r) {
    return (r != NULL && r->esq != NULL && r->dir != NULL);
}

// --- Função de Remoção AVL ---
int remover_no_assinatura(Assinatura **r, char *cpf) {
    int removeu = 0;

    if (*r != NULL) {
        if (strcmp(cpf, (*r)->cpf_assinante) < 0) {
            removeu = remover_no_assinatura(&(*r)->esq, cpf);
        } else if (strcmp(cpf, (*r)->cpf_assinante) > 0) {
            removeu = remover_no_assinatura(&(*r)->dir, cpf);
        } else {
            // Encontrou o nó a ser removido!
            Assinatura *temp = *r;

            // CASO 1: Nó Folha
            if (eh_folha_assinatura(*r)) {
                *r = NULL;
                free(temp);
                removeu = 1; 
            } 
            // CASO 2: Apenas UM filho
            else if (so_um_filho_assinatura(*r) != NULL) {
                *r = so_um_filho_assinatura(*r);
                free(temp);
                removeu = 1; 
            } 
            // CASO 3: Dois filhos
            else if (dois_filhos_assinatura(*r)) {
                temp = (*r)->esq;
                while (temp->dir != NULL) temp = temp->dir;
                
                strcpy((*r)->cpf_assinante, temp->cpf_assinante);
                (*r)->codigo_forma = temp->codigo_forma;
                (*r)->data_assinatura = temp->data_assinatura;
                (*r)->data_vencimento = temp->data_vencimento;
                (*r)->valor = temp->valor;
                
                removeu = remover_no_assinatura(&(*r)->esq, temp->cpf_assinante); 
            }
        }

        // --- MÁGICA DA AVL AQUI ---
        if (*r != NULL && removeu) {
            *r = balancear_ass(*r);
        }
    }
    
    return removeu;
}