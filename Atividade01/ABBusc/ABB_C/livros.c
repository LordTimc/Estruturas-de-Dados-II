#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/livros.h"
#include "../ABB_H/auxiliares.h"

/*
 * Insere um novo livro na Árvore Binária de Busca utilizando o ISBN como chave.
Parâmetros:
 * - Livro **raiz: Ponteiro duplo para a raiz da árvore de livros. Usamos passagem 
 * por referência para que a modificação do ponteiro (ao adicionar um novo nó) reflita diretamente na variável original lá no `main`.
 * - char *isbn, *titulo, *autor, *editora: Strings com os dados textuais do livro.
 * - int edicao, anoPublica: Dados numéricos do livro passados por valor.
 */

int cadastrarLivro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int anoPublica) {
    int statusInsercao = 0;

    // Se o ponteiro atual for NULL, encontramos a posição correta para inserir
    if (*raiz == NULL) {
        // Aloca memória para o novo livro
        Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
        
        // Verifica se a memória foi alocada com sucesso
        if (novoLivro != NULL) {
            strcpy(novoLivro->isbn, isbn);
            strcpy(novoLivro->titulo, titulo);
            strcpy(novoLivro->autor, autor);
            strcpy(novoLivro->editora, editora);
            novoLivro->edicao = edicao;
            novoLivro->anoPublica = anoPublica;
            
            // Como é um nó folha recém-criado, seus filhos são NULL
            novoLivro->esq = NULL;
            novoLivro->dir = NULL;

            *raiz = novoLivro;
                      
            statusInsercao = 1;
        }
    } else {
        // Se a árvore não estiver vazia
        // Compara o ISBN recebido com o ISBN do nó atual
        int comparacao = strcmp(isbn, (*raiz)->isbn);

        if (comparacao < 0) {
            // Se o ISBN for "menor", desce para a subárvore esquerda
            statusInsercao = cadastrarLivro(&((*raiz)->esq), isbn, titulo, autor, editora, edicao, anoPublica);
        } else if (comparacao > 0) {
            // Se o ISBN for "maior", desce para a subárvore direita
            statusInsercao = cadastrarLivro(&((*raiz)->dir), isbn, titulo, autor, editora, edicao, anoPublica);
        } else {
            // Se a comparação for 0, os ISBNs são iguais. 
            // O cadastro é repetido, então a função não insere nada e o status continua 0.
            statusInsercao = 0;
        }
    }

    return statusInsercao;
}