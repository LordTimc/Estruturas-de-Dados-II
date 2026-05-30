#ifndef ALUNO_H
#define ALUNO_H

#include "../AVP_H/structs.h"

// =========================
// FUNÇÕES DE CRIAÇÃO
// =========================

// Aloca e inicializa um novo no de aluno com os dados fornecidos
Aluno *aloca_aluno(char *nome_aluno, int mat, int codigo, int ano, int semestre);

// Coleta os dados do usuario e retorna um novo aluno alocado, ou NULL se falhar
Aluno *cadastra_aluno();


// =========================
// FUNÇÕES DE INSERÇÃO
// =========================

// Insere recursivamente um no na arvore e aciona o balanceamento
int insere_no_aluno(Aluno **raiz, Aluno *novo_aluno);

// Insere um aluno na arvore e garante que a raiz permaneca preta
int insere_aluno(Aluno **raiz, Aluno *novo_aluno);


// =========================
// IMPRESSÃO
// =========================

// Imprime todos os alunos pertencentes a um curso especifico
void imprime_alunos_por_curso(Aluno *raiz, int codigo_curso);

// Imprime todos os alunos de um curso que ingressaram em um ano especifico
void imprime_alunos_por_curso_ano(Aluno *raiz, int codigo_curso, int ano_ingressado);


// =========================
// LIBERAÇÃO DE MEMÓRIA
// =========================

// Libera a memoria de um unico no de aluno e aponta para NULL
void libera_no_aluno(Aluno **raiz);

// Libera recursivamente todos os nos da arvore de alunos
void libera_arvore_aluno(Aluno **raiz);

#endif