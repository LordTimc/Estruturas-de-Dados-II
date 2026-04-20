#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/livros.h"
#include "../ABB_H/auxiliares.h"


Livro *aloca_livro(){
    Livro *novo_livro = (Livro *)malloc(sizeof(Livro));
    if (novo_livro != NULL) {
        strcpy(novo_livro->isbn, "");
        strcpy(novo_livro->titulo, "");
        strcpy(novo_livro->autor, "");
        strcpy(novo_livro->editora, "");
        novo_livro->edicao = 0;
        novo_livro->ano_publica = 0;
        
        novo_livro->esq = NULL;
        novo_livro->dir = NULL;
    }else {
        printf("Erro! Falha na alocacao de memoria para Assinante.\n");
    }
    return(novo_livro);
}


void *cadastrar_livro(Livro **livro){
    char isbn[3];
    char *titulo = NULL;
    char *autor = NULL;
    char *editora = NULL;
    int edicao;
    int ano_publica;
    int cadastrou = 0;
    Livro *novo_li = NULL;

    printf("==== Informacoes do livro ====");

    if(pega_isbn(isbn)){
        novo_li = aloca_livro();

        printf("\nDigite o titulo: ");
        titulo = leitura_de_string();
        
        if(titulo != NULL){
            printf("Autor: ");
            autor = leitura_de_string(); 
            printf("Editora: ");
            editora = leitura_de_string(); 
            printf("Edicao: ");
            edicao = num_inteiro(); 
            printf("Ano de publicacao: ");
            ano_publica = num_inteiro(); 

            if(autor != NULL && editora != NULL){
                
                strcpy(novo_li->isbn, isbn);
                strcpy(novo_li->titulo, titulo);
                strcpy(novo_li->autor, autor);
                novo_li->edicao = edicao;
                novo_li->ano_publica = ano_publica;

                cadastrou = 1;
            }
        }
    }
    if (cadastrou) {
        if (inserir_livro(&(*livro), novo_li)) {
            printf("Assinante cadastrado com sucesso!\n");
        } else {
            printf("Erro: Nao foi possivel inserir na arvore.\n");
        }
    } else {
        if (novo_li != NULL) free(novo_li);
        printf("Cadastro de assinante cancelado ou dados invalidos.\n");
    }

    // Liberação de memória auxiliar
    if (titulo) free(titulo);
    if (autor) free(autor);
    if (editora) free(editora);
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
    int inseriu = 0;
    
    if (*r == NULL) {
        *r = novo;
        inseriu = 1;
    } else {
        if(strcmp(novo->isbn, (*r)->isbn) == 0){
            free(novo);
            inseriu = 0;
        } else if(strcmp(novo->isbn, (*r)->isbn) < 0){
            // CORREÇÃO: Estava chamando inserir_assinante!
            inseriu = inserir_livro(&(*r)->esq, novo);
        } else {
            inseriu = inserir_livro(&(*r)->dir, novo);
        }
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
/*
 * Função Principal: mostrar_livros_por_genero
 * Versão sem comandos de salto (break/continue).
 */
void mostrar_livros_por_genero(Genero lista[], int qtd_genero, int codigo_genero) {
    int encontrou_genero = 0;
    int i = 0;

    // O laço continua enquanto não percorrer todo o vetor E não encontrar o gênero
    while (i < qtd_genero && !encontrou_genero) {
        
        // Verifica se o código atual corresponde ao buscado
        if (lista[i].codigo == codigo_genero) {
            encontrou_genero = 1; // Altera a flag para 1, o que fará o laço parar na próxima verificação
            
            printf("\n--- Livros do Genero: %s ---\n", lista[i].nome);
            
            /* * Chamamos a função auxiliar e verificamos o retorno.
             * Se a árvore estiver vazia, ela retorna 0.
             */
            int imprimiu = mostrar_livros_da_arvore(lista[i].colecao_livros);
            
            if (imprimiu == 0) {
                printf("Nenhum livro cadastrado neste genero.\n");
            }
        }
        i++; 
    }

    // Validação final caso o gênero não exista no cadastro
    if (!encontrou_genero) {
        printf("Erro: Genero com o codigo %d nao foi encontrado.\n", codigo_genero);
    }
}

// Função para liberar os nó e depois a raiz
void liberar_arvore_livros(Livro *raiz){
    if (raiz != NULL) {
        liberar_arvore_livros(raiz->esq);
        liberar_arvore_livros(raiz->dir);
        free(raiz);
    }
}