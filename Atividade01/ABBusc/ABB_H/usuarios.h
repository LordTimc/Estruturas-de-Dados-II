#include "structs.h"
// Função para alocar um novo usuario (assinante)
Usuario *aloca_usuario (char *cpf, char *nome, char *endereco, char *data_nasc);

// Função para cadastrar um novo assinante na árvore binária
Usuario *cadastrar_assinante(Usuario *raiz);

// Função para mostrar todos os assinantes cadastrados na árvore (Em Ordem)
void mostrar_assinantes(Usuario *raiz);