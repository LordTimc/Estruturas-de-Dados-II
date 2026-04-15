#ifndef ASSINATURAS_H
#define ASSINATURAS_H

#include "structs.h"

Assinatura* alocar_assinatura();
void cadastrar_assinatura(Assinatura **r);
int inserir_assinatura(Assinatura **raiz, Assinatura *novo);
void mostrar_assinaturas(Assinatura *raiz);
int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf);

#endif