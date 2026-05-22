#ifndef OPERACOES_H
#define OPERACOES_H
#include "structs.h"

void req_imprimir_alunos_curso(Arv23_Aluno *raiz, int cod_curso);
void req_imprimir_alunos_curso_ano(Arv23_Aluno *raiz, int cod_curso, int ano);
int req_contar_alunos_curso(Arv23_Aluno *raiz, int cod_curso);
void req_imprimir_cursos_blocos(Arv23_Curso *raiz, int blocos);
void req_imprimir_disciplinas_bloco(Arv23_Disciplina *raiz, int bloco);
void req_imprimir_disciplinas_carga(Arv23_Disciplina *raiz, int carga);

#endif