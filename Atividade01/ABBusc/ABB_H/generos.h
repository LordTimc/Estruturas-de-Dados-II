#include "structs.h"

// Função para cadastrar um novo gênero na lista estática ordenada
int cadastrarGenero(Genero lista[], int *qtd, int codigo, char *nome, Livro *arvoreLivros);

// Função para mostrar todos os gêneros cadastrados na lista estática
void mostrarGeneros(Genero lista[], int qtd);