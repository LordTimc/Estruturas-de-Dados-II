#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/usuarios.h"
#include "../ABB_H/auxiliares.h"
#include "../ABB_H/formaAssinat.h"

forma_ass *aloca_forma_assinatura(){
    forma_ass *novo = (forma_ass *) malloc(sizeof(forma_ass));
            
    if (novo == NULL){ 
        printf("Erro na forma de assinatura! Falha naa alocacao memoria.\n");
    }else{
        novo->codigo = 0;
        novo->qtd_livros_mensais = 0;
        novo->qtd_generos_mensais = 0;
        novo->valor_mensal = 0.0;
        novo->valor_anual = 0.0;

        novo->generos_escolhidos = NULL;
        novo->prox = NULL; // Como vai para o final da lista, o próximo é NULL
    }
    return novo;           
}
/* Insere uma nova forma de assinatura no final da lista dinâmica, Valida se existe pelo menos um gênero cadastrado e impede códigos de forma repetidos.
 
 Parâmetros:
 - FormaDaAssi **inicio: Ponteiro duplo para o início da lista (passagem por referência).
 - int qtdGenerosCadastrados: Quantidade de gêneros (passagem por valor) para validar a regra de que deve haver pelo menos um gênero cadastrado.
 - int codigo, livrosMensais, generosMensais: Dados numéricos da forma (passagem por valor).
 - int *vetorGeneros: Vetor contendo os códigos dos gêneros escolhidos (passagem de ponteiro de array).
  - char *tipoEncadern: String do tipo de encadernação.
  - float valorMensal, valorAnual
 
 */

forma_ass* cad_forma_assinatura(forma_ass *lista, int qtd_generos_existentes) {
    // Validação: precisa ter pelo menos um gênero no sistema
    if (qtd_generos_existentes){
        forma_ass *novo = alocar_forma_assinatura();
        if (novo == NULL) return lista;

        printf("Codigo da Assinatura: ");
        scanf("%d", &novo->codigo);
        
        printf("Qtd. Livros Mensais: ");
        scanf("%d", &novo->qtd_livros_mensais);
        
        printf("Qtd. Generos Mensais: ");
        scanf("%d", &novo->qtd_generos_mensais);

        // Alocação do vetor dinâmico de códigos de gêneros dentro da assinatura
        novo->generos_escolhidos = (int*) malloc(novo->qtd_generos_mensais * sizeof(int));
        
        for (int i = 0; i < novo->qtd_generos_mensais; i++) {
            printf("Digite o codigo do %do genero: ", i + 1);
            scanf("%d", &novo->generos_escolhidos[i]);
        }

        printf("Tipo de encadernacao: ");
        scanf(" %[^\n]", novo->tipo_encadern); // Lê string com espaços
        
        printf("Valor Mensal: ");
        scanf("%f", &novo->valor_mensal);
        novo->valor_anual = novo->valor_mensal * 12; // Cálculo automático

        // Inserção no início da lista (mais simples em lista encadeada)
        novo->prox = lista;
        return novo;
    }
       
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