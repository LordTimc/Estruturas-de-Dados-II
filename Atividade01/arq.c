#include <stdio.h>
#include <stdlib.h>

/// ==============================
/// ÁRVORE DE USUÁRIOS (ASSINANTES)
/// ==============================

typedef struct usuario {
    char cpf[15];
    char nome[100];
    char endereco[150];
    char dataNasc[11];

    struct usuario *esq;
    struct usuario *dir;
} Usuario;


/// =====================================
/// LISTA DINÂMICA DE FORMAS DE ASSINATURA
/// =====================================

typedef struct formaAss {
    int codigo;
    int livrosMensais;
    int generosMensais;
    char tipoEncadern[50];
    float valorMensal;
    float valorAnual;

    struct formaAss *prox;
} FormaDaAssi;


/// ==============================
/// ÁRVORE DE ASSINATURAS
/// ==============================

typedef struct assinatura {
    char cpfUsuario[15];              // referência ao usuário
    int codigoForma;                 // referência à forma de assinatura
    char dataAssinatura[11];
    char dataVencimento[11];
    float valor;

    struct assinatura *esq;
    struct assinatura *dir;
} Assin;


/// ==============================
/// ÁRVORE DE LIVROS
/// ==============================

typedef struct livro {
    char isbn[20];
    char titulo[100];
    char autor[100];
    char editora[100];
    int edicao;
    int anoPublica;

    struct livro *esq;
    struct livro *dir;
} Livro;


/// ======================================
/// LISTA ESTÁTICA DE GÊNEROS (VETOR FIXO)
/// ======================================

#define MAXGENEROS 20

typedef struct genero {
    int codigo;
    char nome[50];
    Livro *arvoreLivros;   // ponteiro para árvore de livros daquele gênero
} Genero;

Genero listaGeneros[MAXGENEROS];
