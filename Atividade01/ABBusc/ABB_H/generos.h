#include "structs.h"

// Função para cadastrar um novo gênero na lista estática ordenada
int cadastrar_genero(Genero lista[], int *qtd, int codigo, char *nome, Livro *arvore_livros);

// Função para mostrar todos os gêneros cadastrados na lista estática
void mostrar_generos(Genero lista[], int qtd);


// Função auxiliar para varrer a árvore de assinaturas e marcar os gêneros encontrados
void marcar_generos_assinados(Assinatura *raiz, forma_da_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]);

// Função principal para exibir os gêneros assinados
void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_da_ass *lista_formas, Genero lista_generos[], int qtd_generos);