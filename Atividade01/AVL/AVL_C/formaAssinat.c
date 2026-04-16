#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVL_H/formaAssinat.h"


forma_ass *alocar_forma_assinatura(){
    forma_ass *novo = (forma_ass *) malloc(sizeof(forma_ass));
    if (novo == NULL){ 
        printf("Erro na forma de assinatura! Falha na alocacao memoria.\n");
    }else{
        novo->codigo = 0;
        novo->qtd_livros_mensais = 0;
        novo->qtd_generos_mensais = 0;
        novo->valor_mensal = 0.0;
        novo->valor_anual = 0.0;
        novo->generos_escolhidos = NULL;
        novo->prox = NULL; 
    }
    return novo;           
}

int *alocar_vetor_generos(int qtd){
    int *aux = NULL;
    if (qtd > 0){
        aux = (int*) malloc(qtd * sizeof(int));
        if(aux == NULL)
            printf("Erro! Falha ao alocar memoria para o vetor de generos.\n");
    };
    return aux;
}

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
            printf("Codigo: "); 
            novo->codigo = num_inteiro();
            printf("Qtd Livros: ");
            novo->qtd_livros_mensais = num_inteiro();
            printf("Qtd Generos: "); 
            novo->qtd_generos_mensais = num_inteiro();

            novo->generos_escolhidos = alocar_vetor_generos(novo->qtd_generos_mensais);
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
                    cadastrou = 1; 
                }
            }
        }
    } else {
        printf("Erro: Nenhum genero cadastrado no sistema.\n");
    }

    if (cadastrou) {
        retorno = inserir_na_lista(lista, novo);
        printf("Assinatura cadastrada com sucesso!\n");
    } else {
        if (novo != NULL) {
            if (novo->generos_escolhidos != NULL) free(novo->generos_escolhidos);
            free(novo);
        }
    }
    if (texto_limpo != NULL) free(texto_limpo);
    return retorno; 
}

void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_busca){
    if (raiz != NULL) {
        mostrar_assinaturas_por_forma(raiz->esq, codigo_busca);
        if (raiz->codigo_forma == codigo_busca){
            printf("\n-------------------------------------------");
            printf("\nCPF do Assinante: %s", raiz->cpf_usuario);
            printf("\nData Assinatura:  %02d/%02d/%04d", raiz->data_assinatura.dia, raiz->data_assinatura.mes, raiz->data_assinatura.ano);
            printf("\nData Vencimento:  %02d/%02d/%04d", raiz->data_vencimento.dia, raiz->data_vencimento.mes, raiz->data_vencimento.ano);
            printf("\nValor:            R$ %.2f", raiz->valor);
            printf("\n-------------------------------------------");
        }
        mostrar_assinaturas_por_forma(raiz->dir, codigo_busca);
    }
}

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
            printf("Generos (%d): ", aux->qtd_generos_mensais);
            if (aux->generos_escolhidos != NULL){
                for (int i = 0; i < aux->qtd_generos_mensais; i++){
                    printf("[%d] ", aux->generos_escolhidos[i]);
                }
            }
            printf("\n");
            printf("Valor Mensal: R$ %.2f\n", aux->valor_mensal);
            printf("Valor Anual:  R$ %.2f\n", aux->valor_anual);
            printf("--------------------------------------------------\n");
            aux = aux->prox; 
        }
    }
    printf("====================================================\n");
}