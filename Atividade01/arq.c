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
    int *generosEscolhidos; //Ponteiro para armazenar o vetor com os códigos dos gêneros
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


/*
 Função: cadastrarGenero: Insere um novo gênero na lista estática, mantendo-a ordenada de forma crescente pelo 'codigo'.
 Impede o cadastro de códigos repetidos e só permite o cadastro se a árvore de livros não for vazia.
 
 * Parâmetros:
 - Genero lista[]: O vetor estático onde os gêneros serão armazenados (passado por referência como ponteiro de array).
- int *qtd: Ponteiro para a variável que controla quantos gêneros já existem no vetor, Usado passagem por referência para podermos incrementar o contador real no 'main'.
 * - int codigo, char *nome: Dados do gênero (passagem por valor e ponteiro de string).
 * - Livro *arvoreLivros: Ponteiro para a raiz da árvore de livros correspondente a este gênero.

 * Retorno:
 * - int: 1 se a inserção foi sucesso, 0 se falhou.
 */
int cadastrarGenero(Genero lista[], int *qtd, int codigo, char *nome, Livro *arvoreLivros) {
    int statusInsercao = 0;
    int i, j;

    // 1ª Validação: Verifica se ainda há espaço no vetor
    if (*qtd < MAXGENEROS) {
        
        // 2ª Validação: a árvore de livros passada não pode ser vazia
        if (arvoreLivros != NULL) {
            
            int posicaoInserir = 0;
            int codigoExiste = 0;

            // Percorre os gêneros já cadastrados para encontrar a posição correta
            // e também verifica se o código já existe
            for (i = 0; i < *qtd; i++) {
                if (lista[i].codigo == codigo) {
                    codigoExiste = 1; // Encontrou código repetido
                    break;
                }
                
                // Se o código da lista for maior que o código novo, achamos o ponto de inserção
                if (lista[i].codigo > codigo) {
                    break; 
                }
                posicaoInserir++; // Vai avançando até achar o ponto certo
            }

            // 3ª Validação: Só insere se não encontrou um código repetido
            if (codigoExiste == 0) {
                // Desloca todos os elementos à direita da 'posicaoInserir' uma casa para frente
                for (j = *qtd; j > posicaoInserir; j--) {
                    lista[j] = lista[j - 1];
                }

                // Insere os dados do novo gênero na posição correta
                lista[posicaoInserir].codigo = codigo;
                strcpy(lista[posicaoInserir].nome, nome);
                lista[posicaoInserir].arvoreLivros = arvoreLivros;

                // Incrementa a quantidade de gêneros usando o ponteiro (altera lá no main)
                (*qtd)++;

                statusInsercao = 1; 
            }
        }
    }

    return statusInsercao;
}
/* Insere uma nova forma de assinatura no final da lista dinâmica, Valida se existe pelo menos um gênero cadastrado e impede códigos de forma repetidos.
 
 Parâmetros:
 - FormaDaAssi **inicio: Ponteiro duplo para o início da lista (passagem por referência).
 - int qtdGenerosCadastrados: Quantidade de gêneros (passagem por valor) para validar a regra de que deve haver pelo menos um gênero cadastrado.
 - int codigo, livrosMensais, generosMensais: Dados numéricos da forma (passagem por valor).
 - int *vetorGeneros: Vetor contendo os códigos dos gêneros escolhidos (passagem de ponteiro de array).
  - char *tipoEncadern: String do tipo de encadernação.
  - float valorMensal, valorAnual
 
 */
