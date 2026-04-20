#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVL_H/structs.h"
#include "../AVL_H/assinantes.h"
#include "../AVL_H/auxiliares.h"
#include "../AVL_H/suporteAVL.h"

// Função para alocar um novo assinante
Assinante *aloca_assinante (){ 
    Assinante *novo_assinante = (Assinante *)malloc(sizeof(Assinante));
    if (novo_assinante != NULL) {
        // Inicialização de strings
        strcpy(novo_assinante->cpf, "");
        strcpy(novo_assinante->nome, "");
        strcpy(novo_assinante->endereco, "");

        // Inicialização de struct interna
        novo_assinante->nascimento.dia = 0;
        novo_assinante->nascimento.mes = 0;
        novo_assinante->nascimento.ano = 0;
        
        // Inicialização da altura
        novo_assinante->altura = 1;

        // Inicialização da árvore
        novo_assinante->esq = NULL;
        novo_assinante->dir = NULL;
    }else {
        printf("Erro! Falha na alocacao de memoria para Assinante.\n");
    }
    return (novo_assinante);
}

// Função para cadastrar um novo assinante na árvore binária
void *cadastrar_assinante(Assinante **r) {
    char cpf[12];
    char *nome = NULL;
    char *endereco = NULL; 
    Data nascimento;
    int cadastrou = 0;
    Assinante *novo_no = NULL; 

    printf("==== Informacoes do assinante ====");

    if(pega_cpf(cpf)){
        novo_no = alocar_assinante();
        
        printf("\nDigite o nome: ");
        nome = leitura_de_string();
        
        if(nome != NULL){
            endereco = pega_endereco();
            
            if(endereco != NULL && pega_data_nasci(&nascimento)){
                
                // Preenchimento do nó
                strcpy(novo_no->cpf, cpf);
                strcpy(novo_no->nome, nome);
                strcpy(novo_no->endereco, endereco);
                novo_no->nascimento = nascimento;

                cadastrou = 1;
            }
        }
    }
    if (cadastrou) {
        if (inserir_assinante(&(*r), novo_no)) {
            printf("Assinante cadastrado com sucesso!\n");
        } else {
            printf("Erro: Nao foi possivel inserir na arvore.\n");
        }
    } else {
        if (novo_no != NULL) free(novo_no);
        printf("Cadastro de assinante cancelado ou dados invalidos.\n");
    }

    // Liberação de memória auxiliar
    if (nome) free(nome);
    if (endereco) free(endereco);
}

/* **raiz: Ponteiro duplo para a raiz da árvore. Escolhido (passagem por referência), pois precisamos modificar o ponteiro real da árvore no `main` quando alocamos um novo nó.*/
int inserir_assinante(Assinante **raiz, Assinante *novo){
    int inseriu = 0;

    // Verifica se chegamos em um nó folha/vazio
    if(*raiz == NULL) {
        *raiz = novo;
        inseriu = 1;
    } else {
        if(strcmp(novo->cpf, (*raiz)->cpf) == 0){
            // A função strcmp compara os dois CPFs. Retorna < 0 se a primeira for menor, > 0 se for maior, e 0 se forem iguais.
            // comparacao == 0 significa que o CPF já existe na árvore
            // Não permite cadastro repetido, logo, o inseriu se mantém 0 (falha)
            free(novo);
            inseriu = 0; 
        } else if(strcmp(novo->cpf, (*raiz)->cpf) < 0){
            // Se a árvore não está vazia e o CPF é "menor", vai para a subárvore esquerda.
            inseriu = inserir_assinante(&(*raiz)->esq, novo);
        } else {
            // Se o CPF é "maior", vai para a subárvore direita
            inseriu = inserir_assinante(&(*raiz)->dir, novo);
        }

        // Se inseriu com sucesso, faz o balanceamento
        if (inseriu) {
            *raiz = balancear_assinante(*raiz);
        }
    }
    
    return inseriu; 
}

/* Percorre a árvore binária de assinantes utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenados pelo CPF.
 
 * Parâmetros:
 * - Assinante *raiz: Ponteiro simples para a raiz da árvore. Escolhemos a passagem 
 * por valor (cópia do ponteiro) porque esta função serve apenas para LEITURA. 
 * Não vamos inserir ou remover nós, logo, não precisamos modificar a árvore original.
*/
int mostrar_assinantes(Assinante *raiz) {
    int mostrou = 0;

    // Verifica se o nó atual não é nulo
    if (raiz != NULL) {

        // 1º Passo: Desce tudo que pode para a subárvore esquerda (CPFs menores)
        mostrou = mostrar_assinantes(raiz->esq);

        // 2º Passo: Visita a "raiz" atual (Imprime os dados do usuário)
        printf("--------------------------------------------------\n");
        printf("CPF: %s\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("Endereco: %s\n", raiz->endereco);
        printf("Data de Nascimento: %02d/%02d/%04d\n", raiz->nascimento.dia, raiz->nascimento.mes, raiz->nascimento.ano);

        // 3º Passo: Desce para a subárvore direita (CPFs maiores)
        mostrou = mostrar_assinantes(raiz->dir);
        mostrou = 1;
    }
    return mostrou;
}

// ---------- Remoção ------------

int eh_folha(Assinante *raiz){
    int eh_folha = 0;
    if(raiz != NULL){
        if(raiz->esq == NULL && raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}

Assinante *so_um_filho(Assinante *r){
    Assinante *no = NULL;
    if(r != NULL){
        if(r->esq == NULL && r->dir != NULL) no = r->dir;
        else if(r->esq != NULL && r->dir == NULL) no = r->esq;
    }
    return(no);
}

int dois_filhos(Assinante *r){
    return (r->esq != NULL && r->dir != NULL);
}

int remove_assinant(Assinante **r, char *cpf) {
    int removeu = 0;

    if (*r != NULL) {
        if (strcmp(cpf, (*r)->cpf) < 0) {
            removeu = remove_assinant(&(*r)->esq, cpf);
        } else if (strcmp(cpf, (*r)->cpf) > 0) {
            removeu = remove_assinant(&(*r)->dir, cpf);
        } else {
            // Encontrou o nó a ser removido!
            Assinante *temp = *r;

            // CASO 1: Nó Folha
            if (eh_folha(*r)) {
                *r = NULL;
                free(temp);
                removeu = 1;
            } 
            // CASO 2: Apenas UM filho
            else if (so_um_filho(*r) != NULL) { 
                *r = so_um_filho(*r); 
                free(temp);
                removeu = 1;
            } 
            // CASO 3: Dois filhos
            else if (dois_filhos(*r)) { 
                temp = (*r)->esq;
                while (temp->dir != NULL) temp = temp->dir;
                
                strcpy((*r)->cpf, temp->cpf);
                strcpy((*r)->nome, temp->nome);
                strcpy((*r)->endereco, temp->endereco);
                (*r)->nascimento = temp->nascimento;
                
                removeu = remove_assinant(&(*r)->esq, temp->cpf);
            }
        }

        
        // Se a remoção aconteceu (removeu == 1) e o nó atual não ficou nulo, recalcula o balanceamento
        if (*r != NULL && removeu) {
            *r = balancear_assinante(*r);
        }
    }
    
    return removeu;
}

// --------------- Liberação -----------

void liberar_arvore_assinante(Assinante *raiz){
    if (raiz != NULL) {
        liberar_arvore_assinante(raiz->esq);
        liberar_arvore_assinante(raiz->dir);
        free(raiz);
    }
}
