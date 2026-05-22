#ifndef STRUCTS_H
#define STRUCTS_H

// ===== enum de status de remoção =====
typedef enum {
    OK,
    UNDERFLOW,
    INFO_NAO_ENCONTRADA,
    SUCESSOR_NAO_ENCONTRADO,
    ARVORE_VAZIA,
    NAO_FOI_POSSIVEL_T_UNDERFLOW
} StatusRemocao;

// ===== Estruturas de Informação =====
typedef struct ALUNO {
    int matricula;
    char nome[100];
    int cod_curso;
    int ano_ingresso;
    int semestre_ingresso;
} ALUNO;

typedef struct DISCIPLINA {
    int codigo;
    char nome[100];
    int bloco;
    int carga_horaria;
} DISCIPLINA;

// Nó de Disciplina precisa ser declarado antes de Curso
typedef struct Arv23_Disciplina {
    DISCIPLINA info1, info2;
    int nInfo;
    struct Arv23_Disciplina *esq, *cen, *dir;
} Arv23_Disciplina;

typedef struct CURSO {
    int codigo;
    char nome[100];
    int qtd_blocos;
    int semanas;
    Arv23_Disciplina *arv_disciplinas;
} CURSO;

// ===== Árvores 2-3 =====
typedef struct Arv23_Curso {
    CURSO info1, info2;
    int nInfo;
    struct Arv23_Curso *esq, *cen, *dir;
} Arv23_Curso;

typedef struct Arv23_Aluno {
    ALUNO info1, info2;
    int nInfo;
    struct Arv23_Aluno *esq, *cen, *dir;
} Arv23_Aluno;

#endif