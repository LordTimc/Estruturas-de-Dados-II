#include "structs.h"
// Função para alocar um novo usuario (assinante)
Usuario *aloca_assinante(char *cpf, char *nome, char *endereco, Data data_nascimento);

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

// Funçãao verifica se tem dois filhos
int dois_filhos(Usuario *r);

// Função remove assinante
int remove_assinant(Usuario **r, char *cpf);

// Função para liberar os nó e depois a raiz.
void liberar_arvore_usuario(Usuario *raiz);