#include "structs.h"

// Função para cadastrar um novo assinante na árvore binária
int cadastrar_assinante(Usuario **raiz, char *cpf, char *nome, char *endereco, char *dataNasc);

// Função para mostrar todos os assinantes cadastrados na árvore (Em Ordem)
void mostrar_assinantes(Usuario *raiz);