int cadastrarFormaAssinatura(FormaDaAssi **inicio, int qtdGenerosCadastrados, int codigo, int livrosMensais, int generosMensais, int *vetorGeneros, char *tipoEncadern, float valorMensal, float valorAnual) {
    
    int statusInsercao = 0;

    // 1ª Validação: O usuário já deve ter cadastrado pelo menos um tipo de gênero 
    if (qtdGenerosCadastrados > 0) {
        
        // 2ª Validação: Não permitir cadastro repetido (verificando o código da forma)
        int codigoExiste = 0;
        FormaDaAssi *atual = *inicio;
        
        // Percorre a lista para procurar se o código já existe
        while (atual != NULL) {
            if (atual->codigo == codigo) {
                codigoExiste = 1; // Encontrou duplicata
                break;
            }
            atual = atual->prox;
        }

        // Se o código não existe, prossegue com a criação
        if (codigoExiste == 0) {
            
            FormaDaAssi *novaForma = (FormaDaAssi *)malloc(sizeof(FormaDaAssi));
            
            if (novaForma != NULL) {
                
                novaForma->codigo = codigo;
                novaForma->livrosMensais = livrosMensais;
                novaForma->generosMensais = generosMensais;
                strcpy(novaForma->tipoEncadern, tipoEncadern);
                novaForma->valorMensal = valorMensal;
                novaForma->valorAnual = valorAnual;
                novaForma->prox = NULL; // Como vai para o final da lista, o próximo é NULL

                // Aloca dinamicamente o vetor de gêneros escolhidos com base na quantidade informada
                novaForma->generosEscolhidos = (int *)malloc(generosMensais * sizeof(int));
                
                if (novaForma->generosEscolhidos != NULL) {
                    // Copia os códigos do vetor passado por parâmetro para a struct
                    for (int i = 0; i < generosMensais; i++) {
                        novaForma->generosEscolhidos[i] = vetorGeneros[i];
                    }

                    // Lógica para inserir na lista dinâmica
                    if (*inicio == NULL) {
                        // Se a lista estiver vazia, a nova forma será o primeiro elemento (modifica no main)
                        *inicio = novaForma;
                    } else {
                        // Se não estiver vazia, percorre até o final e conecta
                        FormaDaAssi *temp = *inicio;
                        while (temp->prox != NULL) {
                            temp = temp->prox;
                        }
                        temp->prox = novaForma;
                    }
                    
                    statusInsercao = 1;
                } else {
                    free(novaForma);
                }
            }
        }
    }

    
    return statusInsercao;
}

/// ==============================
/// FUNÇÕES DE ASSINATURAS
/// ==============================

/*
 Insere uma nova assinatura na árvore binária, organizada pelo CPF do assinante.
 * Impede cadastros de CPFs repetidos.
 * Valida obrigatoriamente se o CPF existe na árvore de Usuários e se o código existe na lista de Formas.
 * Parâmetros:
 * - Assin **raiz: Ponteiro duplo para a raiz de Assinaturas (referência, pois modifica a estrutura da árvore).
 * - Usuario *raizUsuarios: Ponteiro simples da raiz de usuários (passagem por valor, apenas para consulta/busca).
 * - FormaDaAssi *listaFormas: Ponteiro simples do início da lista (passagem por valor, apenas para consulta/busca).
 * - char *cpf, *dataAssinatura, *dataVencimento: Strings dos dados (passagem de ponteiro de array).
 * - int codigoForma, float valor: Dados numéricos (passagem por valor).

 */
