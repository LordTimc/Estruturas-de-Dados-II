#ifndef STRUCTS_H
#define STRUCTS_H

#define RED 1
#define BLACK 0

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


// Arvores

typedef struct {
    Disciplina *raiz;

    struct Disciplina *esq;
    struct Disciplina *dir;
    struct Disciplina *pai;
} Arv_Disciplinas;

typedef struct {
    Curso *raiz;

    struct Curso *esq;
    struct Curso *dir;
    struct Curso *pai;
} Arv_Cursos;

typedef struct {
    Aluno *raiz;

    struct Aluno *esq;
    struct Aluno *dir;
    struct Aluno *pai;
} Arv_Alunos;

#endif