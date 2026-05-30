#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Disciplina Disciplina;
typedef struct Curso Curso;
typedef struct Aluno Aluno;

typedef struct Arv23_Disciplina Arv23_Disciplina;
typedef struct Arv23_Curso Arv23_Curso;
typedef struct Arv23_Aluno Arv23_Aluno;

// ===== Estruturas de Informação =====
typedef struct Aluno {
    int matricula;
    char nome[100];
    int cod_curso;
    int ano_ingresso;
    int semestre_ingresso;
} Aluno;

typedef struct Disciplina {
    int codigo;
    char nome[100];
    int bloco;
    int carga_horaria;
} Disciplina;

// Nó de Disciplina precisa ser declarado antes de Curso
typedef struct Arv23_Disciplina {
    Disciplina info1, info2;
    int nInfo;
    struct Arv23_Disciplina *esq, *cen, *dir;
} Arv23_Disciplina;

typedef struct Curso {
    int codigo;
    char nome[100];
    int qtd_blocos;
    int semanas;
    Arv23_Disciplina *arv_disciplinas;
} Curso;

// ===== Árvores 2-3 =====
typedef struct Arv23_Curso {
    Curso info1, info2;
    int nInfo;
    struct Arv23_Curso *esq, *cen, *dir;
} Arv23_Curso;

typedef struct Arv23_Aluno {
    Aluno info1, info2;
    int nInfo;
    struct Arv23_Aluno *esq, *cen, *dir;
} Arv23_Aluno;

#endif