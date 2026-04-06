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