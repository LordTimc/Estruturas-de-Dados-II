#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/livros.h"
#include "../ABB_H/auxiliares.h"


Livro *aloca_livro(char *isbn, char *titulo, char *autor, char *editora, int edicao, int ano_publica){
    // Aloca espaço na memória para o novo livro
    Livro *novo_livro = (Livro *)malloc(sizeof(Livro));
        
    // Verifica se a memória foi alocada com sucesso
    if (novo_livro != NULL) {
        strcpy(novo_livro->isbn, isbn);
        strcpy(novo_livro->titulo, titulo);
        strcpy(novo_livro->autor, autor);
        strcpy(novo_livro->editora, editora);
        novo_livro->edicao = edicao;
        novo_livro->ano_publica = ano_publica;
        
        // Como é um nó folha recém-criado, seus filhos são NULL
        novo_livro->esq = NULL;
        novo_livro->dir = NULL;
    }
    return(novo_livro);
}


Livro *cadastrar_livro(Livro *livro){
    char isbn[3];
    char *titulo = NULL;
    char *autor = NULL;
    char *editora = NULL;
    int edicao;
    int ano_publica;

    int cadastrou = 0;

    printf("==== Informacoes do livro ====");

    if(pega_isbn(isbn)){

        printf("\nDigite o titulo: ");
        titulo = leitura_de_string();
        
        if(titulo != NULL){
            autor = leitura_de_string(); //endreco
            editora = leitura_de_string(); // endereco
            edicao = pega_edicao(edicao); // isdigit
            ano_publica = pega_ano_publica(); // digitar_ano
            if(autor != NULL && editora != NULL){
                livro = aloca_livro(isbn, titulo, autor, editora, edicao, ano_publica);
                cadastrou = 1;

                free(titulo);
                free(autor);
                free(editora);
            }
        }
    }

    if(!cadastrou){
        if(titulo) free(titulo);
        if(autor) free(autor);
        if(editora) free(editora);
    }
    return livro;
}

/*
 * Insere um novo livro na Árvore Binária de Busca utilizando o ISBN como chave.
Parâmetros:
 * - Livro **r: Ponteiro duplo para a raiz da árvore de livros. Usamos passagem 
 * por referência para que a modificação do ponteiro (ao adicionar um novo nó) reflita diretamente na variável original lá no `main`.
 * - char *isbn, *titulo, *autor, *editora: Strings com os dados textuais do livro.
 * - int edicao, anoPublica: Dados numéricos do livro passados por valor.
 */
int inserir_livro(Livro **r, Livro *novo){
    int inseriu = 1;
    // Se o ponteiro atual for NULL, encontramos a posição correta para inserir
    if (*r == NULL) 
        *r = novo;
    else if(strcmp(novo->isbn, (*r)->isbn) == 0){
        // A função strcmp compara os dois ISBN. Retorna < 0 se a primeira for menor, > 0 se for maior, e 0 se forem iguais.
        // comparacao == 0 significa que o ISBN já existe na árvore
        // Não permite cadastro repetido, logo, o inseriu se mantém 0 (falha)
        free(novo);
        novo = NULL;
        inseriu = 0;
    } else if(strcmp(novo->isbn, (*r)->isbn) < 0){
        // Se a árvore não está vazia e o ISBN é "menor", vai para a subárvore esquerda.
        inseriu = inserir_assinante(&(*r)->esq, novo);
    } else if (strcmp(novo->isbn, (*r)->isbn) > 0){
        // Se o ISBN é "maior", vai para a subárvore direita
        inseriu = inserir_assinante(&(*r)->dir, novo);
    }
    return inseriu;
}


/*
 * Função Auxiliar: mostrarLivrosDaArvore
 
  Percorre uma árvore binária de livros utilizando o percurso "Em Ordem" 
  (Esquerda -> Raiz -> Direita), garantindo que sejam impressos ordenados pelo ISBN.
 
  Parâmetros:
 - Livro *raiz: Ponteiro simples para a raiz da árvore de livros (passagem por valor).
 
 */
int mostrar_livros_da_arvore(Livro *r){
    int mostrou = 0;
    if (r != NULL) {
        // 1. Visita a subárvore esquerda
        mostrou = mostrar_livros_da_arvore(r->esq);
        
        // 2. Imprime os dados do livro atual
        printf("--------------------------------------------------\n");
        printf("ISBN: %s\n", r->isbn);
        printf("Titulo: %s\n", r->titulo);
        printf("Autor: %s\n", r->autor);
        printf("Editora: %s\n", r->editora);
        printf("Edicao: %d\n", r->edicao);
        printf("Ano de Publicacao: %dª\n", r->ano_publica);
        
        // 3. Visita a subárvore direita
        mostrou = mostrar_livros_da_arvore(r->dir);
        mostrou = 1;
    }
    return mostrou;
}

/*
 * Função Principal: mostrarLivrosPorGenero
 Percorre a lista estática de gêneros procurando pelo código informado.
 Se encontrar, chama a função auxiliar para imprimir a árvore de livros dele.
 
 *Parâmetros:
  - Genero lista[]: O vetor de gêneros (passagem para leitura).
  - int qtd: Quantidade atual de gêneros cadastrados (passagem por valor).
  - int codigoGenero: O código do gênero que o usuário deseja buscar (passagem por valor).
 
 */
void mostrar_livros_por_genero(Genero lista[], int qtd, int codigo_genero) {
    int encontrou_genero = 0;

    // Percorre o vetor de gêneros
    for (int i = 0; i < qtd; i++) {
        // Verifica se é o gênero que estamos procurando
        if (lista[i].codigo == codigo_genero) {
            encontrou_genero = 1;
            
            printf("\n--- Livros do Genero: %s ---\n", lista[i].nome);
            
            // Verifica se a árvore de livros deste gênero está vazia
            if (lista[i].arvore_livros == NULL) {
                printf("Nenhum livro cadastrado nesta arvore.\n");
            } else {
                // Chama a função auxiliar para imprimir os livros
                mostrar_livros_da_arvore(lista[i].arvore_livros);
            }
            
            // Como já encontrou o gênero, podemos parar a busca no vetor
            break; 
        }
    }

    // Se o laço terminar e a flag continuar 0, o gênero não existe
    if (encontrou_genero == 0) {
        printf("Erro: Genero com o codigo %d nao foi encontrado.\n", codigo_genero);
    }
}