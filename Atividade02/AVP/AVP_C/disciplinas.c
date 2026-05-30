#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVP_H/disciplinas.h"
#include "../AVP_H/curso.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"
#include "../AVP_H/suporteAVP.h"

// FUNÇÕES DE CRIAÇÃO

// Função para alocar um novo curso
// Recebe código, nome, bloco e carga horária
// Retorna um ponteiro para a nova disciplina criada
Disciplina *aloca_disciplina(int codigo, char *nome, int bloco, int ch){

    // Inicializa novo ponteiro
    Disciplina *novo = (Disciplina*) malloc(sizeof(Disciplina));
    
    novo->cod_disciplina = codigo;
    strcpy(novo->nome, nome);
    novo->bloco = bloco;
    novo->carga_horaria = ch;

    novo->cor = RED;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

// Realiza o cadastro de uma disciplina com entrada de dados do usuário
// Valida as entradas e, se tudo estiver correto, cria a disciplina
// Retorna ponteiro para a disciplina criada ou NULL em caso de erro
Disciplina *cadastra_disciplina(){
    int cadastrou = 0;

    Disciplina *disciplina;
    int cod_displina = 0;
    char *nome_displina;
    int bloco;
    int carga_horaria;

    disciplina = NULL;
    nome_displina = NULL;

    printf("Entre com o codigo da nova disciplina: ");
    cod_displina = num_inteiro();

    if(cod_displina){
        printf("Entre com o nome da nova disciplina: ");
        nome_displina = leitura_de_string();
        
        if(nome_displina != NULL){
            printf("Entre com o numero do Bloco: ");
            bloco = num_inteiro();

            if(bloco){
                printf("Entre com a carga horaria: ");
                carga_horaria = num_inteiro();
                
                if(carga_horaria)
                    cadastrou = 1;
            }
        }
    }

    if(cadastrou){
        // Fazer a alocação de memória de disciplina
        disciplina = aloca_disciplina(cod_displina, nome_displina, bloco, carga_horaria);
    }else{
        if(nome_displina != NULL){
            free(nome_displina);
        }
    }
    return disciplina;
}

// FUNÇÕES DE INSERÇÃO

// Insere um nó disciplina na árvore rubro-negra
// Realiza inserção recursiva e balanceamento da árvore
// Retorna 1 se inseriu com sucesso, 0 caso contrário
int insere_no_disciplina(Disciplina **raiz, Disciplina *novo){
    int inseriu = 0;

    if (*raiz == NULL){
        *raiz = novo;
        inseriu = 1;
    }
    else if(novo->cod_disciplina < (*raiz)->cod_disciplina){
        inseriu = insere_no_disciplina(&((*raiz)->esq), novo);
    }else{
        inseriu = insere_no_disciplina(&((*raiz)->dir), novo);
    }

    if(inseriu){
        balancea_VP_disciplina(raiz);
    }

    return inseriu;
}

// Função principal de inserção na árvore
// Garante que a raiz permaneça preta após inserção
// Retorna 1 se inserção foi bem-sucedida
int insere_disciplina(Disciplina **raiz, Disciplina *nova){
    int sucesso = 0;

    sucesso = insere_no_disciplina(raiz, nova);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return sucesso; 
}

// Funcao recursiva auxiliar para percorrer as disciplinas em ordem crescente
// Imprime todas as disciplinas ordenadas pelo código
void percorre_disciplinas_em_ordem(Disciplina *raiz) {
    if (raiz != NULL) {
        percorre_disciplinas_em_ordem(raiz->esq);
        printf("Codigo: %d | Nome: %s | Bloco: %d | Carga Horaria: %d\n", 
               raiz->cod_disciplina, raiz->nome, raiz->bloco, raiz->carga_horaria);
        percorre_disciplinas_em_ordem(raiz->dir);
    }
}


// Funcao recursiva auxiliar para filtrar disciplinas por bloco
void percorre_por_bloco(Disciplina *raiz, int bloco) {
    if (raiz != NULL) {
        percorre_por_bloco(raiz->esq, bloco);
        if (raiz->bloco == bloco) {
            printf("Codigo: %d | Nome: %s | Bloco: %d\n", 
                   raiz->cod_disciplina, raiz->nome, raiz->bloco);
        }
        percorre_por_bloco(raiz->dir, bloco);
    }
}


// Funcao recursiva auxiliar para filtrar disciplinas por carga horaria
void percorre_por_carga_horaria(Disciplina *raiz, int carga_horaria){
    if (raiz != NULL){
        percorre_por_carga_horaria(raiz->esq, carga_horaria);
        if (raiz->carga_horaria == carga_horaria) {
            printf("Codigo: %d | Nome: %s | Carga Horaria: %d horas\n", 
                   raiz->cod_disciplina, raiz->nome, raiz->carga_horaria);
        }
        percorre_por_carga_horaria(raiz->dir, carga_horaria);
    }
}


// LIBERACAO
// Libera a memoria de um unico no de disciplina e aponta para NULL
void libera_no_disciplina(Disciplina **raiz){
    // Libera o no e anula o ponteiro
    free(*raiz);
    *raiz = NULL;
}

// Libera recursivamente todos os nos da arvore de disciplinas
void libera_arvore_disciplina(Disciplina **raiz){
    if (*raiz != NULL){
        // Percorre e libera a subarvore esquerda
        libera_arvore_disciplina(&(*raiz)->esq);

        // Percorre e libera a subarvore direita
        libera_arvore_disciplina(&(*raiz)->dir);

        // Libera o no atual
        libera_no_disciplina(raiz);
    }
}

// Funcao que verifica se uma disciplina existe na árvore pelo código
// Retorna 1 se encontrar, 0 caso contrário
int consulta_disciplina(Disciplina *raiz, int codigo_disc){
    int resultado = 0; 

    if (raiz != NULL){
        // Caso 1: encontrou a disciplina 
        if (codigo_disc == raiz->cod_disciplina)
            resultado = 1;
        // Caso 2: o codigo do no atual eh menor que o procurado
        // Entao vai pra subarvore esquerda 
        else if (codigo_disc < raiz->cod_disciplina)
            resultado = consulta_disciplina(raiz->esq, codigo_disc);
        // Caso 3: o codigo do no atual eh maior que o procurado
        // Entao vaai pra subarvore direita
        else
            resultado = consulta_disciplina(raiz->dir, codigo_disc);
    }
    // Retorna 1 (encontrado) ou 0 (não encontrado)
    return resultado;
}

// FUNÇÕES AUXILIARES

// Funcao auxiliar para encontrar o no com o menor codigo em uma subarvore
// Percorre sempre para a esquerda até encontrar o menor elemento
// Retorna o ponteiro para a menor disciplina
Disciplina* encontra_menor_disciplina(Disciplina *no) {
    Disciplina *menor = no;
    
    if (menor != NULL) {
        while (menor->esq != NULL) {
            menor = menor->esq;
        }
    }
    
    return menor;
}

// Funcao que substitui as informacoes do no que o usuario quer apagar pelas informacoes do sucessor em-ordem (o menor no da subarvore direita) e depois apaga esse sucessor la na base da arvore, onde eh estruturalmente muito mais simples.
// Troca nome, código, bloco e carga horária
void substitui_informacoes_disciplinas(Disciplina *no_atual, Disciplina *sucessor){
    if (no_atual != NULL && sucessor != NULL){
        // 1. Copia o nome do sucessor para o no atual
        strcpy(no_atual->nome, sucessor->nome);

        // 2. Copia as informacoes numericas do sucessor para o no atual
        no_atual->cod_disciplina = sucessor->cod_disciplina;
        no_atual->bloco = sucessor->bloco;
        no_atual->carga_horaria  = sucessor->carga_horaria;
    }
// NAO se copia os ponteiros (esq, dir, pai) e NEM a cor,
// pois 'no_atual' precisa manter a sua posicao fisica e a sua cor 
// na arvore para nao quebrar a estrutura e as regras de balancear.
}

// Função para mover um nó vermelho para a esquerda durante a remoção
void move2_esquerda_disciplina(Disciplina **raiz){
    troca_cor_disciplina(*raiz);

    if ((*raiz)->dir != NULL && cor_disciplina((*raiz)->dir->esq) == RED){
        rotacao_dir_disciplina(&((*raiz)->dir));
        rotacao_esq_disciplina(raiz);
        troca_cor_disciplina(*raiz);
    }
}

// Funcao para mover um no vermelho para a direita durante a remocao
void move2_direita_disciplina(Disciplina **raiz){
    troca_cor_disciplina(*raiz);

    if ((*raiz)->esq != NULL && cor_disciplina((*raiz)->esq->esq) == RED){
        rotacao_dir_disciplina(raiz);
        troca_cor_disciplina(*raiz);
    }
}

// REMOÇÃO AUXILIAR

// Funcao para remover a menor disciplina da arvore
// Utilizado como parte do processo de remoção de um nó com dois filhos
void remove_menor_disciplina_arv(Disciplina **raiz){
    if ((*raiz)->esq == NULL)
        libera_no_disciplina(raiz);
    else{
        // garante que existe um no vermelho no caminho a esquerda
        if (cor_disciplina((*raiz)->esq) == BLACK && cor_disciplina((*raiz)->esq->esq) == BLACK)
            move2_esquerda_disciplina(raiz);

        remove_menor_disciplina_arv(&((*raiz)->esq));
        balancea_VP_disciplina(raiz);
    }
}

// Funcao recursiva para remover o no da disciplina
// Percorre a árvore, encontra o nó e realiza a remoção com balanceamento
// Retorna 1 se removeu com sucesso, 0 caso contrário
int remove_disciplina_no(Disciplina **raiz, int cod_disciplina) {
    int removeu = 1;

    if ((*raiz) != NULL) {
        if (cod_disciplina < (*raiz)->cod_disciplina) {
            if ((*raiz)->esq != NULL) {
                if (cor_disciplina((*raiz)->esq) == BLACK && cor_disciplina((*raiz)->esq->esq) == BLACK) {
                    move2_esquerda_disciplina(raiz);
                }
            }
            removeu = remove_disciplina_no(&((*raiz)->esq), cod_disciplina);
        } else {
            if (cor_disciplina((*raiz)->esq) == RED) {
                rotacao_dir_disciplina(raiz);
            }

            if (cod_disciplina == (*raiz)->cod_disciplina && (*raiz)->dir == NULL) {
                libera_no_disciplina(raiz);
            } else {
                if ((*raiz)->dir != NULL) {
                    if (cor_disciplina((*raiz)->dir) == BLACK && cor_disciplina((*raiz)->dir->esq) == BLACK) {
                        move2_direita_disciplina(raiz);
                    }
                }

                if (cod_disciplina == (*raiz)->cod_disciplina) {
                    // Encontra o menor no da subarvore direita (sucessor em-ordem)
                    Disciplina *menor = encontra_menor_disciplina((*raiz)->dir);
                    // O no atual ganha a identidade do menor (sucessor), mas mantem sua cor e ponteiros
                    substitui_informacoes_disciplinas(*raiz, menor);
                    // Agora removeu-se o menor no na base da arvore
                    remove_menor_disciplina_arv(&((*raiz)->dir));
                } else {
                    removeu = remove_disciplina_no(&((*raiz)->dir), cod_disciplina);
                }
            }
        }

        // Rebalanceia a arvore se o no atual ainda existe
        if (*raiz != NULL) {
            balancea_VP_disciplina(raiz);
        }
    } else {
        removeu = 0;
    }

    return removeu;
}

// Função principal para remocao - mantem a raiz preta
// Primeiro verifica se a disciplina existe
// Garante que a raiz permaneça preta após a remoção
// Retorna 1 se removeu, 0 caso contrário
int remove_disciplina_arvore(Disciplina **raiz, int codigo){
    int removeu = consulta_disciplina(*raiz, codigo);

    if (removeu)
        removeu = remove_disciplina_no(raiz, codigo);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return removeu;
}