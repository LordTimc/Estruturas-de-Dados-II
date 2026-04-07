#include "structs.h"

// Função para cadastrar um novo gênero na lista estática ordenada
int cadastrarGenero(Genero lista[], int *qtd, int codigo, char *nome, Livro *arvoreLivros);

// Função para mostrar todos os gêneros cadastrados na lista estática
void mostrarGeneros(Genero lista[], int qtd);


// Função auxiliar para varrer a árvore de assinaturas e marcar os gêneros encontrados
void marcarGenerosAssinados(Assin *raiz, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros, int marcados[]);

// Função principal para exibir os gêneros assinados
void mostrarGenerosAssinados(Assin *raizAssinaturas, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros);