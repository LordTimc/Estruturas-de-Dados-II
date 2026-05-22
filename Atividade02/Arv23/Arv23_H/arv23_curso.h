#ifndef ARV23_CURSO_H
#define ARV23_CURSO_H
#include "structs.h"

int insere_23_CURSO(Arv23_Curso **raiz, CURSO valor);
CURSO *buscar_info_curso(Arv23_Curso *raiz, int codigo);
StatusRemocao remover_23_CURSO(Arv23_Curso **raiz, int codigo);
void imprime_23_em_ordem_CURSO(Arv23_Curso *raiz);

#endif