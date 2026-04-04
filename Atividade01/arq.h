#ifndef ARQ_h
#define ARQ_H
#define MAXGENEROS 20

typedef struct usuario Usuario;
typedef struct formaAss FormaDaAssi;
typedef struct assinatura Assin;
typedef struct livro Livro;
typedef struct genero Genero;


// Função para cadastrar um novo assinante na árvore binária
int cadastrarAssinante(Usuario **raiz, char *cpf, char *nome, char *endereco, char *dataNasc);

// Função para cadastrar um novo livro na árvore binária
int cadastrarLivro(Livro **raiz, char *isbn, char *titulo, char *autor, char *editora, int edicao, int anoPublica);

// Função para cadastrar um novo gênero na lista estática ordenada
int cadastrarGenero(Genero lista[], int *qtd, int codigo, char *nome, Livro *arvoreLivros);
#endif
