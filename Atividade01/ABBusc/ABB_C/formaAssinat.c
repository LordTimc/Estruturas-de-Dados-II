#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/auxiliares.h"
#include "../ABB_H/formaAssinat.h"

/* Insere uma nova forma de assinatura no final da lista dinâmica, Valida se existe pelo menos um gênero cadastrado e impede códigos de forma repetidos.
 
 Parâmetros:
 - FormaDaAssi **inicio: Ponteiro duplo para o início da lista (passagem por referência).
 - int qtdGenerosCadastrados: Quantidade de gêneros (passagem por valor) para validar a regra de que deve haver pelo menos um gênero cadastrado.
 - int codigo, livrosMensais, generosMensais: Dados numéricos da forma (passagem por valor).
 - int *vetorGeneros: Vetor contendo os códigos dos gêneros escolhidos (passagem de ponteiro de array).
  - char *tipoEncadern: String do tipo de encadernação.
  - float valorMensal, valorAnual
 
 */
int cadastrarFormaAssinatura(FormaDaAssi **inicio, int qtdGenerosCadastrados, int codigo, int livrosMensais, int generosMensais, int *vetorGeneros, char *tipoEncadern, float valorMensal, float valorAnual) {
    
    int statusInsercao = 0;

    // 1ª Validação: O usuário já deve ter cadastrado pelo menos um tipo de gênero 
    if (qtdGenerosCadastrados > 0) {
        
        // 2ª Validação: Não permitir cadastro repetido (verificando o código da forma)
        int codigoExiste = 0;
        FormaDaAssi *atual = *inicio;
        
        // Percorre a lista para procurar se o código já existe
        while (atual != NULL) {
            if (atual->codigo == codigo) {
                codigoExiste = 1; // Encontrou duplicata
                break;
            }
            atual = atual->prox;
        }

        // Se o código não existe, prossegue com a criação
        if (codigoExiste == 0) {
            
            FormaDaAssi *novaForma = (FormaDaAssi *)malloc(sizeof(FormaDaAssi));
            
            if (novaForma != NULL) {
                
                novaForma->codigo = codigo;
                novaForma->livrosMensais = livrosMensais;
                novaForma->generosMensais = generosMensais;
                strcpy(novaForma->tipoEncadern, tipoEncadern);
                novaForma->valorMensal = valorMensal;
                novaForma->valorAnual = valorAnual;
                novaForma->prox = NULL; // Como vai para o final da lista, o próximo é NULL

                // Aloca dinamicamente o vetor de gêneros escolhidos com base na quantidade informada
                novaForma->generosEscolhidos = (int *)malloc(generosMensais * sizeof(int));
                
                if (novaForma->generosEscolhidos != NULL) {
                    // Copia os códigos do vetor passado por parâmetro para a struct
                    for (int i = 0; i < generosMensais; i++) {
                        novaForma->generosEscolhidos[i] = vetorGeneros[i];
                    }

                    // Lógica para inserir na lista dinâmica
                    if (*inicio == NULL) {
                        // Se a lista estiver vazia, a nova forma será o primeiro elemento (modifica no main)
                        *inicio = novaForma;
                    } else {
                        // Se não estiver vazia, percorre até o final e conecta
                        FormaDaAssi *temp = *inicio;
                        while (temp->prox != NULL) {
                            temp = temp->prox;
                        }
                        temp->prox = novaForma;
                    }
                    
                    statusInsercao = 1;
                } else {
                    free(novaForma);
                }
            }
        }
    }

    
    return statusInsercao;
}

/*
 * Percorre toda a árvore binária de assinaturas (método Em Ordem) e imprime 
 apenas os nós cujo 'codigoForma' seja igual ao informado pelo usuário.
 
 Parâmetros:
 - Assin *raiz: Ponteiro simples para a raiz da árvore (passagem por valor). 
 Escolhido porque a função fará apenas LEITURA dos dados, não precisando 
 alterar a árvore original no 'main'.
  int codigoForma: O código numérico da forma que queremos filtrar (passagem por valor).
*/

void mostrarAssinaturasPorForma(Assin *raiz, int codigoForma) {
    
    if (raiz != NULL) {
        
        // 1º Passo: Visita toda a subárvore esquerda
        mostrarAssinaturasPorForma(raiz->esq, codigoForma);
        
        // 2º Passo: Verifica se o nó atual (raiz deste momento) possui o código desejado
        if (raiz->codigoForma == codigoForma) {
            printf("--------------------------------------------------\n");
            printf("CPF do Assinante: %s\n", raiz->cpfUsuario);
            printf("Data da Assinatura: %s\n", raiz->dataAssinatura);
            printf("Data de Vencimento: %s\n", raiz->dataVencimento);
            printf("Valor: R$ %.2f\n", raiz->valor);
        }
        
        // 3º Passo: Visita toda a subárvore direita
        mostrarAssinaturasPorForma(raiz->dir, codigoForma);
    }
}

/*

 Percorre a lista dinâmica de Formas de Assinatura do início ao fim de forma iterativa.
 Imprime o código da forma, o valor mensal e o valor anual.
 
 * Parâmetros:
 - FormaDaAssi *inicio: Ponteiro simples para o primeiro elemento da lista (passagem por value).
 Escolhemos a passagem por value porque a função serve apenas para LEITURA. 
 * Usar uma cópia do ponteiro nos permite percorrer a lista sem perder a referência original no 'main'.
 
 */
void mostrarFormasAssinatura(FormaDaAssi *inicio) {
    // Verifica se a lista está vazia antes de tentar imprimir
    if (inicio == NULL) {
        printf("Nenhuma forma de assinatura cadastrada no momento.\n");
    } else {
        // Cria um ponteiro auxiliar para percorrer a lista
        FormaDaAssi *atual = inicio;

        while (atual != NULL) {
            printf("--------------------------------------------------\n");
            printf("Codigo da Forma: %d\n", atual->codigo);
            printf("Valor Mensal: R$ %.2f\n", atual->valorMensal);
            printf("Valor Anual: R$ %.2f\n", atual->valorAnual);
            
    
            atual = atual->prox;
        }
    }
}