#include "structs.h"

// Funçao para alocar um novo livro
Livro *aloca_livro(char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica);

// Função para cadastrar um novo livro na árvore binária
int cadastrar_livro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica);

// Função auxiliar para imprimir os livros de uma árvore binária
void mostrar_livros_da_arvore(Livro *raiz);

// Função principal para buscar um gênero e mostrar seus livros
void mostrar_livros_por_genero(Genero lista[], int qtd, int codigo_genero);