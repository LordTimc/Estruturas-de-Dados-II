#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/curso.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"

int inserir_no_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = 0;

    if (*raiz == NULL)
    {
        *raiz = novo_curso;
        inseriu = 1;
    }
    else if (novo_curso->cod_curso < (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->esq), novo_curso);
    else if (novo_curso->cod_curso > (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->dir), novo_curso);

    if (inseriu)
        balancear_RB_curso(raiz);

    return inseriu;
}

int inserir_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = inserir_no_curso(raiz, novo_curso);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}

Curso *aloca_curso(int cod, char *nome, int qtd_blocos, int semanas){
    Curso *curso = (Curso *)malloc(sizeof(Curso));

    if (curso != NULL)
    {
        curso->cod_curso = cod;
        strcpy(curso->nome, nome);

        curso->quantidade_blocos = qtd_blocos;
        curso->semanas_por_disciplina = semanas;

        curso->raiz_disciplinas = NULL;

        curso->cor = RED;
        curso->esq = NULL;
        curso->dir = NULL;
        curso->pai = NULL;
    }

    return curso;
}

Curso *cadastrar_curso(){
    Curso *novo = NULL;
    char *nome;
    int cod, blocos, semanas;
    int ok = 1;

    printf("Digite o codigo do curso: ");
    cod = digitar_int();

    printf("Digite o nome do curso: ");
    nome = ler_string();

    if (nome == NULL)
        ok = 0;

    if (ok){
        printf("Digite a quantidade de blocos: ");
        blocos = digitar_int();

        printf("Digite semanas por disciplina: ");
        semanas = digitar_int();
    }

    if (ok)
        novo = aloca_curso(cod, nome, blocos, semanas);
    else if (nome != NULL)
        free(nome);

    return novo;
}

void rotacao_esquerda_curso(Curso **raiz){
    Curso *aux = (*raiz)->dir;

    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacao_direita_curso(Curso **raiz){
    Curso *aux = (*raiz)->esq;

    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

int cor_aluno(Curso *curso){
    int cor;
    if (curso == NULL)
        cor = BLACK;
    else
        cor = curso->cor;
    return cor;
}

void trocar_cor_curso(Curso *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir)
        raiz->dir->cor = !(raiz->dir->cor);
}

void balancear_RB_curso(Curso **raiz){
    if (*raiz != NULL){
        if (cor_curso((*raiz)->esq) == BLACK && cor_curso((*raiz)->dir) == RED)
            rotacao_esquerda_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->esq->esq) == RED)
            rotacao_direita_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->dir) == RED)
            trocar_cor_curso(*raiz);
    }
}

// --- FUNCAO AUXILIAR DE CONTAGEM  ---
int contar_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total = 0;

    if (raiz != NULL) {
        int atual = 0;
        
        // Verifica se o aluno atual pertence ao curso buscado
        if (raiz->codigo_Curso == cod_curso) {
            atual = 1;
        }
        
        // Soma o aluno atual com os resultados das subarvores esquerda e direita
        total = atual + 
                contar_alunos_por_curso(raiz->esq, cod_curso) + 
                contar_alunos_por_curso(raiz->dir, cod_curso);
    }

    return total; 
}

// --- FUNcaO PRINCIPAL PARA MOSTRAR O RESULTADO ---
void mostrar_qtd_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total_alunos = contar_alunos_por_curso(raiz, cod_curso);

    if (total_alunos > 0) {
        printf("O curso com codigo %d possui %d aluno(s) matriculado(s).\n", cod_curso, total_alunos);
    } else {
        printf("Nenhum aluno encontrado para o curso com codigo %d.\n", cod_curso);
    }
}

// --- FUNCAO PARA IMPRIMIR OS CURSOS EM ORDEM CRESCENTE ---
void imprimir_cursos_crescente(Curso *raiz) {
    
    if (raiz != NULL) {
        // 1. Visita a subarvore esquerda 
        imprimir_cursos_crescente(raiz->esq);
        
        // 2. Visita a raiz atual 
        printf("Codigo: %-5d | Nome: %-30s | Blocos: %d\n", 
               raiz->cod_curso, 
               raiz->nome, 
               raiz->quantidade_blocos);
        
        // 3. Visita a subarvore direita 
        imprimir_cursos_crescente(raiz->dir);
    }
}

void imprimir_curso_por_codigo(Curso *raiz, int cod_curso) {
    Curso *atual = raiz;
    int encontrado = 0;

    // Busca controlada por ponteiro e flag 
    while (atual != NULL && !encontrado) {
        if (atual->cod_curso == cod_curso) {
            printf("\n   CURSO ENCONTRADO   \n");
            printf("Codigo do Curso: %d\n", atual->cod_curso);
            printf("Nome do Curso: %s\n", atual->nome);
            printf("Quantidade de Blocos: %d\n", atual->quantidade_blocos);
            printf("Semanas por Disciplina: %d\n", atual->semanas_por_disciplina);
            printf("==================================================\n");
            encontrado = 1; 
        } else if (cod_curso < atual->cod_curso) {
            atual = atual->esq; // Vai para a esquerda se o codigo for menor
        } else {
            atual = atual->dir; // Vai para a direita se o codigo for maior
        }
    }

    // Se varreu a arvore e nao achou
    if (!encontrado) {
        printf("Aviso: Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// --- FUNCAO AUXILIAR DE CONTAGEM E IMPRESSAO ---
int busca_imprime_por_blocos(Curso *raiz, int qtd_blocos) {
    int total_encontrados = 0;

    if (raiz != NULL) {
        int atual = 0;

        // Verifica se o no atual atende ao criterio informado pelo usuário
        if (raiz->quantidade_blocos == qtd_blocos) {
            printf("Codigo: %-5d | Nome: %-30s | Blocos: %d\n", 
                   raiz->cod_curso, raiz->nome, raiz->quantidade_blocos);
            atual = 1;
        }

        // Acumula o atual com o resultado das subarvores esquerda e direita
        total_encontrados = atual + 
                            busca_imprime_por_blocos(raiz->esq, qtd_blocos) + 
                            busca_imprime_por_blocos(raiz->dir, qtd_blocos);
    }

    return total_encontrados;
}

// --- FUNCAO PRINCIPAL CHAMADA PELO USUARIO ---
void lista_cursos_por_qtd_blocos(Curso *raiz, int qtd_blocos) {
    printf("\n--- Buscando cursos com %d blocos ---\n", qtd_blocos);
    
    int total = busca_imprime_por_blocos(raiz, qtd_blocos);

    if (total == 0) {
        printf("Nenhum curso foi encontrado com a quantidade de %d blocos.\n", qtd_blocos);
    } else {
        printf("Total de cursos listados: %d\n", total);
    }
}