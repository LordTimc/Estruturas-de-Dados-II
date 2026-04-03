#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arq.h"

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


/* **raiz: Ponteiro duplo para a raiz da árvore. Escolhido (passagem por referência) 
  porque precisamos modificar o ponteiro real da árvore no `main` quando alocamos um novo nó.
 * - char *cpf, *nome, *endereco, *dataNasc: Dados do usuário a serem inseridos (passagem por valor/ponteiro de array).*/
int cadastrarAssinante(Usuario **raiz, char *cpf, char *nome, char *endereco, char *dataNasc) {
    // Variável única de retorno para saber se deu certo cadastrar.
    int statusInsercao = 0; 

    // Verifica se chegamos em um nó folha/vazio
    if (*raiz == NULL) {
        // Aloca espaço na memória para o novo usuário
        Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
        
        if (novoUsuario != NULL) {
            strcpy(novoUsuario->cpf, cpf);
            strcpy(novoUsuario->nome, nome);
            strcpy(novoUsuario->endereco, endereco);
            strcpy(novoUsuario->dataNasc, dataNasc);
            
            novoUsuario->esq = NULL;
            novoUsuario->dir = NULL;

            // Modifica o ponteiro da árvore original (por referência) para apontar para o novo nó
            *raiz = novoUsuario; 
            
            // Define o status como sucesso
            statusInsercao = 1;  
        }
    } else {
        // A árvore não está vazia.
        // A função strcmp compara duas strings. Retorna < 0 se a primeira for menor, > 0 se for maior, e 0 se forem iguais.
        int comparacao = strcmp(cpf, (*raiz)->cpf);

        if (comparacao < 0) {
            // O CPF é "menor" alfabeticamente, vai para a subárvore esquerda
            statusInsercao = cadastrarAssinante(&((*raiz)->esq), cpf, nome, endereco, dataNasc);
        } else if (comparacao > 0) {
            // O CPF é "maior" alfabeticamente, vai para a subárvore direita
            statusInsercao = cadastrarAssinante(&((*raiz)->dir), cpf, nome, endereco, dataNasc);
        } else {
            // comparacao == 0 significa que o CPF já existe na árvore
            // Não permite cadastro repetido, logo, o status se mantém 0 (falha)
            statusInsercao = 0; 
        }
    }

    return statusInsercao; 
}



/*
 * Insere um novo livro na Árvore Binária de Busca utilizando o ISBN como chave.
Parâmetros:
 * - Livro **raiz: Ponteiro duplo para a raiz da árvore de livros. Usamos passagem 
 * por referência para que a modificação do ponteiro (ao adicionar um novo nó) reflita diretamente na variável original lá no `main`.
 * - char *isbn, *titulo, *autor, *editora: Strings com os dados textuais do livro.
 * - int edicao, anoPublica: Dados numéricos do livro passados por valor.
 */
int cadastrarLivro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int anoPublica) {
    int statusInsercao = 0;

    // Se o ponteiro atual for NULL, encontramos a posição correta para inserir
    if (*raiz == NULL) {
        // Aloca memória para o novo livro
        Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
        
        // Verifica se a memória foi alocada com sucesso
        if (novoLivro != NULL) {
            strcpy(novoLivro->isbn, isbn);
            strcpy(novoLivro->titulo, titulo);
            strcpy(novoLivro->autor, autor);
            strcpy(novoLivro->editora, editora);
            novoLivro->edicao = edicao;
            novoLivro->anoPublica = anoPublica;
            
            // Como é um nó folha recém-criado, seus filhos são NULL
            novoLivro->esq = NULL;
            novoLivro->dir = NULL;

            *raiz = novoLivro;
                      
            statusInsercao = 1;
        }
    } else {
        // Se a árvore não estiver vazia
        // Compara o ISBN recebido com o ISBN do nó atual
        int comparacao = strcmp(isbn, (*raiz)->isbn);

        if (comparacao < 0) {
            // Se o ISBN for "menor", desce para a subárvore esquerda
            statusInsercao = cadastrarLivro(&((*raiz)->esq), isbn, titulo, autor, editora, edicao, anoPublica);
        } else if (comparacao > 0) {
            // Se o ISBN for "maior", desce para a subárvore direita
            statusInsercao = cadastrarLivro(&((*raiz)->dir), isbn, titulo, autor, editora, edicao, anoPublica);
        } else {
            // Se a comparação for 0, os ISBNs são iguais. 
            // O cadastro é repetido, então a função não insere nada e o status continua 0.
            statusInsercao = 0;
        }
    }

    return statusInsercao;
}