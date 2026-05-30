#include <stdio.h>
#include <stdlib.h>
#include "../Arv23_H/aluno.h"
#include "../Arv23_H/curso.h"

#include "../Arv23_H/structs.h"
#include "../Arv23_H/suporteArv23.h"


// Funcao para checar se o no de aluno atual e uma folha
int eh_folha_aluno(Arv23_Aluno *no) {
    return (no != NULL && no->esq == NULL);
}

// Funcao que gerencia o cadastro de um aluno validando a existencia de seu curso
int cadastrar_aluno(Arv23_Aluno **raiz_alunos, Arv23_Curso *raiz_cursos, Aluno novo_aluno) {
    int sucesso = 0;

    // Verifica se o curso informado para o aluno realmente existe na arvore de cursos
    if (buscar_info_curso(raiz_cursos, novo_aluno.cod_curso) != NULL) {
        // Tenta realizar a insercao fisica do aluno na arvore 2-3 de alunos
        sucesso = insere_23_aluno(raiz_alunos, novo_aluno);
    }

    // Ponto unico de saida retornando o status do cadastro (1 para sucesso, 0 para erro)
    return sucesso;
}

// Funcao recursiva para varrer a arvore e inserir o aluno
int insere_rec_aluno(Arv23_Aluno **raiz, Aluno valor, Aluno *sobe, Arv23_Aluno **maior) {
    int sucesso = 0;
    Arv23_Aluno *atual = *raiz;
    if (atual == NULL) {
        *raiz = cria_no_aluno(valor, NULL, NULL);
        *maior = NULL;
        sucesso = (*raiz != NULL);
    }
    else if (valor.matricula == atual->info1.matricula || (atual->nInfo == 2 && valor.matricula == atual->info2.matricula)) {
        *maior = NULL;
        sucesso = 0;
    }
    else {
        // Verifica se chegou ao nivel folha para efetuar a insercao fisica
        if (eh_folha_aluno(atual)) {
            if (atual->nInfo == 1) {
                adiciona_aluno(raiz, valor, NULL);
                *maior = NULL;
                sucesso = 1;
            }
            else {
                *maior = quebra_aluno(raiz, valor, sobe, NULL);
                sucesso = (*maior != NULL);
            }
        } else {
            // Escolhe o caminho apropriado para descer na arvore com base na matricula
            Arv23_Aluno **prox;
            if (valor.matricula < atual->info1.matricula)
                prox = &(atual->esq);
            else if (atual->nInfo == 1 || valor.matricula < atual->info2.matricula)
                prox = &(atual->cen);
            else
                prox = &(atual->dir);
            
            int suc_rec = insere_rec_aluno(prox, valor, sobe, maior);
            // Trata o retorno da recursao caso tenha ocorrido quebra de no abaixo
            if (*maior != NULL) {
                Aluno ch = *sobe;
                Arv23_Aluno *nf = *maior;
                *maior = NULL;
                if (atual->nInfo == 1) {
                    adiciona_aluno(raiz, ch, nf);
                    sucesso = 1;
                }
                else {
                    *maior = quebra_aluno(raiz, ch, sobe, nf);
                    sucesso = (*maior != NULL);
                }
            } else
                sucesso = suc_rec;
        }
    }
    return sucesso;
}

// Funcao publica para iniciar o processo de insercao de um aluno
int insere_23_aluno(Arv23_Aluno **raiz, Aluno valor) {
    int sucesso = 0;
    Aluno sobe;
    Arv23_Aluno *maior = NULL;
    if (raiz != NULL) {
        sucesso = insere_rec_aluno(raiz, valor, &sobe, &maior);
        // Se houve divisao na raiz original, uma nova raiz surge aumentando a altura
        if (maior != NULL) {
            Arv23_Aluno *nova = cria_no_aluno(sobe, *raiz, maior);
            if (nova)
                *raiz = nova;
            else
                sucesso = 0;
        }
    }
    return sucesso;
}

// Funcao que imprime todos os alunos de um determinado curso (cod_curso)
void imprime_alunos_curso(Arv23_Aluno *raiz, int cod_curso) {

    // verifica se o no atual existe
    if (raiz != NULL) {
        // percorre subarvore esquerda primeiro
        imprime_alunos_curso(raiz->esq, cod_curso);
        // verifica info1 do no
        // se o curso for o desejado, imprime os dados do aluno
        if (raiz->info1.cod_curso == cod_curso) 
            printf("Mat: %d | Nome: %s\n", raiz->info1.matricula, raiz->info1.nome);

        // percorre subarvore central
        imprime_alunos_curso(raiz->cen, cod_curso);

        // verifica se o no possui segunda informacao (no com 2 chaves)
        if (raiz->nInfo == 2) {

            // verifica info2 do no
            // se o curso for o desejado, imprime os dados do aluno
            if (raiz->info2.cod_curso == cod_curso) 
                printf("Mat: %d | Nome: %s\n", raiz->info2.matricula, raiz->info2.nome);

            // percorre subarvore direita
            imprime_alunos_curso(raiz->dir, cod_curso);
        }
    }
}

// Funcao que imprime os alunos de um curso que ingressaram em um ano especifico
void imprime_alunos_curso_ano(Arv23_Aluno *raiz, int cod_curso, int ano) {
    if (raiz != NULL) {
        imprime_alunos_curso_ano(raiz->esq, cod_curso, ano);
        if (raiz->info1.cod_curso == cod_curso && raiz->info1.ano_ingresso == ano) 
            printf("Mat: %d | Nome: %s\n", raiz->info1.matricula, raiz->info1.nome);
        imprime_alunos_curso_ano(raiz->cen, cod_curso, ano);
        if (raiz->nInfo == 2) {
            if (raiz->info2.cod_curso == cod_curso && raiz->info2.ano_ingresso == ano) 
                printf("Mat: %d | Nome: %s\n", raiz->info2.matricula, raiz->info2.nome);
            imprime_alunos_curso_ano(raiz->dir, cod_curso, ano);
        }
    }
}

// Funcao que conta e retorna a quantidade de alunos de um determinado curso
int conta_alunos_curso(Arv23_Aluno *raiz, int cod_curso) {
    int total = 0;
    if (raiz != NULL) {
        total += conta_alunos_curso(raiz->esq, cod_curso);
        if (raiz->info1.cod_curso == cod_curso) total++;
        total += conta_alunos_curso(raiz->cen, cod_curso);
        if (raiz->nInfo == 2) {
            if (raiz->info2.cod_curso == cod_curso) total++;
            total += conta_alunos_curso(raiz->dir, cod_curso);
        }
    }
    return total;
}

// Libera a memoria de um unico no de aluno e aponta para NULL
void libera_no_aluno(Arv23_Aluno **raiz) {
    if (raiz && *raiz != NULL) {
        free(*raiz);
        *raiz = NULL;
    }
}

// Libera recursivamente todos os nos da arvore 2-3 de alunos
void libera_arvore_aluno(Arv23_Aluno **raiz) {
    if (raiz && *raiz != NULL) {
        // Percorre e libera a subarvore esquerda
        libera_arvore_aluno(&(*raiz)->esq);

        // Percorre e libera a subarvore central (Especifico da Arvore 2-3)
        libera_arvore_aluno(&(*raiz)->cen);

        // Percorre e libera a subarvore direita
        libera_arvore_aluno(&(*raiz)->dir);

        // Libera o no atual apos garantir que os filhos foram liberados
        libera_no_aluno(raiz);
    }
}