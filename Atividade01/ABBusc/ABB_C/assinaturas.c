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

int cadastrar_assinatura(Assinatura **raiz, Usuario *raiz_usuarios, forma_ass *lista_formas, char *cpf, int codigo_forma, char *data_assinatura, char *data_vencimento, float valor) {

    int status_insercao = 0;
    
    int assinante_existe = 0;
    int forma_existe = 0;

    // --- VALIDAÇÃO 1: O assinante existe? ---
    // Busca na árvore binária de usuários de forma iterativa
    if (raiz_usuarios != NULL) {
        if (strcmp(cpf, raiz_usuarios->cpf) == 0) {
            assinante_existe = 1; // Encontrou o CPF
        } else if (strcmp(cpf, raiz_usuarios->cpf) < 0) {
            raiz_usuarios = raiz_usuarios->esq;
        } else {
            raiz_usuarios = raiz_usuarios->dir;
        }
    }

     // --- VALIDAÇÃO 2: A forma de assinatura existe? ---
    // Percorre a lista dinâmica iterativamente
    forma_da_ass *temp_f = lista_formas;
    while (temp_f != NULL) {
        if (temp_f->codigo == codigo_forma) {
            forma_existe = 1;
            break;
        }
        temp_f = temp_f->prox;
    }

    // Só prossegue se as duas validações forem verdadeiras
    if (assinante_existe == 1 && forma_existe == 1) {
        
        Assinatura *atual = *raiz;
        Assinatura *pai = NULL;
        int cpf_repetido = 0;

        // --- VALIDAÇÃO 3: O CPF já tem assinatura nesta árvore? ---
        // Desce na árvore de assinaturas procurando pelo CPF para achar a folha correta
        while (atual != NULL) {
            pai = atual; // Salva o nó atual como "pai" antes de descer
            int comp = strcmp(cpf, atual->cpf_usuario);
            
            if (comp == 0) {
                // CPF já tem uma assinatura cadastrada
                cpf_repetido = 1;
                break;
            } else if (comp < 0) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }

        // Se o CPF não for repetido, aloca e insere o nó
        if (cpf_repetido == 0) {
            Assinatura *nova_assinatura = (Assinatura *)malloc(sizeof(Assinatura));
            
            if (nova_assinatura != NULL) {
               
                strcpy(nova_assinatura->cpf_usuario, cpf);
                nova_assinatura->codigo_forma = codigo_forma;
                strcpy(nova_assinatura->data_assinatura, data_assinatura);
                strcpy(nova_assinatura->data_vencimento, data_vencimento);
                nova_assinatura->valor = valor;
                
                // Filhos nulos pois é um novo nó folha
                nova_assinatura->esq = NULL;
                nova_assinatura->dir = NULL;

                // Conecta o novo nó à árvore
                if (pai == NULL) {
                    // Se pai é NULL, a árvore estava vazia
                    *raiz = nova_assinatura;
                } else {
                    // Verifica se insere na esquerda ou direita do pai encontrado
                    if (strcmp(cpf, pai->cpf_usuario) < 0) {
                        pai->esq = nova_assinatura;
                    } else {
                        pai->dir = nova_assinatura;
                    }
                }
                
                status_insercao = 1;
            }
        }
    }

    return status_insercao;
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