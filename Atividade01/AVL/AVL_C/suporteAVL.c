#include <stdio.h>
#include <stdlib.h>
#include "../AVL_H/suporteAVL.h"

int maior(int a, int b) { return (a > b) ? a : b; }

// ================= ASSINATURAS =================
int altura_ass(Assinatura *no) { return (no == NULL) ? 0 : no->altura; }
int fb_ass(Assinatura *no) { return (no == NULL) ? 0 : altura_ass(no->esq) - altura_ass(no->dir); }

Assinatura* rot_dir_ass(Assinatura *y) {
    Assinatura *x = y->esq;
    Assinatura *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = maior(altura_ass(y->esq), altura_ass(y->dir)) + 1;
    x->altura = maior(altura_ass(x->esq), altura_ass(x->dir)) + 1;
    return x;
}

Assinatura* rot_esq_ass(Assinatura *x) {
    Assinatura *y = x->dir;
    Assinatura *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = maior(altura_ass(x->esq), altura_ass(x->dir)) + 1;
    y->altura = maior(altura_ass(y->esq), altura_ass(y->dir)) + 1;
    return y;
}

// ================= USUÁRIOS =================
int altura_usu(Usuario *no) { return (no == NULL) ? 0 : no->altura; }
int fb_usu(Usuario *no) { return (no == NULL) ? 0 : altura_usu(no->esq) - altura_usu(no->dir); }

Usuario* rot_dir_usu(Usuario *y) {
    Usuario *x = y->esq;
    Usuario *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = maior(altura_usu(y->esq), altura_usu(y->dir)) + 1;
    x->altura = maior(altura_usu(x->esq), altura_usu(x->dir)) + 1;
    return x;
}

Usuario* rot_esq_usu(Usuario *x) {
    Usuario *y = x->dir;
    Usuario *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = maior(altura_usu(x->esq), altura_usu(x->dir)) + 1;
    y->altura = maior(altura_usu(y->esq), altura_usu(y->dir)) + 1;
    return y;
}

// ================= LIVROS =================
int altura_liv(Livro *no) { return (no == NULL) ? 0 : no->altura; }
int fb_liv(Livro *no) { return (no == NULL) ? 0 : altura_liv(no->esq) - altura_liv(no->dir); }

Livro* rot_dir_liv(Livro *y) {
    Livro *x = y->esq;
    Livro *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = maior(altura_liv(y->esq), altura_liv(y->dir)) + 1;
    x->altura = maior(altura_liv(x->esq), altura_liv(x->dir)) + 1;
    return x;
}

Livro* rot_esq_liv(Livro *x) {
    Livro *y = x->dir;
    Livro *T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = maior(altura_liv(x->esq), altura_liv(x->dir)) + 1;
    y->altura = maior(altura_liv(y->esq), altura_liv(y->dir)) + 1;
    return y;
}