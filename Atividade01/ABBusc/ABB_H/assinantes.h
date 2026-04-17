#include "structs.h"
// Função para alocar um novo usuario (assinante)
Assinante *aloca_assinante(char *cpf, char *nome, char *endereco, Data data_nascimento);

// Função para cadastrar um novo assinante na árvore binária
Assinante *cadastrar_assinante(Assinante *raiz);

// Função para inserir um novo assissante na arvore binária
int inserir_assinante(Assinante **raiz, Assinante *novo);

// Função para mostrar todos os assinantes cadastrados na árvore (Em Ordem)
int mostrar_assinantes(Assinante *raiz);

// Função verifica se o nó é folha
int no_sem_filho(Assinante *raiz);

// Função verifica se é só um filho
Assinante *so_um_filho(Assinante *r);

// Funçãao verifica se tem dois filhos
int dois_filhos(Assinante *r);

// Função remove assinante
int remove_assinant(Assinante **r, char *cpf);

// Função para liberar os nó e depois a raiz.
void liberar_arvore_usuario(Assinante *raiz);