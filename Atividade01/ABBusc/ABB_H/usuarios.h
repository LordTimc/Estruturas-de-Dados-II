#include "structs.h"
// Função para alocar um novo usuario (assinante)
Usuario *aloca_assinante(char *cpf, char *nome, char *endereco, data_nasci data_nasc);

// Função para cadastrar um novo assinante na árvore binária
Usuario *cadastrar_assinante(Usuario *raiz);

// Função para inserir um novo assissante na arvore binária
int inserir_assinante(Usuario **raiz, Usuario *novo);

// Função para mostrar todos os assinantes cadastrados na árvore (Em Ordem)
int mostrar_assinantes(Usuario *raiz);

// Função verifica se o nó é folha
int no_sem_filho(Usuario *raiz);

// Função verifica se é só um filho
Usuario *so_um_filho(Usuario *r);