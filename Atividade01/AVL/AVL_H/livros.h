#ifndef LIVROS_H
#define LIVROS_H

#include "structs.h"

Livro *aloca_livro();
void *cadastrar_livro(Livro **livro);
int inserir_livro(Livro **r, Livro *novo);
int mostrar_livros_da_arvore(Livro *r);
void mostrar_livros_por_genero(Genero lista[], int qtd, int codigo_genero);
void liberar_arvore_livros(Livro *raiz);

#endif