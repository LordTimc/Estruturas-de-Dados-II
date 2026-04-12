#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct data_nasci data_nasci;
typedef struct usuario Usuario;
typedef struct forma_da_ass forma_da_ass;
typedef struct assinatura Assinatura;
typedef struct livro Livro;
typedef struct genero Genero;


// STRUCT DA DATA DE NASCIMENTO
typedef struct data_nasci {
    int dia;
    int mes;
    int ano;
} data_nasci;

// ÁRVORE DE USUÁRIOS (ASSINANTES)
typedef struct usuario {
    char cpf[12];
    char nome[100];
    char endereco[100];
    data_nasci data;

    struct usuario *esq, *dir;
} Usuario;


// LISTA DINÂMICA DE FORMAS DE ASSINATURA
typedef struct forma_ass {
    int codigo;
    int qtd_livros_mensais;
    int qtd_generos_mensais;
    int *generos_escolhidos; //Ponteiro para armazenar o vetor com os códigos dos gêneros
    char tipo_encadern[50];
    float valor_mensal;
    float valor_anual;

    struct forma_ass *prox;
} forma_ass;


// ÁRVORE DE ASSINATURAS
typedef struct assinatura {

    char cpf_usuario[15];              // referência ao usuário
    int codigo_forma;                 // referência à forma de assinatura
    char data_assinatura[11];
    char data_vencimento[11];
    float valor;

    struct assinatura *esq, *dir;
} Assinatura;


// ÁRVORE DE LIVROS
typedef struct livro {

    char isbn[2];
    char titulo[100];
    char autor[100];
    char editora[100];
    int edicao;
    int ano_publica;

    struct livro *esq, *dir;
} Livro;


// LISTA ESTÁTICA DE GÊNEROS (VETOR FIXO)
#define MAX_GENEROS 5

typedef struct genero {
    int codigo;
    char nome[50];
    Livro *colecao_livros;   // ponteiro para árvore de livros daquele gênero
} Genero;

Genero lista_generos[MAX_GENEROS];

#endif

