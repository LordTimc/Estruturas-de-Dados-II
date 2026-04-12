#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/usuarios.h"
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
int cadastrar_forma_assinatura(forma_ass **inicio, int qtd_generos_cadastrados, int codigo, int livros_mensais, int generos_mensais, int *vetor_generos, char *tipo_encadern, float valor_mensal, float valor_anual) {
    
    int status_insercao = 0;

    // 1ª Validação: O usuário já deve ter cadastrado pelo menos um tipo de gênero 
    if (qtd_generos_cadastrados > 0) {
        
        // 2ª Validação: Não permitir cadastro repetido (verificando o código da forma)
        int codigo_existe = 0;
        forma_ass *atual = *inicio;
        
        // Percorre a lista para procurar se o código já existe
        while (atual != NULL) {
            if (atual->codigo == codigo) {
                codigo_existe = 1; // Encontrou duplicata
                break;
            }
            atual = atual->prox;
        }

        // Se o código não existe, prossegue com a criação
        if (codigo_existe == 0) {
            
            forma_ass *nova_forma = (forma_ass *)malloc(sizeof(forma_ass));
            
            if (nova_forma != NULL) {
                
                nova_forma->codigo = codigo;
                nova_forma->livros_mensais = livros_mensais;
                nova_forma->generos_mensais = generos_mensais;
                strcpy(nova_forma->tipo_encadern, tipo_encadern);
                nova_forma->valor_mensal = valor_mensal;
                nova_forma->valor_anual = valor_anual;
                nova_forma->prox = NULL; // Como vai para o final da lista, o próximo é NULL

                // Aloca dinamicamente o vetor de gêneros escolhidos com base na quantidade informada
                nova_forma->generos_escolhidos = (int *)malloc(generos_mensais * sizeof(int));
                
                if (nova_forma->generos_escolhidos != NULL) {
                    // Copia os códigos do vetor passado por parâmetro para a struct
                    for (int i = 0; i < generos_mensais; i++) {
                        nova_forma->generos_escolhidos[i] = vetor_generos[i];
                    }

                    // Lógica para inserir na lista dinâmica
                    if (*inicio == NULL) {
                        // Se a lista estiver vazia, a nova forma será o primeiro elemento (modifica no main)
                        *inicio = nova_forma;
                    } else {
                        // Se não estiver vazia, percorre até o final e conecta
                        forma_ass *temp = *inicio;
                        while (temp->prox != NULL) {
                            temp = temp->prox;
                        }
                        temp->prox = nova_forma;
                    }
                    
                    status_insercao = 1;
                } else {
                    free(nova_forma);
                }
            }
        }
    }

    
    return status_insercao;
}

/*
 * Percorre toda a árvore binária de assinaturas (método Em Ordem) e imprime 
 apenas os nós cujo 'codigo_forma' seja igual ao informado pelo usuário.
 
 Parâmetros:
 - Assin *raiz: Ponteiro simples para a raiz da árvore (passagem por valor). 
 Escolhido porque a função fará apenas LEITURA dos dados, não precisando 
 alterar a árvore original no 'main'.
  int codigo_forma: O código numérico da forma que queremos filtrar (passagem por valor).
*/

void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_forma) {
    
    if (raiz != NULL) {
        
        // 1º Passo: Visita toda a subárvore esquerda
        mostrar_assinaturas_por_forma(raiz->esq, codigo_forma);
        
        // 2º Passo: Verifica se o nó atual (raiz deste momento) possui o código desejado
        if (raiz->codigo_forma == codigo_forma) {
            printf("--------------------------------------------------\n");
            printf("CPF do Assinante: %s\n", raiz->cpf_usuario);
            printf("Data da Assinatura: %s\n", raiz->data_assinatura);
            printf("Data de Vencimento: %s\n", raiz->data_vencimento);
            printf("Valor: R$ %.2f\n", raiz->valor);
        }
        
        // 3º Passo: Visita toda a subárvore direita
        mostrar_assinaturas_por_forma(raiz->dir, codigo_forma);
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
void mostrar_formas_assinatura(forma_ass *inicio) {
    // Verifica se a lista está vazia antes de tentar imprimir
    if (inicio == NULL) {
        printf("Nenhuma forma de assinatura cadastrada no momento.\n");
    } else {
        // Cria um ponteiro auxiliar para percorrer a lista
        forma_ass *atual = inicio;

        while (atual != NULL) {
            printf("--------------------------------------------------\n");
            printf("Codigo da Forma: %d\n", atual->codigo);
            printf("Valor Mensal: R$ %.2f\n", atual->valor_mensal);
            printf("Valor Anual: R$ %.2f\n", atual->valor_anual);
            
            atual = atual->prox;
        }
    }
}