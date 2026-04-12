#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/usuarios.h"
#include "../ABB_H/auxiliares.h"

Usuario *aloca_assinante (char *cpf, char *nome, char *endereco, data_nasci data){ 
    // Aloca espaço na memória para o novo usuário
    Usuario *novo_usuario = (Usuario *)malloc(sizeof(Usuario));
        
    if (novo_usuario != NULL) {
        strcpy(novo_usuario->cpf, cpf);
        strcpy(novo_usuario->nome, nome);
        strcpy(novo_usuario->endereco, endereco);
        novo_usuario->data = data;
        
        novo_usuario->esq = NULL;
        novo_usuario->dir = NULL;
    }
    return (novo_usuario);
}


/* - char *cpf, *nome, *endereco, *dataNasc: Dados do usuário a serem inseridos (passagem por valor/ponteiro de array).*/
Usuario *cadastrar_assinante(Usuario *usuario) {

    char cpf[12];
    char *nome = NULL;
    char *endereco = NULL; 
    data_nasci data;
    // Variável única de retorno para saber se deu certo cadastrar.
    int cadastrou = 0; 

    printf("==== Informacoes do assinante====");

    if(pega_cpf(cpf)){

        printf("\nDigite o nome: ");
        nome = leitura_de_string();
        
        if(nome != NULL){
            endereco = pega_endereco();    
            if(endereco != NULL && pega_data_nasci(&data)){
                usuario = aloca_usuario(cpf, nome, endereco, data);
                cadastrou = 1;

                free(nome);
                free(endereco);
            }
        }
    }

    if(!cadastrou){
        if(nome) free(nome);
        if(endereco) free(endereco);
    }
    return usuario;
}
/* **raiz: Ponteiro duplo para a raiz da árvore. Escolhido (passagem por referência), pois precisamos modificar o ponteiro real da árvore no `main` quando alocamos um novo nó.*/
int inserir_assinante(Usuario **raiz, Usuario *novo){
    int inseriu = 1;

    // Verifica se chegamos em um nó folha/vazio
    if(*raiz == NULL)
        *raiz = novo;
    else if(strcmp(novo->cpf, (*raiz)->cpf) == 0){
        // A função strcmp compara os dois CPFs. Retorna < 0 se a primeira for menor, > 0 se for maior, e 0 se forem iguais.
        // comparacao == 0 significa que o CPF já existe na árvore
        // Não permite cadastro repetido, logo, o inseriu se mantém 0 (falha)
        free(novo);
        novo = NULL;
        inseriu = 0;
    } else if(strcmp(novo->cpf, (*raiz)->cpf) < 0){
        // Se a árvore não está vazia e o CPF é "menor", vai para a subárvore esquerda.
        inseriu = inserir_assinante(&(*raiz)->esq, novo);
    } else if (strcmp(novo->cpf, (*raiz)->cpf) > 0){
        // Se o CPF é "maior", vai para a subárvore direita
        inseriu = inserir_assinante(&(*raiz)->dir, novo);
    }
    return inseriu; 
}


/* Percorre a árvore binária de assinantes utilizando o método "Em Ordem" (Esquerda -> Raiz -> Direita).
 ordenados pelo CPF.
 
 * Parâmetros:
 * - Usuario *raiz: Ponteiro simples para a raiz da árvore. Escolhemos a passagem 
 * por valor (cópia do ponteiro) porque esta função serve apenas para LEITURA. 
 * Não vamos inserir ou remover nós, logo, não precisamos modificar a árvore original.
*/
int mostrar_assinantes(Usuario *raiz) {
    int mostrou = 0;

    // Verifica se o nó atual não é nulo
    if (raiz != NULL) {
        
        // 1º Passo: Desce tudo que pode para a subárvore esquerda (CPFs menores)
        mostrou = mostrar_assinantes(raiz->esq);
        
        // 2º Passo: Visita a "raiz" atual (Imprime os dados do usuário)
        printf("--------------------------------------------------\n");
        printf("CPF: %s\n", raiz->cpf);
        printf("Nome: %s\n", raiz->nome);
        printf("Endereco: %s\n", raiz->endereco);
        printf("Data de Nascimento: %02d/%02d/%04d\n", raiz->data.dia, raiz->data.mes, raiz->data.ano);
        
        // 3º Passo: Desce para a subárvore direita (CPFs maiores)
        mostrou = mostrar_assinantes(raiz->dir);
        mostrou = 1;
    }
    return mostrou;
}

// ------ Remoção ----------

int no_sem_filho(Usuario *raiz){
    int eh_folha = 0;

    if(raiz != NULL){
        if(raiz->esq == NULL & raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}