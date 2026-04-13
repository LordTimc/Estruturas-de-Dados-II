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

// Função para criar o vetor de códigos dentro da struct
int *alocar_vetor_generos(int qtd){
    int *aux = NULL;
    if (qtd > 0){
        aux = (int*) malloc(qtd * sizeof(int));
        if(aux == NULL)
            printf("Erro! Falha ao alocar memoria para o vetor de generos.\n");
    };
    return aux;
}

// Função para inserir um nó já pronto na lista
forma_ass *inserir_na_lista(forma_ass* lista, forma_ass* novo){
    forma_ass* retorno = lista;
    if (novo != NULL) {
        novo->prox = lista;
        retorno = novo;
    }
    return retorno;
}

forma_ass *cad_forma_assinatura(forma_ass *lista, int qtd_generos_sistema){
    forma_ass *retorno = lista; 
    forma_ass *novo = NULL;
    char *texto_limpo = NULL;
    int cadastrou = 0;

    if (qtd_generos_sistema > 0) {
        novo = alocar_forma_assinatura();
        
        if (novo != NULL) {
            // --- Leitura de Dados Básicos ---
            printf("Codigo: "); 
            novo->codigo = num_inteiro();
            printf("Qtd Livros: ");
            novo->qtd_livros_mensais = num_inteiro();
            printf("Qtd Generos: "); 
            novo->qtd_generos_mensais = num_inteiro();

            // Alocação do vetor interno
            novo->generos_escolhidos = alocar_vetor_generos(novo->qtd_generos_mensais);
            
            // Verificamos se o vetor de gêneros foi alocado com sucesso
            if (novo->generos_escolhidos != NULL) {
                for (int i = 0; i < novo->qtd_generos_mensais; i++) {
                    printf("Codigo do %do genero: ", i + 1);
                    novo->generos_escolhidos[i] = num_inteiro();
                }

                printf("Encadernacao: ");
                texto_limpo = leitura_de_string(); 

                if (texto_limpo != NULL) {
                    strncpy(novo->tipo_encadern, texto_limpo, 49);
                    novo->tipo_encadern[49] = '\0';
                    
                    printf("Valor Mensal: "); 
                    novo->valor_mensal = num_decimal();
                    novo->valor_anual = novo->valor_mensal * 12;

                    // Se chegou aqui, tudo deu certo!
                    cadastrou = 1; 
                }
            }
        }
    } else {
        printf("Erro: Nenhum genero cadastrado no sistema.\n");
    }

    // --- Lógica Pós-Processamento ---
    if (cadastrou) {
        retorno = inserir_na_lista(lista, novo);
        printf("Assinatura cadastrada com sucesso!\n");
    } else {
        // Se algo falhou, precisamos limpar o que foi alocado
        if (novo != NULL) {
            if (novo->generos_escolhidos != NULL) free(novo->generos_escolhidos);
            free(novo);
        }
    }

    // Limpeza obrigatória de variáveis auxiliares de leitura
    if (texto_limpo != NULL) free(texto_limpo);

    return retorno; 
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


/*
 * Percorre toda a árvore binária de assinaturas (método Em Ordem) e imprime 
 apenas os nós cujo 'codigo_forma' seja igual ao informado pelo usuário.
 
 Parâmetros:
 - Assin *raiz: Ponteiro simples para a raiz da árvore (passagem por valor). 
 Escolhido porque a função fará apenas LEITURA dos dados, não precisando 
 alterar a árvore original no 'main'.
  int codigo_forma: O código numérico da forma que queremos filtrar (passagem por valor).
*/

void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_busca){
    int encontrou = 0;
    if (raiz != NULL) {
        // 1. Visita a subárvore da esquerda
        mostrar_assinaturas_por_forma(raiz->esq, codigo_busca);

        // 2. Verifica se o nó atual corresponde à busca
        if (raiz->codigo_forma == codigo_busca){
            encontrou = 1;
            printf("\n-------------------------------------------");
            printf("\nCPF do Assinante: %s", raiz->cpf_usuario);
            printf("\nData Assinatura:  %02d/%02d/%04d", 
                    raiz->data_assinatura.dia, 
                    raiz->data_assinatura.mes, 
                    raiz->data_assinatura.ano);
            printf("\nData Vencimento:  %02d/%02d/%04d", 
                    raiz->data_vencimento.dia, 
                    raiz->data_vencimento.mes, 
                    raiz->data_vencimento.ano);
            printf("\nValor:            R$ %.2f", raiz->valor);
            printf("\n-------------------------------------------");
        }

        // 3. Visita a subárvore da direita
        mostrar_assinaturas_por_forma(raiz->dir, codigo_busca);
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
void mostrar_formas_assinatura(forma_ass *lista){
    forma_ass *aux = lista;
    printf("\n========= FORMAS DE ASSINATURA CADASTRADAS =========\n");

    if (aux == NULL){
        printf("Nenhuma assinatura cadastrada no sistema.\n");
    }else{
        while (aux != NULL) {
            printf("Codigo: %d\n", aux->codigo);
            printf("Tpo de Encadernacao: %s\n", aux->tipo_encadern);
            printf("Quantidade de Livros Mensais: %d\n", aux->qtd_livros_mensais);
            
            // Exibindo os gêneros escolhidos (vetor dinâmico interno)
            printf("Generos (%d): ", aux->qtd_generos_mensais);
            if (aux->generos_escolhidos != NULL){
                for (int i = 0; i < aux->qtd_generos_mensais; i++){
                    printf("[%d] ", aux->generos_escolhidos[i]);
                }
            }
            printf("\n");

            // Exibindo os valores financeiros
            printf("Valor Mensal: R$ %.2f\n", aux->valor_mensal);
            printf("Valor Anual:  R$ %.2f\n", aux->valor_anual);
            
            printf("--------------------------------------------------\n");
            aux = aux->prox; // Avança para o próximo nó da lista
        }
    }
    printf("====================================================\n");
}