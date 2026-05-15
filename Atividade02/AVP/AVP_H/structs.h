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
// Ela vem primeiro porque não depende de nenhuma outra struct
typedef struct Disciplina {
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
// a struct Curso vem em segundo porque depende da struct Disciplina
typedef struct Curso {
    int cod_curso;
    char nome[100];

    int quantidade_blocos;
    int semanas_por_disciplina; // Na UFPI é 15

    /* quando o compilador ler isso, ele já precisa conhecer o tipo Disciplina */
    Disciplina *raiz_disciplinas;

    /* Ponteiros da árvore Rubro-Negra */
    struct Curso *esq;
    struct Curso *dir;
    struct Curso *pai;

    int cor;
} Curso;


//STRUCT ALUNO
// não depende de nenhuma struct, pois não possui ponteiro para curso
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

#endif