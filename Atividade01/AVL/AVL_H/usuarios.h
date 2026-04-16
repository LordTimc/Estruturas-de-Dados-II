#ifndef USUARIOS_H
#define USUARIOS_H

#include "../AVL_H/structs.h"

Usuario *aloca_assinante(char *cpf, char *nome, char *endereco, Data data_nascimento);
Usuario *cadastrar_assinante(Usuario *raiz);
int inserir_assinante(Usuario **raiz, Usuario *novo);
int mostrar_assinantes(Usuario *raiz);
int remove_assinant(Usuario **r, char *cpf);
void liberar_arvore_usuario(Usuario *raiz);

// Funções de verificação para remoção
int no_sem_filho(Usuario *raiz);
Usuario *so_um_filho(Usuario *r);
int dois_filhos(Usuario *r);

#endif