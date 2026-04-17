#ifndef ASSINATURAS_H
#define ASSINATURAS_H

#include "../AVL_H/structs.h"

Assinatura* alocar_assinatura();
void cadastrar_assinatura(Assinatura **r);
int inserir_assinatura(Assinatura **raiz, Assinatura *novo);
void mostrar_assinaturas(Assinatura *raiz);
int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf);
Assinatura* buscar_assinatura(Assinatura *raiz, char *cpf);
int remover_no_assinatura(Assinatura **r, char *cpf);

#endif