#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/generos.h"
#include "../ABB_H/auxiliares.h"

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
/* * Função: cadastrar_genero_estatico

 * Equivalente à alocação de um nó, mas aplicada a um vetor fixo.

 */

 // Função para criar um novo gênero na lista estática não ordenada
Genero criar_genero(int codigo_livro, char *nome_genero){
    Genero novo;
    
    novo.codigo = codigo_livro;
    strcpy(novo.nome, nome_genero);
    // Todo gênero nasce com uma árvore de livros vazia
    novo.colecao_livros = NULL; 
    
    return novo; // Retorna a struct preenchida
}

// Função para inserir o genero na lista estática
int inserir_genero(Genero lista[], int *qtd_gen, Genero novo_genero){
    int inseriu = 0;
    if (*qtd_gen < MAX_GENEROS) {
        // A inserção é apenas copiar a struct para a vaga livre
        lista[*qtd_gen] = novo_genero;
        (*qtd_gen)++;
        inseriu = 1; // Sucesso
    }
    
    printf("Erro! Limite maximo atingido.\n");
    return inseriu; // Falha
}

// Função para verificar se o genero já existe
int existe_livro_cad(Genero lista[], int qtd_gen, int codigo_livro){
    int existe = 0;
    for (int i = 0; i < qtd_gen; i++) {
        if (lista[i].codigo == codigo_livro) {
            existe = 1;
        }
    }
    return existe;
}



/*
 Percorre o vetor estático de gêneros do início até a quantidade atual cadastrada.
 Imprime o código e o nome de cada gênero.
 
  Parâmetros:
  - Genero lista[]: O vetor estático onde os gêneros estão armazenados. Em C, 
  passar o vetor dessa forma já passa o endereço inicial para leitura.
  - int qtd: A quantidade atual de gêneros cadastrados (passagem por valor). 
 *Escolhemos a passagem por valor porque a função serve apenas para LEITURA. 
  Não vamos incrementar ou alterar a quantidade, então não precisamos de ponteiro.
 *
 */
void mostrar_generos(Genero lista[], int qtd_gen){
    printf("\n--- Lista de Generos Cadastrados ---\n");

    if (qtd_gen == 0) {
        printf("Nenhum genero cadastrado no momento.\n");
    } else {
        // Percorre o vetor da posição 0 até o limite da quantidade de genero atual
        for (int i = 0; i < qtd_gen; i++) {
            printf("--------------------------------------------------\n");
            printf("Codigo do Genero: %d\n", lista[i].codigo);
            printf("Nome do Genero: %s\n", lista[i].nome);
        }
    }
}


/*
  Função Auxiliar: marcar_generos_assinados
 
 Percorre a árvore de assinaturas. Para cada assinatura, busca a forma correspondente 
 na lista dinâmica e "marca" com 1 (no vetor 'marcados') a posição dos gêneros escolhidos.
 
  Parâmetros:
 - Assin *raiz: Ponteiro para a árvore de assinaturas (passagem por valor, só leitura).
 - FormaDaAssi *listaFormas: Ponteiro para a lista de formas (passagem por valor, só leitura).
 - Genero listaGeneros[]: Vetor de gêneros (passagem do ponteiro base, só leitura).
 - int qtdGeneros: Quantidade total de gêneros (passagem por valor).
 - int marcados[]: Vetor de inteiros passado por REFERÊNCIA (ponteiro). Usamos ele para 
 alterar as flags (0 ou 1) que serão lidas depois pela função principal.
 
 */
void marcar_generos_assinados(Assinatura *raiz, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]) {
    if (raiz != NULL) {
        // 1. Desce pela esquerda
        marcar_generos_assinados(raiz->esq, lista_formas, lista_generos, qtd_generos, marcados);
        
        // 2. Processa a raiz atual (Assinatura)
        forma_ass *forma_atual = lista_formas;
        
        // Busca a forma vinculada a esta assinatura
        while (forma_atual != NULL) {
            if (forma_atual->codigo == raiz->codigo_forma) {
                // Encontrou a forma! Agora pega os gêneros dela e marca no vetor
                for (int i = 0; i < forma_atual->qtd_generos_mensais; i++) {
                    int codigo_genero_escolhido = forma_atual->generos_escolhidos[i];
                    
                    // Procura o índice deste código no vetor estático de gêneros
                    for (int j = 0; j < qtd_generos; j++) {
                        if (lista_generos[j].codigo == codigo_genero_escolhido) {
                            marcados[j] = 1; // Marca o gênero como "assinado"
                            break; // Sai do loop interno, pois já achou e marcou
                        }
                    }
                }
                break; // Sai do loop da forma, pois já encontrou a que procurava
            }
            forma_atual = forma_atual->prox;
        }

        // 3. Desce pela direita
        marcar_generos_assinados(raiz->dir, lista_formas, lista_generos, qtd_generos, marcados);
    }
}

/*
 * Função Principal: mostrar_generos_assinados
 Cria um vetor de marcação zerado, chama a função auxiliar para preenchê-lo e, em seguida,
 imprime apenas os gêneros que receberam a marcação '1'.
 
 Parâmetros:
  - Assin *raizAssinaturas, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros:
 Estruturas bases passadas por valor (ou ponteiro base para arrays) apenas para leitura.
 
 */
void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos) {
    // Cria um vetor local com o tamanho máximo de gêneros e inicializa tudo com 0 (não assinado)
    int marcados[MAX_GENEROS] = {0}; 
    int encontrou = 0;

    // Chama a função auxiliar passando o vetor 'marcados' por referência para ser modificado
    marcar_generos_assinados(raiz_assinaturas, lista_formas, lista_generos, qtd_generos, marcados);

    printf("--- Generos Atualmente Assinados ---\n");
    
    // Percorre a lista estática de gêneros baseando-se no vetor de marcação
    for (int i = 0; i < qtd_generos; i++) {
        if (marcados[i] == 1) { // Se a flag for 1, significa que alguém assina esse gênero
            printf("Codigo: %d | Nome: %s\n", lista_generos[i].codigo, lista_generos[i].nome);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhum genero esta sendo assinado no momento.\n");
    }
}