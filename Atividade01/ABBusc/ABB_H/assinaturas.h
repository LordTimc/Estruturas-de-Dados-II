#ifndef ARQ_h
#define ARQ_H
#define MAXGENEROS 5

#include "structs.h"

// Função para alocar a memoria de uma assinatura
Assinatura* alocar_assinatura();

// Função para cadastrar uma assinatura na árvore binária
void cadastrar_assinatura(Assinatura **r);

// Função para inserir assinatura
int *inserir_assinatura(Assinatura **raiz, Assinatura *novo);

//função que verifica se o usuario possui alguma assinatura
int possui_assinatura_vencida(Assinatura *raiz, char *cpf);

// Função para mostrar todas as assinaturas cadastradas na árvore (Em Ordem)
void mostrar_assinaturas(Assinatura *raiz);

// Função para buscar e mostrar a data de vencimento de uma assinatura específica
int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf);
#endif


// Supondo que na main você tenha: Assinatura *raiz_assinaturas = NULL;
// cadastrar_assinatura(&raiz_assinaturas);