#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/usuarios.h"
#include "../ABB_H/auxiliares.h"

Usuario *aloca_usuario (char *cpf, char *nome, char *endereco, char *data){ 
    // Aloca espaço na memória para o novo usuário
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));
        
    if (novo_usuario != NULL) {
        strcpy(novo_usuario->cpf, cpf);
        strcpy(novo_usuario->nome, nome);
        strcpy(novo_usuario->endereco, endereco);
        strcpy(novo_usuario->data, data);
        
        novo_usuario->esq = NULL;
        novo_usuario->dir = NULL;
    }
    return (novo_usuario);
}

/* **raiz: Ponteiro duplo para a raiz da árvore. Escolhido (passagem por referência) 
  porque precisamos modificar o ponteiro real da árvore no `main` quando alocamos um novo nó.
 * - char *cpf, *nome, *endereco, *dataNasc: Dados do usuário a serem inseridos (passagem por valor/ponteiro de array).*/
Usuario *cadastrar_assinante(Usuario *raiz) {

    char *cpf, *nome, *endereco, *data;
    // Variável única de retorno para saber se deu certo cadastrar.
    int cadastrou = 0; 

    printf("==== Informacoes do assinante====");
    printf("Digite o cpf: ");
    cpf = leitura_de_string();

    printf("\nDigite o nome: ");
    nome = leitura_de_string();

    printf("Digite o endereco: ");
    endereco = leitura_de_string();

    printf("\nDigite a data de nascimento: ");
    data = leitura_de_string();    

    // Verifica se chegamos em um nó folha/vazio
    if (raiz == NULL) {
        // Modifica o ponteiro da árvore original (por referência) para apontar para o novo nó
        raiz = aloca_usuario(cpf, nome, endereco, data_nasc); 
        
        // Define o status como sucesso
        cadastrou = 1;  
    } else {
        // A árvore não está vazia.
        // A função strcmp compara duas strings. Retorna < 0 se a primeira for menor, > 0 se for maior, e 0 se forem iguais.
        int comparacao = strcmp(cpf, (*raiz)->cpf);

        if (comparacao < 0) {
            // O CPF é "menor" alfabeticamente, vai para a subárvore esquerda
            status_insercao = cadastrar_assinante(&((*raiz)->esq), cpf, nome, endereco, data_nasc);
        } else if (comparacao > 0) {
            // O CPF é "maior" alfabeticamente, vai para a subárvore direita
            status_insercao = cadastrar_assinante(&((*raiz)->dir), cpf, nome, endereco, data_nasc);
        } else {
            // comparacao == 0 significa que o CPF já existe na árvore
            // Não permite cadastro repetido, logo, o status se mantém 0 (falha)
            status_insercao = 0; 
        }
    }

    return status_insercao; 
}


/*
 
 * Percorre a árvore binária de assinantes utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenados pelo CPF.
 
 * Parâmetros:
 * - Usuario *raiz: Ponteiro simples para a raiz da árvore. Escolhemos a passagem 
 * por valor (cópia do ponteiro) porque esta função serve apenas para LEITURA. 
 * Não vamos inserir ou remover nós, logo, não precisamos modificar a árvore original.
*/
void mostrar_assinantes(Usuario *raiz) {
    // Verifica se o nó atual não é nulo
    if (raiz != NULL) {
        
        // 1º Passo: Desce tudo que pode para a subárvore esquerda (CPFs menores)
        mostrar_assinantes(raiz->esq);
        
        // 2º Passo: Visita a "raiz" atual (Imprime os dados do usuário)
        printf("--------------------------------------------------\n");
        printf("CPF: %s\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("Endereco: %s\n", raiz->endereco);
        printf("Data de Nascimento: %s\n", raiz->data_nasc);
        
        // 3º Passo: Desce para a subárvore direita (CPFs maiores)
        mostrar_assinantes(raiz->dir);
    }
}

