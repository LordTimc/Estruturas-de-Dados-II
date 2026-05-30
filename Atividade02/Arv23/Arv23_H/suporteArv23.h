#ifndef SUPORTEARV23_H
#define SUPORTEARV23_H

#include "../Arv23_H/structs.h"


// =======================
// ALUNO
// =======================

// Aloca e cria um novo no de aluno
Arv23_Aluno *cria_no_aluno(Aluno info, Arv23_Aluno *esq, Arv23_Aluno *cen);

// Adiciona uma informacao dentro de um no de aluno ja existente
void adiciona_aluno(Arv23_Aluno **no, Aluno info, Arv23_Aluno *sub);

// Divide um no de aluno cheio em dois subnos
Arv23_Aluno *quebra_aluno(Arv23_Aluno **no, Aluno info, Aluno *sobe, Arv23_Aluno *dir);


// =======================
// CURSO
// =======================

// Aloca memoria e configura um no de curso
Arv23_Curso *cria_no_curso(Curso info, Arv23_Curso *esq, Arv23_Curso *cen);

// Acopla dados de um curso em uma vaga disponivel de um no
void adiciona_curso(Arv23_Curso **no, Curso info, Arv23_Curso *sub);

// Divide um no de curso cheio em dois subnos
Arv23_Curso *quebra_curso(Arv23_Curso **no, Curso info, Curso *sobe, Arv23_Curso *dir);


// =======================
// DISCIPLINAS
// =======================

// Aloca e instancia um no de disciplina
Arv23_Disciplina *cria_no_disciplina(Disciplina info, Arv23_Disciplina *F_esq, Arv23_Disciplina *F_cen);

// Adiciona os dados da disciplina em um slot vazio do no
void adiciona_infos_disciplina(Arv23_Disciplina **no, Disciplina info, Arv23_Disciplina *Sub_Arv_Info);

// Funcao encarregada de desmembrar um no de disciplina saturado
Arv23_Disciplina *quebra_no_disciplina(Arv23_Disciplina **no, Disciplina info, Disciplina *sobe, Arv23_Disciplina *F_dir);

#endif