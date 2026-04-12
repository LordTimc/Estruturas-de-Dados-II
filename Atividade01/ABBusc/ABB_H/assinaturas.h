#ifndef ARQ_h
#define ARQ_H
#define MAXGENEROS 5

#include "structs.h"

// Função para alocar a memoria de uma assinatura
Assinatura* alocar_assinatura();

// Função para cadastrar uma assinatura na árvore binária
int cadastrar_assinatura(Assinatura **raiz, Usuario *raiz_usuarios, forma_ass *lista_formas, char *cpf, int codigo_forma, char *data_assinatura, char *data_vencimento, float valor);


// Função para mostrar todas as assinaturas cadastradas na árvore (Em Ordem)
void mostrarAssinaturas(Assinatura *raiz);

// Função para buscar e mostrar a data de vencimento de uma assinatura específica
void mostrarVencimentoAssinatura(Assinatura *raiz, char *cpf);
#endif
