#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct data_nasci Data;
typedef struct usuario Usuario;
typedef struct forma_ass forma_ass;
typedef struct assinatura Assinatura;
typedef struct livro Livro;
typedef struct genero Genero;

// STRUCT DA DATA DE NASCIMENTO
typedef struct data_nasci {
    int dia;
    int mes;
    int ano;
} Data;

// ÁRVORE DE USUÁRIOS (ASSINANTES) - [AVL]
typedef struct usuario {
    char cpf[12];
    char nome[100];
    char endereco[100];
    Data nascimento;
    int altura; // Necessário para AVL

    struct usuario *esq, *dir;
} Usuario;

// ÁRVORE DE LIVROS - [AVL]
typedef struct livro {
    char isbn[3]; // Ajustado para 3 para caber o '\0'
    char titulo[100];
    char autor[100];
    char editora[100];
    int edicao;
    int ano_publica;
    int altura; // Necessário para AVL

    struct livro *esq, *dir;
} Livro;

// LISTA ESTÁTICA DE GÊNEROS (VETOR FIXO)
#define MAX_GENEROS 5
typedef struct genero {
    int codigo;
    char nome[50];
    Livro *colecao_livros;   
} Genero;

Genero lista_generos[MAX_GENEROS];

// LISTA DINÂMICA DE FORMAS DE ASSINATURA
typedef struct forma_ass {
    int codigo;
    int qtd_livros_mensais;
    int qtd_generos_mensais;
    int *generos_escolhidos; 
    char tipo_encadern[50];
    float valor_mensal;
    float valor_anual;

    struct forma_ass *prox;
} forma_ass;

// ÁRVORE DE ASSINATURAS - [AVL]
typedef struct assinatura {
    char cpf_usuario[12];              
    int codigo_forma;                 
    Data data_assinatura;
    Data data_vencimento;
    float valor;
    int altura; // Necessário para AVL

    struct assinatura *esq, *dir;
} Assinatura;

#endif