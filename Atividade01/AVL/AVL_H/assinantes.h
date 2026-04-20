#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h"

Assinante *aloca_assinante();
void *cadastrar_assinante(Assinante **r);
int inserir_assinante(Assinante **raiz, Assinante *novo);
int mostrar_assinantes(Assinante *raiz);
int remove_assinant(Assinante **r, char *cpf);
void liberar_arvore_assinante(Assinante *raiz);

// Funções de verificação para remoção
int eh_folha(Assinante *raiz);
Assinante *so_um_filho(Assinante *r);
int dois_filhos(Assinante *r);



#endif