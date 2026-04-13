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

void cadastrar_assinatura(Assinatura **r){
    char cpf_aux[12];
    int cadastrou = 0;
    Assinatura *novo_no = NULL;

    printf("\n--- Nova Assinatura ---\n");

    // 1. Valida o CPF antes de qualquer alocação
    if (pega_cpf(cpf_aux)) {
        
        // 2. Aloca e inicializa o nó (Responsabilidade Única)
        novo_no = alocar_assinatura();

        if (novo_no != NULL) {
            // 3. Preenchimento dos dados com verificações em cascata
            strcpy(novo_no->cpf_usuario, cpf_aux);
            
            printf("Digite o codigo da forma de assinatura: ");
            novo_no->codigo_forma = num_inteiro();

            printf("Data de Inicio da assinatura:\n");
            if (pega_data(&novo_no->data_assinatura)) {

                printf("Data de Vencimento da assinatura:\n");
                if (pega_data(&novo_no->data_vencimento)) {
                    
                    printf("Valor da Assinatura: ");
                    novo_no->valor = num_decimal();
                    
                    // Se o fluxo chegou aqui, todos os dados são válidos
                    cadastrou = 1;
                }
            }
        }
    }

    // 4. Finalização
    if (cadastrou) {
        // Chamada compatível com a sua função de ponteiro duplo
        // Note que passamos 'r' diretamente, pois 'r' já é Assinatura**
        if (inserir_assinatura(r, novo_no)) {
            printf("Assinatura realizada com sucesso!\n");
        } else {
            // Caso a função de inserção retorne 0 (ex: CPF duplicado)
            // A própria função 'inserir_assinatura' já deu free(novo_no) conforme seu código
            printf("Erro: Nao foi possivel inserir na arvore.\n");
        }
    } else {
        // Se o erro foi na leitura dos dados (antes da inserção), limpamos aqui
        if (novo_no != NULL) {
            free(novo_no);
        }
        printf("Cadastro cancelado ou dados invalidos.\n");
    }
}


int *inserir_assinatura(Assinatura **raiz, Assinatura *novo){
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
void mostrar_assinaturas(Assinatura *raiz){
    if (raiz != NULL) {
        // 1. Visita a subárvore da esquerda (Recursão)
        mostrar_assinaturas(raiz->esq);

        // 2. Exibe os dados do nó atual
        printf("\n-------------------------------------------");
        printf("\nCPF do Assinante: %s", raiz->cpf_usuario);
        printf("\nCodigo da Forma:  %d", raiz->codigo_forma);
        
        // Exibição das Datas (formatadas com %02d para garantir 2 dígitos)
        printf("\nData Assinatura:  %02d/%02d/%04d", 
                raiz->data_assinatura.dia, 
                raiz->data_assinatura.mes, 
                raiz->data_assinatura.ano);
        
        printf("\nData Vencimento:  %02d/%02d/%04d\n", 
                raiz->data_vencimento.dia, 
                raiz->data_vencimento.mes, 
                raiz->data_vencimento.ano);
        
        printf("\nValor:            R$ %.2f", raiz->valor);
        printf("\n-------------------------------------------");

        // 3. Visita a subárvore da direita (Recursão)
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
int mostrar_vencimento_assinatura_cpf(Assinatura *raiz, char *cpf){
    int encontrou = 0;

    if (raiz != NULL) 
    {
        if (strcmp(cpf, raiz->cpf_usuario) == 0) 
        {
            //Exibe os dados se encontrar
            printf("--------------------------------------------------\n");
            printf("Assinante CPF: %s\n", raiz->cpf_usuario);
            printf("\nData Vencimento:  %02d/%02d/%04d\n", 
                raiz->data_vencimento.dia, 
                raiz->data_vencimento.mes, 
                raiz->data_vencimento.ano);
            printf("--------------------------------------------------\n");
            encontrou = 1; 
        } 
        else if (strcmp(cpf, raiz->cpf_usuario) < 0) 
        {
            // Busca na subárvore esquerda
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->esq, cpf);
        } 
        else 
        {
            // Busca na subárvore direita
            encontrou = mostrar_vencimento_assinatura_cpf(raiz->dir, cpf);
        }
    }
    return encontrou;
}