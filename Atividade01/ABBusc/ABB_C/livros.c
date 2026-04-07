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


/*
 * Função Auxiliar: mostrarLivrosDaArvore
 
  Percorre uma árvore binária de livros utilizando o percurso "Em Ordem" 
  (Esquerda -> Raiz -> Direita), garantindo que sejam impressos ordenados pelo ISBN.
 
  Parâmetros:
 - Livro *raiz: Ponteiro simples para a raiz da árvore de livros (passagem por valor).
 
 */
void mostrarLivrosDaArvore(Livro *raiz) {
    
    if (raiz != NULL) {
        // 1. Visita a subárvore esquerda
        mostrarLivrosDaArvore(raiz->esq);
        
        // 2. Imprime os dados do livro atual
        printf("--------------------------------------------------\n");
        printf("ISBN: %s\n", raiz->isbn);
        printf("Titulo: %s\n", raiz->titulo);
        printf("Autor: %s\n", raiz->autor);
        printf("Editora: %s\n", raiz->editora);
        printf("Edicao: %d\n", raiz->edicao);
        printf("Ano de Publicacao: %d\n", raiz->anoPublica);
        
        // 3. Visita a subárvore direita
        mostrarLivrosDaArvore(raiz->dir);
    }
}

/*
 * Função Principal: mostrarLivrosPorGenero
 Percorre a lista estática de gêneros procurando pelo código informado.
 Se encontrar, chama a função auxiliar para imprimir a árvore de livros dele.
 
 *Parâmetros:
  - Genero lista[]: O vetor de gêneros (passagem para leitura).
  - int qtd: Quantidade atual de gêneros cadastrados (passagem por valor).
  - int codigoGenero: O código do gênero que o usuário deseja buscar (passagem por valor).
 
 */
void mostrarLivrosPorGenero(Genero lista[], int qtd, int codigoGenero) {
    int encontrouGenero = 0;

    // Percorre o vetor de gêneros
    for (int i = 0; i < qtd; i++) {
        // Verifica se é o gênero que estamos procurando
        if (lista[i].codigo == codigoGenero) {
            encontrouGenero = 1;
            
            printf("\n--- Livros do Genero: %s ---\n", lista[i].nome);
            
            // Verifica se a árvore de livros deste gênero está vazia
            if (lista[i].arvoreLivros == NULL) {
                printf("Nenhum livro cadastrado nesta arvore.\n");
            } else {
                // Chama a função auxiliar para imprimir os livros
                mostrarLivrosDaArvore(lista[i].arvoreLivros);
            }
            
            // Como já encontrou o gênero, podemos parar a busca no vetor
            break; 
        }
    }

    // Se o laço terminar e a flag continuar 0, o gênero não existe
    if (encontrouGenero == 0) {
        printf("Erro: Genero com o codigo %d nao foi encontrado.\n", codigoGenero);
    }
}