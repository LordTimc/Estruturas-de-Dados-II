#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "livros.h"
#include "auxiliares.h"
#include "suporteAVL.h"

Livro *aloca_livro(char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica){
    Livro *novo_livro = (Livro *)malloc(sizeof(Livro));
    if (novo_livro != NULL) {
        strcpy(novo_livro->isbn, isbn);
        strcpy(novo_livro->titulo, titulo);
        strcpy(novo_livro->autor, autor);
        strcpy(novo_livro->editora, editora);
        novo_livro->edicao = edicao;
        novo_livro->ano_publica = ano_publica;
        
        novo_livro->altura = 1;
        novo_livro->esq = NULL;
        novo_livro->dir = NULL;
    }
    return(novo_livro);
}

Livro *cadastrar_livro(Livro *livro){
    char isbn[3];
    char *titulo = NULL;
    char *autor = NULL;
    char *editora = NULL;
    int edicao;
    int ano_publica;
    int cadastrou = 0;

    printf("==== Informacoes do livro ====");

    if(pega_isbn(isbn)){
        printf("\nDigite o titulo: ");
        titulo = leitura_de_string();
        
        if(titulo != NULL){
            printf("Autor: ");
            autor = leitura_de_string(); 
            printf("Editora: ");
            editora = leitura_de_string(); 
            printf("Edicao: ");
            edicao = num_inteiro(); 
            printf("Ano de publicacao: ");
            ano_publica = num_inteiro(); 

            if(autor != NULL && editora != NULL){
                livro = aloca_livro(isbn, titulo, autor, editora, edicao, ano_publica);
                cadastrou = 1;
                free(titulo);
                free(autor);
                free(editora);
            }
        }
    }
    if(!cadastrou){
        if(titulo) free(titulo);
        if(autor) free(autor);
        if(editora) free(editora);
    }
    return livro;
}

int inserir_livro(Livro **r, Livro *novo){
    if (*r == NULL) {
        *r = novo;
        return 1;
    }
    
    int inseriu = 0;
    if(strcmp(novo->isbn, (*r)->isbn) == 0){
        free(novo);
        return 0;
    } else if(strcmp(novo->isbn, (*r)->isbn) < 0){
        inseriu = inserir_livro(&(*r)->esq, novo);
    } else {
        inseriu = inserir_livro(&(*r)->dir, novo);
    }
    
    if (!inseriu) return 0;

    // BALANCEAMENTO AVL
    (*r)->altura = 1 + maior(altura_liv((*r)->esq), altura_liv((*r)->dir));
    int fb = fb_liv(*r);

    if (fb > 1 && strcmp(novo->isbn, (*r)->esq->isbn) < 0)
        *r = rot_dir_liv(*r);
    else if (fb < -1 && strcmp(novo->isbn, (*r)->dir->isbn) > 0)
        *r = rot_esq_liv(*r);
    else if (fb > 1 && strcmp(novo->isbn, (*r)->esq->isbn) > 0) {
        (*r)->esq = rot_esq_liv((*r)->esq);
        *r = rot_dir_liv(*r);
    } else if (fb < -1 && strcmp(novo->isbn, (*r)->dir->isbn) < 0) {
        (*r)->dir = rot_dir_liv((*r)->dir);
        *r = rot_esq_liv(*r);
    }
    return inseriu;
}

int mostrar_livros_da_arvore(Livro *r){
    int mostrou = 0;
    if (r != NULL) {
        mostrou = mostrar_livros_da_arvore(r->esq);
        printf("--------------------------------------------------\n");
        printf("ISBN: %s\n", r->isbn);
        printf("Titulo: %s\n", r->titulo);
        printf("Autor: %s\n", r->autor);
        printf("Editora: %s\n", r->editora);
        printf("Edicao: %d\n", r->edicao);
        printf("Ano de Publicacao: %d\n", r->ano_publica);
        mostrou = mostrar_livros_da_arvore(r->dir);
        mostrou = 1;
    }
    return mostrou;
}

void mostrar_livros_por_genero(Genero lista[], int qtd_genero, int codigo_genero) {
    int encontrou_genero = 0;
    int i = 0;
    while (i < qtd_genero && !encontrou_genero) {
        if (lista[i].codigo == codigo_genero) {
            encontrou_genero = 1; 
            printf("\n--- Livros do Genero: %s ---\n", lista[i].nome);
            int imprimiu = mostrar_livros_da_arvore(lista[i].colecao_livros);
            if (imprimiu == 0) {
                printf("Nenhum livro cadastrado neste genero.\n");
            }
        }
        i++; 
    }
    if (!encontrou_genero) {
        printf("Erro: Genero com o codigo %d nao foi encontrado.\n", codigo_genero);
    }
}

void liberar_arvore_livros(Livro *raiz){
    if (raiz != NULL) {
        liberar_arvore_livros(raiz->esq);
        liberar_arvore_livros(raiz->dir);
        free(raiz);
    }
}