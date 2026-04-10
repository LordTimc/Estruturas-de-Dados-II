#include "structs.h"


// Função para cadastrar uma nova forma de assinatura na lista dinâmica
int cadastrar_forma_assinatura(forma_da_ass **inicio, int qtd_generos_cadastrados, int codigo, int livros_mensais, int generos_mensais, int *vetor_generos, char *tipo_encadern, float valor_mensal, float valor_anual);

// Função para mostrar assinaturas filtradas por um código de forma específico
void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_forma);

// Função para mostrar todas as formas de assinatura cadastradas
void mostrar_formas_assinatura(forma_da_ass *inicio);