int cadastrarAssinatura(Assin **raiz, Usuario *raizUsuarios, FormaDaAssi *listaFormas, char *cpf, int codigoForma, char *dataAssinatura, char *dataVencimento, float valor) {

    int statusInsercao = 0;
    
    int assinanteExiste = 0;
    int formaExiste = 0;

    // --- VALIDAÇÃO 1: O assinante existe? ---
    // Busca na árvore binária de usuários de forma iterativa
    Usuario *tempU = raizUsuarios;
    while (tempU != NULL) {
        int comp = strcmp(cpf, tempU->cpf);
        if (comp == 0) {
            assinanteExiste = 1; // Encontrou o CPF
            break;
        } else if (comp < 0) {
            tempU = tempU->esq;
        } else {
            tempU = tempU->dir;
        }
    }

    // --- VALIDAÇÃO 2: A forma de assinatura existe? ---
    // Percorre a lista dinâmica iterativamente
    FormaDaAssi *tempF = listaFormas;
    while (tempF != NULL) {
        if (tempF->codigo == codigoForma) {
            formaExiste = 1; // Encontrou o código
            break;
        }
        tempF = tempF->prox;
    }

    // Só prossegue se as duas validações forem verdadeiras
    if (assinanteExiste == 1 && formaExiste == 1) {
        
        Assin *atual = *raiz;
        Assin *pai = NULL;
        int cpfRepetido = 0;

        // --- VALIDAÇÃO 3: O CPF já tem assinatura nesta árvore? ---
        // Desce na árvore de assinaturas procurando pelo CPF para achar a folha correta
        while (atual != NULL) {
            pai = atual; // Salva o nó atual como "pai" antes de descer
            int comp = strcmp(cpf, atual->cpfUsuario);
            
            if (comp == 0) {
                cpfRepetido = 1; // CPF já tem uma assinatura cadastrada
                break;
            } else if (comp < 0) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }

        // Se o CPF não for repetido, aloca e insere o nó
        if (cpfRepetido == 0) {
            Assin *novaAssinatura = (Assin *)malloc(sizeof(Assin));
            
            if (novaAssinatura != NULL) {
               
                strcpy(novaAssinatura->cpfUsuario, cpf);
                novaAssinatura->codigoForma = codigoForma;
                strcpy(novaAssinatura->dataAssinatura, dataAssinatura);
                strcpy(novaAssinatura->dataVencimento, dataVencimento);
                novaAssinatura->valor = valor;
                
                // Filhos nulos pois é um novo nó folha
                novaAssinatura->esq = NULL;
                novaAssinatura->dir = NULL;

                // Conecta o novo nó à árvore
                if (pai == NULL) {
                    // Se pai é NULL, a árvore estava vazia
                    *raiz = novaAssinatura;
                } else {
                    // Verifica se insere na esquerda ou direita do pai encontrado
                    if (strcmp(cpf, pai->cpfUsuario) < 0) {
                        pai->esq = novaAssinatura;
                    } else {
                        pai->dir = novaAssinatura;
                    }
                }
                
                
                statusInsercao = 1;
            }
        }
    }

    return statusInsercao;
}

/*
 
 * Percorre a árvore binária de assinantes utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenados pelo CPF.
 
 * Parâmetros:
 * - Usuario *raiz: Ponteiro simples para a raiz da árvore. Escolhemos a passagem 
 * por valor (cópia do ponteiro) porque esta função serve apenas para LEITURA. 
 * Não vamos inserir ou remover nós, logo, não precisamos modificar a árvore original.
*/
void mostrarAssinantes(Usuario *raiz) {
    // Verifica se o nó atual não é nulo
    if (raiz != NULL) {
        
        // 1º Passo: Desce tudo que pode para a subárvore esquerda (CPFs menores)
        mostrarAssinantes(raiz->esq);
        
        // 2º Passo: Visita a "raiz" atual (Imprime os dados do usuário)
        printf("--------------------------------------------------\n");
        printf("CPF: %s\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("Endereco: %s\n", raiz->endereco);
        printf("Data de Nascimento: %s\n", raiz->dataNasc);
        
        // 3º Passo: Desce para a subárvore direita (CPFs maiores)
        mostrarAssinantes(raiz->dir);
    }
}

/*

 * Percorre a árvore binária de assinaturas utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenadas pelo CPF do assinante.
 *
 * Parâmetros:
  - Assin *raiz: Ponteiro simples para a raiz da árvore de assinaturas. Usamos passagem 
 por valor (cópia do ponteiro) porque o objetivo é apenas exibir os dados na tela (LEITURA),
 sem alterar a estrutura ou os nós da árvore original.
 
 */
void mostrarAssinaturas(Assin *raiz) {
    
    if (raiz != NULL) {
        
        // 1º Passo: Visita a subárvore esquerda (CPFs menores)
        mostrarAssinaturas(raiz->esq);
        
        // 2º Passo: Imprime os dados do nó atual (a raiz deste momento)
        printf("--------------------------------------------------\n");
        printf("CPF do Assinante: %s\n", raiz->cpfUsuario);
        printf("Codigo da Forma: %d\n", raiz->codigoForma);
        printf("Data da Assinatura: %s\n", raiz->dataAssinatura);
        printf("Data de Vencimento: %s\n", raiz->dataVencimento);
        printf("Valor: R$ %.2f\n", raiz->valor);
        
        // 3º Passo: Visita a subárvore direita (CPFs maiores)
        mostrarAssinaturas(raiz->dir);
    }
}