#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/auxiliares.h"

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

