#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/auxiliares.h"
#include "../ABB_H/formaAssinat.h"


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

void cadastrar_assinatura(Assinatura **r, Assinante *raiz_usu, forma_ass *lista_formas){
    char cpf_aux[12];
    int cadastrou = 0;
    Assinatura *novo_no = NULL;

    printf("\n--- Nova Assinatura ---\n");

    if (pega_cpf(cpf_aux)) {
        // REGRA DE NEGÓCIO III: O assinante TEM que existir
        if (buscar_assinante(raiz_usu, cpf_aux) == NULL) {
            printf("Erro: Assinante com CPF %s nao encontrado no sistema.\n", cpf_aux);
            return;
        }

        novo_no = alocar_assinatura();
        if (novo_no != NULL) {
            strcpy(novo_no->cpf_usuario, cpf_aux);
            
            printf("Digite o codigo da forma de assinatura: ");
            novo_no->codigo_forma = num_inteiro();

            // REGRA DE NEGÓCIO III: A forma de assinatura TEM que existir
            if (buscar_forma(lista_formas, novo_no->codigo_forma) == NULL) {
                printf("Erro: Forma de assinatura %d nao existe.\n", novo_no->codigo_forma);
                free(novo_no);
                return;
            }

            printf("Data de Inicio da assinatura:\n");
            if (pega_data(&novo_no->data_assinatura)) {
                printf("Data de Vencimento da assinatura:\n");
                if (pega_data(&novo_no->data_vencimento)) {
                    printf("Valor da Assinatura: ");
                    novo_no->valor = num_decimal();
                    cadastrou = 1;
                }
            }
        }
    }

    if (cadastrou) {
        if (inserir_assinatura(r, novo_no)) {
            printf("Assinatura realizada com sucesso!\n");
        } else {
            printf("Erro: Nao foi possivel inserir na arvore.\n");
        }
    } else {
        if (novo_no != NULL) free(novo_no);
        printf("Cadastro cancelado ou dados invalidos.\n");
    }
}


int inserir_assinatura(Assinatura **raiz, Assinatura *novo){
    int inseriu = 0;
    if (*raiz == NULL) {
        *raiz = novo;
        inseriu = 1;
    } else {
        if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) == 0){
            printf("Aviso: Assinatura ja existente para o CPF %s.\n", novo->cpf_usuario);
            free(novo);
            inseriu = 0;
        } else if(strcmp(novo->cpf_usuario, (*raiz)->cpf_usuario) < 0){
            // CORREÇÃO: Estava chamando si mesmo errado
            inseriu = inserir_assinatura(&(*raiz)->esq, novo);
        } else {
            // CORREÇÃO: Estava chamando 'inserir_na_arvore'
            inseriu = inserir_assinatura(&(*raiz)->dir, novo);
        }
    }
    return inseriu; 
}

int possui_assinatura_vencida(Assinatura *raiz, char *cpf) {
    int resultado = 0;
    Data hoje;

    pegar_data_de_hoje(&hoje);

    if (raiz != NULL) {
        if (strcmp(cpf, raiz->cpf_usuario) == 0) {
            // Verifica se está vencida
            if (
                (raiz->data_vencimento.ano < hoje.ano) ||
                (raiz->data_vencimento.ano == hoje.ano && raiz->data_vencimento.mes < hoje.mes) ||
                (raiz->data_vencimento.ano == hoje.ano && raiz->data_vencimento.mes == hoje.mes && raiz->data_vencimento.dia < hoje.dia)
            ) {
                resultado = 1; // está vencida
            } else {
                resultado = 0; // não está vencida
            }
        } else if (strcmp(cpf, raiz->cpf_usuario)< 0) {
            resultado = possui_assinatura_vencida(raiz->esq, cpf);
        } else {
            resultado = possui_assinatura_vencida(raiz->dir, cpf);
        }
    }
    return resultado;
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


Assinatura* buscar_assinatura(Assinatura *raiz, char *cpf) {
    Assinatura *encontrado = NULL; 
    if (raiz != NULL) {
        if (strcmp(cpf, raiz->cpf_usuario) == 0) {
            encontrado = raiz;
        } else if (strcmp(cpf, raiz->cpf_usuario) < 0) {
            encontrado = buscar_assinatura(raiz->esq, cpf);
        } else {
            encontrado = buscar_assinatura(raiz->dir, cpf);
        }
    }
    return encontrado;
}


int no_sem_filho_assinatura(Assinatura *raiz) {
    int eh_folha = 0;
    if (raiz != NULL) {
        if (raiz->esq == NULL && raiz->dir == NULL)
            eh_folha = 1;
    }
    return eh_folha;
}

Assinatura *so_um_filho_assinatura(Assinatura *r) {
    Assinatura *no = NULL;
    if (r != NULL) {
        if (r->esq == NULL && r->dir != NULL)
            no = r->dir;
        else if (r->esq != NULL && r->dir == NULL)
            no = r->esq;
    }
    return no;
}

int dois_filhos_assinatura(Assinatura *r) {
    return (r != NULL && r->esq != NULL && r->dir != NULL);
}


int remover_no_assinatura(Assinatura **r, char *cpf) {
    // Única variável de controle do fluxo
    int removeu = 0;

    if (*r != NULL) {
        if (strcmp(cpf, (*r)->cpf_usuario) < 0) {
            removeu = remover_no_assinatura(&(*r)->esq, cpf);
        } else if (strcmp(cpf, (*r)->cpf_usuario) > 0) {
            removeu = remover_no_assinatura(&(*r)->dir, cpf);
        } else {
            // Encontrou o nó a ser removido!
            Assinatura *temp = *r;

            // CASO 1: Nó Folha (Zero filhos)
            if (no_sem_filho_assinatura(*r)) {
                *r = NULL;
                free(temp);
                removeu = 1; 
            } 
            // CASO 2: Apenas UM filho
            else if (so_um_filho_assinatura(*r) != NULL) {
                *r = so_um_filho_assinatura(*r);
                free(temp);
                removeu = 1; 
            } 
            // CASO 3: Dois filhos
            else if (dois_filhos_assinatura(*r)) {
                // Busca o maior elemento da subárvore esquerda
                temp = (*r)->esq;
                while (temp->dir != NULL) {
                    temp = temp->dir;
                }
                
                // Copia todos os dados do nó substituto para o nó atual
                strcpy((*r)->cpf_usuario, temp->cpf_usuario);
                (*r)->codigo_forma = temp->codigo_forma;
                (*r)->data_assinatura = temp->data_assinatura;
                (*r)->data_vencimento = temp->data_vencimento;
                (*r)->valor = temp->valor;
                
                // Dispara a recursão para deletar o nó duplicado
                // Captura o sucesso da recursão na nossa variável de controle
                removeu = remover_no_assinatura(&(*r)->esq, temp->cpf_usuario); 
            }
        }
    }
    
    return removeu;
}

void liberar_arvore_assinaturas(Assinatura *raiz){
    if (raiz != NULL) {
        liberar_arvore_assinaturas(raiz->esq);
        liberar_arvore_assinaturas(raiz->dir);
        free(raiz);
    }
}