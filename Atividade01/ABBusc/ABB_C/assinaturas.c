#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/auxiliares.h"

/*
 Insere uma nova assinatura na árvore binária, organizada pelo CPF do assinante.
 * Impede cadastros de CPFs repetidos.
 * Valida obrigatoriamente se o CPF existe na árvore de Usuários e se o código existe na lista de Formas.
 * Parâmetros:
 * - Assin **raiz: Ponteiro duplo para a raiz de Assinaturas (referência, pois modifica a estrutura da árvore).
 * - Usuario *raizUsuarios: Ponteiro simples da raiz de usuários (passagem por valor, apenas para consulta/busca).
 * - FormaDaAssi *listaFormas: Ponteiro simples do início da lista (passagem por valor, apenas para consulta/busca).
 * - char *cpf, *dataAssinatura, *dataVencimento: Strings dos dados (passagem de ponteiro de array).
 * - int codigoForma, float valor: Dados numéricos (passagem por valor).

 */
int cadastrarAssinatura(Assin **raiz, Usuario *raizUsuarios, FormaDaAssi *listaFormas, char *cpf, int codigoForma, char *dataAssinatura, char *dataVencimento, float valor) {

    int statusInsercao = 0;
    
    int assinanteExiste = 0;
    int formaExiste = 0;

    // --- VALIDAÇÃO 1: O assinante existe? ---
    // Busca na árvore binária de usuários de forma iterativa
    Usuario *tempU = raizUsuarios;
    while (tempU != NULL) {
        int comp = strcmp(cpf, tempU->cpf);
        if (comp == 0) {
            assinanteExiste = 1; // Encontrou o CPF
            break;
        } else if (comp < 0) {
            tempU = tempU->esq;
        } else {
            tempU = tempU->dir;
        }
    }

    // --- VALIDAÇÃO 2: A forma de assinatura existe? ---
    // Percorre a lista dinâmica iterativamente
    FormaDaAssi *tempF = listaFormas;
    while (tempF != NULL) {
        if (tempF->codigo == codigoForma) {
            formaExiste = 1; // Encontrou o código
            break;
        }
        tempF = tempF->prox;
    }

    // Só prossegue se as duas validações forem verdadeiras
    if (assinanteExiste == 1 && formaExiste == 1) {
        
        Assin *atual = *raiz;
        Assin *pai = NULL;
        int cpfRepetido = 0;

        // --- VALIDAÇÃO 3: O CPF já tem assinatura nesta árvore? ---
        // Desce na árvore de assinaturas procurando pelo CPF para achar a folha correta
        while (atual != NULL) {
            pai = atual; // Salva o nó atual como "pai" antes de descer
            int comp = strcmp(cpf, atual->cpfUsuario);
            
            if (comp == 0) {
                cpfRepetido = 1; // CPF já tem uma assinatura cadastrada
                break;
            } else if (comp < 0) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }

        // Se o CPF não for repetido, aloca e insere o nó
        if (cpfRepetido == 0) {
            Assin *novaAssinatura = (Assin *)malloc(sizeof(Assin));
            
            if (novaAssinatura != NULL) {
               
                strcpy(novaAssinatura->cpfUsuario, cpf);
                novaAssinatura->codigoForma = codigoForma;
                strcpy(novaAssinatura->dataAssinatura, dataAssinatura);
                strcpy(novaAssinatura->dataVencimento, dataVencimento);
                novaAssinatura->valor = valor;
                
                // Filhos nulos pois é um novo nó folha
                novaAssinatura->esq = NULL;
                novaAssinatura->dir = NULL;

                // Conecta o novo nó à árvore
                if (pai == NULL) {
                    // Se pai é NULL, a árvore estava vazia
                    *raiz = novaAssinatura;
                } else {
                    // Verifica se insere na esquerda ou direita do pai encontrado
                    if (strcmp(cpf, pai->cpfUsuario) < 0) {
                        pai->esq = novaAssinatura;
                    } else {
                        pai->dir = novaAssinatura;
                    }
                }
                
                
                statusInsercao = 1;
            }
        }
    }

    return statusInsercao;
}

/*

 * Percorre a árvore binária de assinaturas utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenadas pelo CPF do assinante.
 *
 * Parâmetros:
  - Assin *raiz: Ponteiro simples para a raiz da árvore de assinaturas. Usamos passagem 
 por valor (cópia do ponteiro) porque o objetivo é apenas exibir os dados na tela (LEITURA),
 sem alterar a estrutura ou os nós da árvore original.
 
 */
void mostrarAssinaturas(Assin *raiz) {
    
    if (raiz != NULL) {
        
        // 1º Passo: Visita a subárvore esquerda (CPFs menores)
        mostrarAssinaturas(raiz->esq);
        
        // 2º Passo: Imprime os dados do nó atual (a raiz deste momento)
        printf("--------------------------------------------------\n");
        printf("CPF do Assinante: %s\n", raiz->cpfUsuario);
        printf("Codigo da Forma: %d\n", raiz->codigoForma);
        printf("Data da Assinatura: %s\n", raiz->dataAssinatura);
        printf("Data de Vencimento: %s\n", raiz->dataVencimento);
        printf("Valor: R$ %.2f\n", raiz->valor);
        
        // 3º Passo: Visita a subárvore direita (CPFs maiores)
        mostrarAssinaturas(raiz->dir);
    }
}