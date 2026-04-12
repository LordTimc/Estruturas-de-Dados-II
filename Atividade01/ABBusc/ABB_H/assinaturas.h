#ifndef ARQ_h
#define ARQ_H
#define MAXGENEROS 5

#include "structs.h"

// Função para alocar a memoria de uma assinatura
Assinatura* alocar_assinatura();

// Função para cadastrar uma assinatura na árvore binária
Assinatura* cadastrar_assinatura(Assinatura *r);

// Função para inserir assinatura
int *inserir_assintura(Assinatura **raiz, Assinatura *novo);

// Função para mostrar todas as assinaturas cadastradas na árvore (Em Ordem)
void mostrarAssinaturas(Assinatura *raiz);

// Função para buscar e mostrar a data de vencimento de uma assinatura específica
void mostrarVencimentoAssinatura(Assinatura *raiz, char *cpf);
#endif
