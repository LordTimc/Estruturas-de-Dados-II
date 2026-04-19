#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/auxiliares.h"

Assinante *aloca_assinante (char *cpf, char *nome, char *endereco, Data data_nascimento){ 
    // Aloca espaço na memória para o novo usuário
    Assinante *novo_usuario = (Assinante *)malloc(sizeof(Assinante));
        
    if (novo_usuario != NULL) {
        strcpy(novo_usuario->cpf, cpf);
        strcpy(novo_usuario->nome, nome);
        strcpy(novo_usuario->endereco, endereco);
        novo_usuario->nascimento = data_nascimento;
        
        novo_usuario->esq = NULL;
        novo_usuario->dir = NULL;
    }
    return (novo_usuario);
}


/* - char *cpf, *nome, *endereco, *dataNasc: Dados do usuário a serem inseridos (passagem por valor/ponteiro de array).*/
Assinante *cadastrar_assinante(Assinante *usuario) {
    char cpf[12];
    char *nome = NULL;
    char *endereco = NULL; 
    Data nascimento;
    int cadastrou = 0; 

    printf("==== Informacoes do assinante ====");

    if(pega_cpf(cpf)){
        printf("\nDigite o nome: ");
        nome = leitura_de_string();
        
        if(nome != NULL){
            endereco = pega_endereco();    
            if(endereco != NULL && pega_data_nasci(&nascimento)){
                // CORREÇÃO: Estava aloca_usuario
                usuario = aloca_assinante(cpf, nome, endereco, nascimento);
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
int inserir_assinante(Assinante **raiz, Assinante *novo){
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
int mostrar_assinantes(Assinante *raiz) {
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
        printf("Data de Nascimento: %02d/%02d/%04d\n", raiz->nascimento.dia, raiz->nascimento.mes, raiz->nascimento.ano);
        
        // 3º Passo: Desce para a subárvore direita (CPFs maiores)
        mostrou = mostrar_assinantes(raiz->dir);
        mostrou = 1;
    }
    return mostrou;
}

// ------ Remoção ----------

int eh_folha(Assinante *raiz){
    int eh_folha = 0;

    if(raiz != NULL){
        if(raiz->esq == NULL & raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}

Assinante *so_um_filho(Assinante *r){
    Assinante *no;
    no = NULL;

    if(r != NULL){
        if(r->esq == NULL && r->dir != NULL)
            no = r->dir;
        else if(r->esq != NULL && r->dir == NULL)
            no = r->esq;
    }
    return(no);
}

int dois_filhos(Assinante *r){
    return (r->esq != NULL && r->dir != NULL);
}

int remove_assinant(Assinante **r, char *cpf) {
    // Inicializa a variável de controle (único ponto de saída)
    int removeu = 0;

    if (*r != NULL) {
        if (strcmp(cpf, (*r)->cpf) < 0) {
            removeu = remove_assinant(&(*r)->esq, cpf);
        } else if (strcmp(cpf, (*r)->cpf) > 0) {
            removeu = remove_assinant(&(*r)->dir, cpf);
        } else {
            // Encontrou o nó a ser removido!
            Assinante *temp = *r;

            // CASO 1: Nó Folha (Zero filhos)
            if (no_sem_filho(*r)) {
                *r = NULL;
                free(temp);
                removeu = 1; // Define sucesso
            } 
            // CASO 2: Apenas UM filho
            // Como so_um_filho retorna NULL se não houver exatamente 1 filho, 
            // podemos testar se o retorno é diferente de NULL.
            else if (so_um_filho(*r) != NULL) { 
                *r = so_um_filho(*r); 
                free(temp);
                removeu = 1; // Define sucesso
            } 
            // CASO 3: Dois filhos
            else if (dois_filhos(*r)) { 
                // Busca o maior elemento da subárvore esquerda
                temp = (*r)->esq;
                while (temp->dir != NULL) {
                    temp = temp->dir;
                }
                
                // Copia os dados do nó substituto para o nó atual
                strcpy((*r)->cpf, temp->cpf);
                strcpy((*r)->nome, temp->nome);
                strcpy((*r)->endereco, temp->endereco);
                (*r)->nascimento = temp->nascimento;
                
                // A recursão cuidará de deletar o nó duplicado.
                // O retorno dessa recursão (1) é passado para a nossa variável.
                removeu = remove_assinant(&(*r)->esq, temp->cpf);
            }
        }
    }
    
    // Único return de toda a função!
    return removeu;
}

// Função para liberar os nó e depois a raiz.
void liberar_arvore_usuario(Assinante *raiz){
    if (raiz != NULL) {
        liberar_arvore_usuario(raiz->esq);
        liberar_arvore_usuario(raiz->dir);
        free(raiz);
    }
}

Assinante* buscar_assinante(Assinante *raiz, char *cpf) {
    if (raiz == NULL) return NULL;
    if (strcmp(cpf, raiz->cpf) == 0) return raiz;
    if (strcmp(cpf, raiz->cpf) < 0) return buscar_assinante(raiz->esq, cpf);
    return buscar_assinante(raiz->dir, cpf);
}

