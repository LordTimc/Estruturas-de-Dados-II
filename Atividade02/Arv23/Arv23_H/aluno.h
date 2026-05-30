#ifndef ARV23_ALUNO_H
#define ARV23_ALUNO_H
#include "../Arv23_H/structs.h"

// Verifica se o no de aluno atual e uma folha
int eh_folha_aluno(Arv23_Aluno *no);

// Gerencia o cadastro de um aluno validando a existencia de seu curso
int cadastrar_aluno(Arv23_Aluno **raiz_alunos, Arv23_Curso *raiz_cursos, Aluno novo_aluno);

// Funcao recursiva para varrer a arvore e inserir o aluno
int insere_rec_aluno(Arv23_Aluno **raiz, Aluno valor, Aluno *sobe, Arv23_Aluno **maior);

// Funcao publica para iniciar o processo de insercao de um aluno
int insere_23_aluno(Arv23_Aluno **raiz, Aluno valor);

// Funcao que imprime todos os alunos de um determinado curso (cod_curso)
void imprime_alunos_curso(Arv23_Aluno *raiz, int cod_curso);

// Funcao que imprime os alunos de um curso que ingressaram em um ano especifico
void imprime_alunos_curso_ano(Arv23_Aluno *raiz, int cod_curso, int ano);

// Funcao que conta e retorna a quantidade de alunos de um determinado curso
int conta_alunos_curso(Arv23_Aluno *raiz, int cod_curso);

// Libera a memoria de um unico no de aluno e aponta para NULL
void libera_no_aluno(Arv23_Aluno **raiz);

// Libera recursivamente todos os nos da arvore 2-3 de alunos
void libera_arvore_aluno(Arv23_Aluno **raiz);

#endif