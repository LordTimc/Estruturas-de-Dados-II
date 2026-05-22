#include <stdio.h>
#include "operacoes.h"

void req_imprimir_alunos_curso(Arv23_Aluno *raiz, int cod_curso) {
    if (raiz != NULL) {
        req_imprimir_alunos_curso(raiz->esq, cod_curso);
        if (raiz->info1.cod_curso == cod_curso) 
            printf("Mat: %d | Nome: %s\n", raiz->info1.matricula, raiz->info1.nome);
        req_imprimir_alunos_curso(raiz->cen, cod_curso);
        if (raiz->nInfo == 2) {
            if (raiz->info2.cod_curso == cod_curso) 
                printf("Mat: %d | Nome: %s\n", raiz->info2.matricula, raiz->info2.nome);
            req_imprimir_alunos_curso(raiz->dir, cod_curso);
        }
    }
}

void req_imprimir_alunos_curso_ano(Arv23_Aluno *raiz, int cod_curso, int ano) {
    if (raiz != NULL) {
        req_imprimir_alunos_curso_ano(raiz->esq, cod_curso, ano);
        if (raiz->info1.cod_curso == cod_curso && raiz->info1.ano_ingresso == ano) 
            printf("Mat: %d | Nome: %s\n", raiz->info1.matricula, raiz->info1.nome);
        req_imprimir_alunos_curso_ano(raiz->cen, cod_curso, ano);
        if (raiz->nInfo == 2) {
            if (raiz->info2.cod_curso == cod_curso && raiz->info2.ano_ingresso == ano) 
                printf("Mat: %d | Nome: %s\n", raiz->info2.matricula, raiz->info2.nome);
            req_imprimir_alunos_curso_ano(raiz->dir, cod_curso, ano);
        }
    }
}

int req_contar_alunos_curso(Arv23_Aluno *raiz, int cod_curso) {
    int total = 0;
    if (raiz != NULL) {
        total += req_contar_alunos_curso(raiz->esq, cod_curso);
        if (raiz->info1.cod_curso == cod_curso) total++;
        total += req_contar_alunos_curso(raiz->cen, cod_curso);
        if (raiz->nInfo == 2) {
            if (raiz->info2.cod_curso == cod_curso) total++;
            total += req_contar_alunos_curso(raiz->dir, cod_curso);
        }
    }
    return total;
}

void req_imprimir_cursos_blocos(Arv23_Curso *raiz, int blocos) {
    if (raiz != NULL) {
        req_imprimir_cursos_blocos(raiz->esq, blocos);
        if (raiz->info1.qtd_blocos == blocos) 
            printf("Curso [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        req_imprimir_cursos_blocos(raiz->cen, blocos);
        if (raiz->nInfo == 2) {
            if (raiz->info2.qtd_blocos == blocos) 
                printf("Curso [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            req_imprimir_cursos_blocos(raiz->dir, blocos);
        }
    }
}

void req_imprimir_disciplinas_bloco(Arv23_Disciplina *raiz, int bloco) {
    if (raiz != NULL) {
        req_imprimir_disciplinas_bloco(raiz->esq, bloco);
        if (raiz->info1.bloco == bloco) 
            printf("Disciplina [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        req_imprimir_disciplinas_bloco(raiz->cen, bloco);
        if (raiz->nInfo == 2) {
            if (raiz->info2.bloco == bloco) 
                printf("Disciplina [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            req_imprimir_disciplinas_bloco(raiz->dir, bloco);
        }
    }
}

void req_imprimir_disciplinas_carga(Arv23_Disciplina *raiz, int carga) {
    if (raiz != NULL) {
        req_imprimir_disciplinas_carga(raiz->esq, carga);
        if (raiz->info1.carga_horaria == carga) 
            printf("Disciplina [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        req_imprimir_disciplinas_carga(raiz->cen, carga);
        if (raiz->nInfo == 2) {
            if (raiz->info2.carga_horaria == carga) 
                printf("Disciplina [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            req_imprimir_disciplinas_carga(raiz->dir, carga);
        }
    }
}