#ifndef USUARIOS_H
#define USUARIOS_H

#include "structs.h"

Assinante *aloca_assinante(char *cpf, char *nome, char *endereco, Data data_nascimento);
Assinante *cadastrar_assinante(Assinante *raiz);
int inserir_assinante(Assinante **raiz, Assinante *novo);
int mostrar_assinantes(Assinante *raiz);
int remove_assinant(Assinante **r, char *cpf);
void liberar_arvore_usuario(Assinante *raiz);

// Funções de verificação para remoção
int no_sem_filho(Assinante *raiz);
Assinante *so_um_filho(Assinante *r);
int dois_filhos(Assinante *r);



#endif