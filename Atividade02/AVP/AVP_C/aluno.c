#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/aluno.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"
#include "../AVP_H/suporteAVP.h"

// FUNÇÕES DE CRIAÇÃO

Aluno *aloca_aluno(char *nome_aluno, int mat, int codigo, int ano, int semestre){
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

    strcpy(aluno->nome, nome_aluno);
    aluno->matricula = mat;
    aluno->codigo_Curso = codigo;
    aluno->ano_Ingresso = ano;
    aluno->semestre_Ingresso = semestre;

    aluno->cor = RED;
    aluno->esq = NULL;
    aluno->dir = NULL;

    return aluno;
}

Aluno *cadastra_aluno(){
    int cadastrou = 0;

    Aluno *novo_aluno;
    int matricula = 0;
    char *nome;
    int codigo;
    int ano;
    int semestre;

    novo_aluno = NULL;
    nome = NULL;

    printf("Digite a matricula do aluno: ");
    matricula = num_inteiro();

    if(matricula){
        printf("Digite o nome do aluno: ");
        nome = leitura_de_string();

        if(nome != NULL){
            printf("Digite o codigo do curso do aluno: ");
            codigo = num_inteiro();

            if(codigo){
                printf("Digite o ano de ingresso: ");
                ano = num_inteiro();

                if(ano){
                    printf("Digite o semestre de ingresso: ");
                    semestre = num_inteiro();

                    if(semestre)
                        cadastrou = 1;
                }
            }
        }
    }

    if(cadastrou){
        novo_aluno = aloca_aluno(nome, matricula, codigo, ano, semestre);
    } else {
        if(nome != NULL){
            free(nome);
        }
    }

    return novo_aluno;
}

// =================================
// INSERCAO
// =================================

int insere_no_aluno(Aluno **raiz, Aluno *novo_aluno){
    int inseriu = 0;

    if (*raiz == NULL){
        *raiz = novo_aluno;
        inseriu = 1;
    }
    else if (strcasecmp(novo_aluno->nome, (*raiz)->nome) < 0)
        inseriu = insere_no_aluno(&((*raiz)->esq), novo_aluno);
    else if (strcasecmp(novo_aluno->nome, (*raiz)->nome) > 0)
        inseriu = insere_no_aluno(&((*raiz)->dir), novo_aluno);

    if (inseriu)
        balancea_VP_aluno(raiz);

    return inseriu;
}

int insere_aluno(Aluno **raiz, Aluno *novo_aluno){
    int inseriu;
    inseriu = insere_no_aluno(raiz, novo_aluno);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}



// Função para imprimir informações de um aluno de um curso
void imprime_alunos_por_curso(Aluno *raiz, int codigo_curso) {
    if (raiz != NULL) {
        // Percorre a subarvore esquerda
        imprime_alunos_por_curso(raiz->esq, codigo_curso);
        
        // Verifica se o no atual pertence ao curso desejado 
        if (raiz->codigo_Curso == codigo_curso) {
            printf("Matricula: %d | Nome: %s\n", raiz->matricula, raiz->nome);
        }
        
        /* Percorre a subárvore direita */
        imprime_alunos_por_curso(raiz->dir, codigo_curso);
    }
}

void imprime_alunos_por_curso_ano(Aluno *raiz, int codigo_curso, int ano_ingressado) {
    if (raiz != NULL) {
        /* 1. Percorre toda a subárvore esquerda */
        imprime_alunos_por_curso_ano(raiz->esq, codigo_curso, ano_ingressado);
        
        /* 2. Visita o nó atual: verifica as duas condições simultaneamente */
        if (raiz->codigo_Curso == codigo_curso && raiz->ano_Ingresso == ano_ingressado) {
            printf("Matricula: %d | Nome: %s\n", raiz->matricula, raiz->nome);
        }
        
        /* 3. Percorre toda a subárvore direita */
        imprime_alunos_por_curso_ano(raiz->dir, codigo_curso, ano_ingressado);
    }
}

// Libera a memoria de um unico no de aluno e aponta para NULL
void libera_no_aluno(Aluno **raiz){
    // Libera o no e anula o ponteiro
    free(*raiz);
    *raiz = NULL;
}

// Libera recursivamente todos os nos da arvore de alunos
void libera_arvore_aluno(Aluno **raiz){
    if (*raiz != NULL){
        // Percorre e libera a subarvore esquerda
        libera_arvore_aluno(&(*raiz)->esq);

        // Percorre e libera a subarvore direita
        libera_arvore_aluno(&(*raiz)->dir);

        // Libera o no atual
        libera_no_aluno(raiz);
    }
}