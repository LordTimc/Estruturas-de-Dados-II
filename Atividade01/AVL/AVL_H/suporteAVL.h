#ifndef SUPORTE_AVL_H
#define SUPORTE_AVL_H

#include "structs.h"


int maior(int a, int b);

// Suporte para Assinaturas
int altura_ass(Assinatura *no);
int fb_ass(Assinatura *no);
Assinatura* rot_dir_ass(Assinatura *y);
Assinatura* rot_esq_ass(Assinatura *x);

// Suporte para Usuários
int altura_usu(Assinante *no);
int fb_usu(Assinante *no);
Assinante* rot_dir_usu(Assinante *y);
Assinante* rot_esq_usu(Assinante *x);

// Suporte para Livros
int altura_liv(Livro *no);
int fb_liv(Livro *no);
Livro* rot_dir_liv(Livro *y);
Livro* rot_esq_liv(Livro *x);

//Funções balanceamento
Assinatura* balancear_ass(Assinatura *no);
Assinante* balancear_usu(Assinante *no);
Livro* balancear_liv(Livro *no);

#endif