#include "structs.h"

// Funçao para alocar um novo livro
Livro *aloca_livro();

// Função para cadastrar um novo livro na árvore binária
void *cadastrar_livro(Livro **livro);

// Função para inserir um novo livro na árvore binária
int inserir_livro(Livro **r, Livro *novo);

// Função auxiliar para imprimir os livros de uma árvore binária
int mostrar_livros_da_arvore(Livro *r);

// Função principal para buscar um gênero e mostrar seus livros
void mostrar_livros_por_genero(Genero lista[], int qtd, int codigo_genero);

// Função para liberar os nó e depois a raiz.
void liberar_arvore_livros(Livro *raiz);