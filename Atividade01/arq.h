#ifndef ARQ_h
#define ARQ_H

typedef struct usuario Usuario;
typedef struct formaAss FormaDaAssi;
typedef struct assinatura Assin;
typedef struct livro Livro;
typedef struct genero Genero;


// Função para cadastrar um novo assinante na árvore binária
int cadastrarAssinante(Usuario **raiz, char *cpf, char *nome, char *endereco, char *dataNasc);
#endif
