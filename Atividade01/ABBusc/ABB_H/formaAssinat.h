#include "structs.h"


// Função para cadastrar uma nova forma de assinatura na lista dinâmica
int cadastrarFormaAssinatura(FormaDaAssi **inicio, int qtdGenerosCadastrados, int codigo, int livrosMensais, int generosMensais, int *vetorGeneros, char *tipoEncadern, float valorMensal, float valorAnual);

// Função para mostrar assinaturas filtradas por um código de forma específico
void mostrarAssinaturasPorForma(Assin *raiz, int codigoForma);

// Função para mostrar todas as formas de assinatura cadastradas
void mostrarFormasAssinatura(FormaDaAssi *inicio);