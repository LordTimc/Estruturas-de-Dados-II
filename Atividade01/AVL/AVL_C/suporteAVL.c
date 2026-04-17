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
int altura_usu(Assinante *no) { return (no == NULL) ? 0 : no->altura; }
int fb_usu(Assinante *no) { return (no == NULL) ? 0 : altura_usu(no->esq) - altura_usu(no->dir); }

Assinante* rot_dir_usu(Assinante *y) {
    Assinante *x = y->esq;
    Assinante *T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = maior(altura_usu(y->esq), altura_usu(y->dir)) + 1;
    x->altura = maior(altura_usu(x->esq), altura_usu(x->dir)) + 1;
    return x;
}

Assinante* rot_esq_usu(Assinante *x) {
    Assinante *y = x->dir;
    Assinante *T2 = y->esq;
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



// ================= BALANCEAMENTO ASSINATURAS =================
Assinatura* balancear_ass(Assinatura *no) {
    Assinatura *retorno = no;

    if (no != NULL) {
        no->altura = maior(altura_ass(no->esq), altura_ass(no->dir)) + 1;
        int fb = fb_ass(no);

        if (fb > 1) {
            if (fb_ass(no->esq) >= 0) {
                retorno = rot_dir_ass(no); 
            } else {
                no->esq = rot_esq_ass(no->esq); 
                retorno = rot_dir_ass(no);
            }
        } else if (fb < -1) {
            if (fb_ass(no->dir) <= 0) {
                retorno = rot_esq_ass(no); 
            } else {
                no->dir = rot_dir_ass(no->dir); 
                retorno = rot_esq_ass(no);
            }
        }
    }
    return retorno; 
}

// ================= BALANCEAMENTO USUÁRIOS =================
Assinante* balancear_assinante(Assinante *no) {
    Assinante *retorno = no;

    if (no != NULL) {
        no->altura = maior(altura_usu(no->esq), altura_usu(no->dir)) + 1;
        int fb = fb_usu(no);

        if (fb > 1) {
            if (fb_usu(no->esq) >= 0) {
                retorno = rot_dir_usu(no);
            } else {
                no->esq = rot_esq_usu(no->esq);
                retorno = rot_dir_usu(no);
            }
        } else if (fb < -1) {
            if (fb_usu(no->dir) <= 0) {
                retorno = rot_esq_usu(no);
            } else {
                no->dir = rot_dir_usu(no->dir);
                retorno = rot_esq_usu(no);
            }
        }
    }
    return retorno;
}

// ================= BALANCEAMENTO LIVROS =================
Livro* balancear_liv(Livro *no) {
    Livro *retorno = no;

    if (no != NULL) {
        no->altura = maior(altura_liv(no->esq), altura_liv(no->dir)) + 1;
        int fb = fb_liv(no);

        if (fb > 1) {
            if (fb_liv(no->esq) >= 0) {
                retorno = rot_dir_liv(no);
            } else {
                no->esq = rot_esq_liv(no->esq);
                retorno = rot_dir_liv(no);
            }
        } else if (fb < -1) {
            if (fb_liv(no->dir) <= 0) {
                retorno = rot_esq_liv(no);
            } else {
                no->dir = rot_dir_liv(no->dir);
                retorno = rot_esq_liv(no);
            }
        }
    }
    return retorno;
}