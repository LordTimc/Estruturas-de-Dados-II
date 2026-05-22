#ifndef ARV23_DISCIPLINA_H
#define ARV23_DISCIPLINA_H
#include "structs.h"

Arv23_Disciplina *cria_no_DISCIPLINA(DISCIPLINA info, Arv23_Disciplina *F_esq, Arv23_Disciplina *F_cen);
int eh_folha_DISCIPLINA(Arv23_Disciplina *no);
Arv23_Disciplina *buscar_menor_elemento_DISCIPLINA(Arv23_Disciplina *no);
DISCIPLINA *buscar_info_disciplina(Arv23_Disciplina *raiz, int codigo);

void adiciona_infos_DISCIPLINA(Arv23_Disciplina **no, DISCIPLINA info, Arv23_Disciplina *Sub_Arv_Info);
Arv23_Disciplina *quebra_no_DISCIPLINA(Arv23_Disciplina **no, DISCIPLINA info, DISCIPLINA *sobe, Arv23_Disciplina *F_dir);
int insere_23_DISCIPLINA(Arv23_Disciplina **raiz, DISCIPLINA valor);

StatusRemocao remover_23_DISCIPLINA(Arv23_Disciplina **raiz, int codigo);
void imprime_23_em_ordem_DISCIPLINA(Arv23_Disciplina *raiz);
#endif