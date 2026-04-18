#ifndef ASSINATURAS_H
#define ASSINATURAS_H

#include "structs.h"

Assinatura* alocar_assinatura();
void cadastrar_assinatura(Assinatura **r);
int inserir_assinatura(Assinatura **raiz, Assinatura *novo);
void mostrar_assinaturas(Assinatura *raiz);
int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf);
Assinatura* buscar_assinatura(Assinatura *raiz, char *cpf);

int no_sem_filho_assinatura(Assinatura *raiz);
Assinatura *so_um_filho_assinatura(Assinatura *r);
int dois_filhos_assinatura(Assinatura *r);
int remover_no_assinatura(Assinatura **r, char *cpf);

#endif