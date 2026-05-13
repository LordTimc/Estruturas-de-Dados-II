#ifndef STRUCTS_H
#define STRUCTS_H

#define VERMELHO 1
#define PRETO 0

typedef struct disciplina Disciplina;
typedef struct curso Curso;
typedef struct aluno ALuno;
typedef struct Arvore_Alunos;
typedef struct Arvore_Cursos;
typedef struct Arvore_Disciplinas;

// STRUCT DISCIPLINA
typedef struct disciplina {
    int cod_disciplina;
    char nome[100];
    int bloco;
    int carga_horaria;

    /* Ponteiros da árvore Rubro-Negra */
    struct Disciplina *esq;
    struct Disciplina *dir;
    struct Disciplina *pai;

    int cor;

} Disciplina;


//STRUCT CURSO
typedef struct curso {
    int cod_curso;
    char nome[100];

    int quantidade_blocos;
    int semanas_por_disciplina;

    /* Raiz da árvore de disciplinas */
    Disciplina *raiz_disciplinas;

    /* Ponteiros da árvore Rubro-Negra */
    struct Curso *esq;
    struct Curso *dir;
    struct Curso *pai;

    int cor;

} Curso;


//STRUCT ALUNO
typedef struct aluno {
    int matricula;
    char nome[100];

    int codigo_Curso;
    int ano_Ingresso;
    int semestre_Ingresso; // 1 = primeiro semestre; 2 = segundo semestre 

    /* Ponteiros da árvore Rubro-Negra */
    struct Aluno *esq;
    struct Aluno *dir;
    struct Aluno *pai;

    int cor;

} Aluno;


/* =========================================================
   ÁRVORES
========================================================= */

typedef struct {
    Aluno *raiz;
} Arvore_Alunos;

typedef struct {
    Curso *raiz;
} Arvore_Cursos;

typedef struct {
    Disciplina *raiz;
} Arvore_Disciplinas;

#endif