#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "generos.h"
#include "auxiliares.h"

Genero criar_genero(int codigo_livro, char *nome_genero){
    Genero novo;
    novo.codigo = codigo_livro;
    strcpy(novo.nome, nome_genero);
    novo.colecao_livros = NULL; 
    return novo; 
}

int inserir_genero(Genero lista[], int *qtd_gen, Genero novo_genero){
    int inseriu = 0;
    if (*qtd_gen < MAX_GENEROS) {
        lista[*qtd_gen] = novo_genero;
        (*qtd_gen)++;
        inseriu = 1; 
    } else {
        printf("Erro! Limite maximo atingido.\n");
    }
    return inseriu; 
}

int existe_livro_cad(Genero lista[], int qtd_gen, int codigo_livro){
    int existe = 0;
    for (int i = 0; i < qtd_gen; i++) {
        if (lista[i].codigo == codigo_livro) {
            existe = 1;
        }
    }
    return existe;
}

void mostrar_generos(Genero lista[], int qtd_gen){
    printf("\n--- Lista de Generos Cadastrados ---\n");
    if (qtd_gen == 0) {
        printf("Nenhum genero cadastrado no momento.\n");
    } else {
        for (int i = 0; i < qtd_gen; i++) {
            printf("--------------------------------------------------\n");
            printf("Codigo do Genero: %d\n", lista[i].codigo);
            printf("Nome do Genero: %s\n", lista[i].nome);
        }
    }
}

void marcar_generos_assinados(Assinatura *raiz, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]) {
    if (raiz != NULL) {
        marcar_generos_assinados(raiz->esq, lista_formas, lista_generos, qtd_generos, marcados);
        forma_ass *forma_atual = lista_formas;
        while (forma_atual != NULL) {
            if (forma_atual->codigo == raiz->codigo_forma) {
                for (int i = 0; i < forma_atual->qtd_generos_mensais; i++) {
                    int codigo_genero_escolhido = forma_atual->generos_escolhidos[i];
                    for (int j = 0; j < qtd_generos; j++) {
                        if (lista_generos[j].codigo == codigo_genero_escolhido) {
                            marcados[j] = 1; 
                            break; 
                        }
                    }
                }
                break; 
            }
            forma_atual = forma_atual->prox;
        }
        marcar_generos_assinados(raiz->dir, lista_formas, lista_generos, qtd_generos, marcados);
    }
}

void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos) {
    int marcados[MAX_GENEROS] = {0}; 
    int encontrou = 0;
    marcar_generos_assinados(raiz_assinaturas, lista_formas, lista_generos, qtd_generos, marcados);

    printf("--- Generos Atualmente Assinados ---\n");
    for (int i = 0; i < qtd_generos; i++) {
        if (marcados[i] == 1) { 
            printf("Codigo: %d | Nome: %s\n", lista_generos[i].codigo, lista_generos[i].nome);
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum genero esta sendo assinado no momento.\n");
    }
}