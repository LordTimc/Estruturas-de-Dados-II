#ifndef GENEROS_H
#define GENEROS_H

#include "../AVL_H/structs.h"

Genero criar_genero(int codigo_livro, char *nome_genero);
int inserir_genero(Genero lista[], int *qtd_gen, Genero novo_genero);
int existe_livro_cad(Genero lista[], int qtd_gen, int codigo_livro);
void mostrar_generos(Genero lista[], int qtd);
void marcar_generos_assinados(Assinatura *raiz, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]);
void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos);

#endif