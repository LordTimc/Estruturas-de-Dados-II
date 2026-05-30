#ifndef SUPORTEAVP_H
#define SUPORTEAVP_H

#include "../AVP_H/structs.h"


// =======================
// ALUNO
// =======================

// ROTAÇÕES 

// Realiza rotacao para a esquerda no no apontado por raiz
void rotacao_esq_aluno(Aluno **raiz);

// Realiza rotacao para a direita no no apontado por raiz
void rotacao_dir_aluno(Aluno **raiz);


// CONTROLE DE CORES

// Retorna a cor do no, tratando NULL como BLACK
int cor_aluno(Aluno *aluno);

// Inverte a cor do no raiz e de seus dois filhos
void troca_cor_aluno(Aluno *raiz);


// BALANCEAMENTO

// Aplica as correcoes necessarias para manter as propriedades da arvore Rubro-Negra
void balancea_VP_aluno(Aluno **raiz);


// =======================
// CURSO
// =======================

// ROTAÇÕES 

// Realiza uma rotacao para a esquerda no no apontado por raiz
void rotacao_esq_curso(Curso **raiz);

// Realiza uma rotacao para a direita no no apontado por raiz
void rotacao_dir_curso(Curso **raiz);


// CONTROLE DE CORES

// Retorna a cor de um no, tratando NULL como preto
int cor_curso(Curso *curso);

// Inverte a cor do no raiz e de seus dois filhos
void troca_cor_curso(Curso *raiz);


// BALANCEAMENTO

// Verifica e corrige violacoes da arvore Rubro-Negra apos insercao
void balancea_VP_curso(Curso **raiz);


// =======================
// DISCIPLINAS
// =======================

// ROTAÇÕES 

// Realiza rotação à esquerda na árvore
void rotacao_esq_disciplina(Disciplina **raiz);

// Realiza rotação à direita na árvore
void rotacao_dir_disciplina(Disciplina **raiz);


// CONTROLE DE CORES

// Retorna a cor do nó
int cor_disciplina(Disciplina *aluno);

// Inverte a cor do nó e de seus filhos
void troca_cor_disciplina(Disciplina *raiz);


// BALANCEAMENTO

// Realiza o balanceamento da árvore rubro-negra após inserção ou remoção
void balancea_VP_disciplina(Disciplina **raiz);

#endif