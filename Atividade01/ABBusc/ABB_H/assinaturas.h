#ifndef ARQ_h
#define ARQ_H
#define MAXGENEROS 20

#include "structs.h"


// Função para cadastrar uma assinatura na árvore binária
int cadastrarAssinatura(Assin **raiz, Usuario *raizUsuarios, FormaDaAssi *listaFormas, char *cpf, int codigoForma, char *dataAssinatura, char *dataVencimento, float valor);


// Função para mostrar todas as assinaturas cadastradas na árvore (Em Ordem)
void mostrarAssinaturas(Assin *raiz);

// Função para buscar e mostrar a data de vencimento de uma assinatura específica
void mostrarVencimentoAssinatura(Assin *raiz, char *cpf);
#endif
