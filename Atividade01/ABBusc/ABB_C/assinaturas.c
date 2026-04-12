#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/usuarios.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/auxiliares.h"


Assinatura* alocar_assinatura(){
    // Inicializa o ponteiro como NULL 
    Assinatura *novo = (Assinatura*) malloc(sizeof(Assinatura));

    if (novo != NULL) {
        // Inicialização de strings para evitar lixo de memória
        strcpy(novo->cpf_usuario, "");
        
        // Inicialização de valores numéricos
        novo->codigo_forma = 0;
        novo->valor = 0.0;

        // Inicialização de structs internas
        novo->data_assinatura.dia = 0;
        novo->data_assinatura.mes = 0;
        novo->data_assinatura.ano = 0;

        novo->data_vencimento.dia = 0;
        novo->data_vencimento.mes = 0;
        novo->data_vencimento.ano = 0;

        novo->esq = NULL;
        novo->dir = NULL;
    } else {
        printf("Erro! Falha na alocacao de memoria para Assinatura.\n");
    }
    return novo; 
}

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

Assinatura* cadastrar_assinatura(Assinatura *r){
    char cpf_aux[12];
    int cadastrou = 0;
    Assinatura *novo_no = NULL;

    printf("--- Nova Assinatura ---\n");

    // Primeiro: Valida os dados
    if (pega_cpf(cpf_aux)) {
        
        // Segundo: Aloca o espaço
        novo_no = alocar_assinatura();

        if (novo_no != NULL) {
            // Terceiro: Transfere os dados validados para a struct
            strcpy(novo_no->cpf_usuario, cpf_aux);
            
            // Aqui você pediria o código da forma, as datas, etc.
            printf("Digite o codigo da forma de assinatura: ");
            novo_no->codigo_forma = num_inteiro();

            printf("Data de Inicio da assinatura:\n");
            if (pega_data(&novo_no->data_assinatura)){

                printf("Data de Vencimento da assinatura:\n");
                if (pega_data(&novo_no->data_vencimento)){
                    
                    printf("Valor da Assinatura: ");
                    novo_no->valor = num_decimal();
                }
            }
            cadastrou = 1;
        }
    }

    if (cadastrou) {
        // Quarto: Insere na Árvore de Busca (ABB)
        r = inserir_na_arvore(r, novo_no); 
        printf("Assinatura realizada com sucesso!\n");
    } else {
        if (novo_no) free(novo_no); // Limpa se algo deu errado no meio
    }

    return r;
}


int *inserir_assintura(Assinatura **raiz, Assinatura *novo){
    int inseriu = 1;
    // Caso base: se chegamos em uma folha (ou árvore vazia),
    // o ponteiro 'raiz' recebe o 'novo' nó.
    if (*raiz == NULL) {
        *raiz = novo;
    }else if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) == 0){
        // Comparamos os CPFs para decidir o lado.
        // strcmp retorna < 0 se o primeiro for menor, e > 0 se for maior.
        // Caso o CPF seja igual, você decide o que fazer.
            // Geralmente, em sistemas de cadastro, não permitimos duplicatas.
        printf("Aviso: Assinatura ja existente para o CPF %s.\n", novo->cpf_usuario);
        free(novo);
        novo = NULL;
        inseriu = 0;
    }else if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) < 0){
            // Se o novo CPF for "menor", vai para a esquerda
            inseriu = inserir_assinatura(&(*raiz)->esq, novo);
     
    }else if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) > 0){
            // Se o novo CPF for "maior", vai para a direita
            inseriu = inserir_na_arvore(&(*raiz)->dir, novo);
    }
    return inseriu; 
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
void mostrar_assinaturas(Assinatura *raiz) {
    
    if (raiz != NULL) {
        
        // 1º Passo: Visita a subárvore esquerda (CPFs menores)
        mostrar_assinaturas(raiz->esq);
        
        // 2º Passo: Imprime os dados do nó atual (a raiz deste momento)
        printf("--------------------------------------------------\n");
        printf("cpf do assinante: %s\n", raiz->cpf_usuario);
        printf("codigo da forma: %d\n", raiz->codigo_forma);
        printf("data da assinatura: %s\n", raiz->data_assinatura);
        printf("data de vencimento: %s\n", raiz->data_vencimento);
        printf("valor: r$ %.2f\n", raiz->valor);
        
        // 3º Passo: Visita a subárvore direita (CPFs maiores)
        mostrar_assinaturas(raiz->dir);
    }
}

/*
 Realiza uma busca binária iterativa na árvore de assinaturas utilizando o CPF.
  Se encontrar, imprime a data de vencimento. Se não, avisa que não encontrou.
 
  Parâmetros:
  - Assin *raiz: Ponteiro simples para a raiz da árvore de assinaturas (passagem por valor).
  - char *cpf: O CPF (string) informado pelo usuário para a busca.
 
 */
void mostrar_vencimento_assinatura(Assinatura *raiz, char *cpf) {
    Assinatura *atual = raiz;
    int encontrou = 0; // Flag para saber se achou o assinante

    while (atual != NULL) {
        // Compara o CPF procurado com o CPF do nó atual
        int comparacao = strcmp(cpf, atual->cpf_usuario);

        if (comparacao == 0) {
            // Encontrou a assinatura do usuário!
            printf("--------------------------------------------------\n");
            printf("assinante cpf: %s\n", atual->cpf_usuario);
            printf("data de vencimento: %s\n", atual->data_vencimento);
            
            encontrou = 1;
            break; // Pode parar o laço, pois já achamos o que queríamos e não há CPFs repetidos
            
        } else if (comparacao < 0) {
            // Se o CPF buscado for "menor", vai para a esquerda
            atual = atual->esq;
        } else {
            // Se o CPF buscado for "maior", vai para a direita
            atual = atual->dir;
        }
    }

    // Se o laço terminou e a flag continua 0, a assinatura não existe
    if (encontrou == 0) {
        printf("aviso: nenhuma assinatura encontrada para o cpf %s.\n", cpf);
    }
}