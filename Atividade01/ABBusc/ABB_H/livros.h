#include "structs.h"

// Função para cadastrar um novo livro na árvore binária
int cadastrarLivro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int anoPublica);

// Função auxiliar para imprimir os livros de uma árvore binária
void mostrarLivrosDaArvore(Livro *raiz);

// Função principal para buscar um gênero e mostrar seus livros
void mostrarLivrosPorGenero(Genero lista[], int qtd, int codigoGenero);