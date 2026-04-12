#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/livros.h"
#include "../ABB_H/auxiliares.h"


Livro *aloca_livro(char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica){
    // Aloca espaço na memória para o novo livro
    Livro *novo_livro = (Livro *)malloc(sizeof(Livro));
        
    // Verifica se a memória foi alocada com sucesso
    if (novo_livro != NULL) {
        strcpy(novo_livro->isbn, isbn);
        strcpy(novo_livro->titulo, titulo);
        strcpy(novo_livro->autor, autor);
        strcpy(novo_livro->editora, editora);
        novo_livro->edicao = edicao;
        novo_livro->ano_publica = ano_publica;
        
        // Como é um nó folha recém-criado, seus filhos são NULL
        novo_livro->esq = NULL;
        novo_livro->dir = NULL;
    }
    return(novo_livro);
}

/*
 * Insere um novo livro na Árvore Binária de Busca utilizando o ISBN como chave.
Parâmetros:
 * - Livro **raiz: Ponteiro duplo para a raiz da árvore de livros. Usamos passagem 
 * por referência para que a modificação do ponteiro (ao adicionar um novo nó) reflita diretamente na variável original lá no `main`.
 * - char *isbn, *titulo, *autor, *editora: Strings com os dados textuais do livro.
 * - int edicao, anoPublica: Dados numéricos do livro passados por valor.
 */

int cadastrar_livro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica) {
    int status_insercao = 0;

    // Se o ponteiro atual for NULL, encontramos a posição correta para inserir
    if (*raiz == NULL) {
        // Aloca memória para o novo livro
        

            *raiz = novo_livro;
                      
            status_insercao = 1;
        }
    } else {
        // Se a árvore não estiver vazia
        // Compara o ISBN recebido com o ISBN do nó atual
        int comparacao = strcmp(isbn, (*raiz)->isbn);

        if (comparacao < 0) {
            // Se o ISBN for "menor", desce para a subárvore esquerda
            status_insercao = cadastrar_livro(&((*raiz)->esq), isbn, titulo, autor, editora, edicao, ano_publica);
        } else if (comparacao > 0) {
            // Se o ISBN for "maior", desce para a subárvore direita
            status_insercao = cadastrar_livro(&((*raiz)->dir), isbn, titulo, autor, editora, edicao, ano_publica);
        } else {
            // Se a comparação for 0, os ISBNs são iguais. 
            // O cadastro é repetido, então a função não insere nada e o status continua 0.
            status_insercao = 0;
        }
    }

    return status_insercao;
}


/*
 * Função Auxiliar: mostrarLivrosDaArvore
 
  Percorre uma árvore binária de livros utilizando o percurso "Em Ordem" 
  (Esquerda -> Raiz -> Direita), garantindo que sejam impressos ordenados pelo ISBN.
 
  Parâmetros:
 - Livro *raiz: Ponteiro simples para a raiz da árvore de livros (passagem por valor).
 
 */
void mostrar_livros_da_arvore(Livro *raiz) {
    
    if (raiz != NULL) {
        // 1. Visita a subárvore esquerda
        mostrar_livros_da_arvore(raiz->esq);
        
        // 2. Imprime os dados do livro atual
        printf("--------------------------------------------------\n");
        printf("ISBN: %s\n", raiz->isbn);
        printf("Titulo: %s\n", raiz->titulo);
        printf("Autor: %s\n", raiz->autor);
        printf("Editora: %s\n", raiz->editora);
        printf("Edicao: %d\n", raiz->edicao);
        printf("Ano de Publicacao: %d\n", raiz->ano_publica);
        
        // 3. Visita a subárvore direita
        mostrar_livros_da_arvore(raiz->dir);
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
void mostrar_livros_por_genero(Genero lista[], int qtd, int codigo_genero) {
    int encontrou_genero = 0;

    // Percorre o vetor de gêneros
    for (int i = 0; i < qtd; i++) {
        // Verifica se é o gênero que estamos procurando
        if (lista[i].codigo == codigo_genero) {
            encontrou_genero = 1;
            
            printf("\n--- Livros do Genero: %s ---\n", lista[i].nome);
            
            // Verifica se a árvore de livros deste gênero está vazia
            if (lista[i].arvore_livros == NULL) {
                printf("Nenhum livro cadastrado nesta arvore.\n");
            } else {
                // Chama a função auxiliar para imprimir os livros
                mostrar_livros_da_arvore(lista[i].arvore_livros);
            }
            
            // Como já encontrou o gênero, podemos parar a busca no vetor
            break; 
        }
    }

    // Se o laço terminar e a flag continuar 0, o gênero não existe
    if (encontrou_genero == 0) {
        printf("Erro: Genero com o codigo %d nao foi encontrado.\n", codigo_genero);
    }
}