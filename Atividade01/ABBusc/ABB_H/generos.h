#include "structs.h"

// Função para criar um novo gênero na lista estática não ordenada
Genero criar_genero(int codigo_livro, char *nome_genero);

// Função para inserir o genero na lista estática
int inserir_genero(Genero lista[], int *qtd_gen, Genero novo_genero);

// Função para verificar se o genero já existe
int existe_livro_cad(Genero lista[], int qtd_gen, int codigo_livro);

// Função para mostrar todos os gêneros cadastrados na lista estática
void mostrar_generos(Genero lista[], int qtd);



// Função auxiliar para varrer a árvore de assinaturas e marcar os gêneros encontrados
void marcar_generos_assinados(Assinatura *raiz, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]);

// Função principal para exibir os gêneros assinados
void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos);