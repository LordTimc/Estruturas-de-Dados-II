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
void mostrarGeneros(Genero lista[], int qtd) {

    if (qtd == 0) {
        printf("Nenhum genero cadastrado no momento.\n");
    } else {
        // Percorre o vetor da posição 0 até a última posição preenchida (qtd - 1)
        for (int i = 0; i < qtd; i++) {
            printf("--------------------------------------------------\n");
            printf("Codigo do Genero: %d\n", lista[i].codigo);
            printf("Nome do Genero: %s\n", lista[i].nome);
        }
    }
}


/*
  Função Auxiliar: marcarGenerosAssinados
 
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
void marcarGenerosAssinados(Assin *raiz, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros, int marcados[]) {
    if (raiz != NULL) {
        // 1. Desce pela esquerda
        marcarGenerosAssinados(raiz->esq, listaFormas, listaGeneros, qtdGeneros, marcados);
        
        // 2. Processa a raiz atual (Assinatura)
        FormaDaAssi *formaAtual = listaFormas;
        
        // Busca a forma vinculada a esta assinatura
        while (formaAtual != NULL) {
            if (formaAtual->codigo == raiz->codigoForma) {
                // Encontrou a forma! Agora pega os gêneros dela e marca no vetor
                for (int i = 0; i < formaAtual->generosMensais; i++) {
                    int codigoGeneroEscolhido = formaAtual->generosEscolhidos[i];
                    
                    // Procura o índice deste código no vetor estático de gêneros
                    for (int j = 0; j < qtdGeneros; j++) {
                        if (listaGeneros[j].codigo == codigoGeneroEscolhido) {
                            marcados[j] = 1; // Marca o gênero como "assinado"
                            break; // Sai do loop interno, pois já achou e marcou
                        }
                    }
                }
                break; // Sai do loop da forma, pois já encontrou a que procurava
            }
            formaAtual = formaAtual->prox;
        }

        // 3. Desce pela direita
        marcarGenerosAssinados(raiz->dir, listaFormas, listaGeneros, qtdGeneros, marcados);
    }
}

/*
 * Função Principal: mostrarGenerosAssinados
 Cria um vetor de marcação zerado, chama a função auxiliar para preenchê-lo e, em seguida,
 imprime apenas os gêneros que receberam a marcação '1'.
 
 Parâmetros:
  - Assin *raizAssinaturas, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros:
 Estruturas bases passadas por valor (ou ponteiro base para arrays) apenas para leitura.
 
 */
void mostrarGenerosAssinados(Assin *raizAssinaturas, FormaDaAssi *listaFormas, Genero listaGeneros[], int qtdGeneros) {
    // Cria um vetor local com o tamanho máximo de gêneros e inicializa tudo com 0 (não assinado)
    int marcados[MAXGENEROS] = {0}; 
    int encontrouAlgum = 0;

    // Chama a função auxiliar passando o vetor 'marcados' por referência para ser modificado
    marcarGenerosAssinados(raizAssinaturas, listaFormas, listaGeneros, qtdGeneros, marcados);

    printf("--- Generos Atualmente Assinados ---\n");
    
    // Percorre a lista estática de gêneros baseando-se no vetor de marcação
    for (int i = 0; i < qtdGeneros; i++) {
        if (marcados[i] == 1) { // Se a flag for 1, significa que alguém assina esse gênero
            printf("Codigo: %d | Nome: %s\n", listaGeneros[i].codigo, listaGeneros[i].nome);
            encontrouAlgum = 1;
        }
    }

    if (encontrouAlgum == 0) {
        printf("Nenhum genero esta sendo assinado no momento.\n");
    }
}