#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Arv23_H/aluno.h"
#include "../Arv23_H/curso.h"
#include "../Arv23_H/disciplina.h"

#include "../Arv23_H/structs.h"
#include "../Arv23_H/auxiliares.h"
#include "../Arv23_H/suporteArv23.h"

// =======================
// ALUNO
// =======================

// Funcao para alocar e criar um novo no de aluno
Arv23_Aluno *cria_no_aluno(Aluno info, Arv23_Aluno *esq, Arv23_Aluno *cen) {
    Arv23_Aluno *no = (Arv23_Aluno *)malloc(sizeof(Arv23_Aluno));
    if (no) {
        no->info1 = info;
        no->nInfo = 1;
        no->esq = esq;
        no->cen = cen;
        no->dir = NULL;
    }
    return no;
}

// Funcao para adicionar uma informacao dentro de um no de aluno ja existente
void adiciona_aluno(Arv23_Aluno **no, Aluno info, Arv23_Aluno *sub) {
    Arv23_Aluno *atual = *no;
    if (info.matricula > atual->info1.matricula) {
        atual->info2 = info;
        atual->dir = sub;
    }
    else {
        atual->info2 = atual->info1;
        atual->info1 = info;
        atual->dir = atual->cen;
        atual->cen = sub;
    }
    atual->nInfo = 2;
}

// Funcao para dividir um no de aluno cheio em dois subnos
Arv23_Aluno *quebra_aluno(Arv23_Aluno **no, Aluno info, Aluno *sobe, Arv23_Aluno *dir) {
    Arv23_Aluno *atual = *no;
    Arv23_Aluno *maior = NULL;
    if (info.matricula > atual->info2.matricula) {
        *sobe = atual->info2;
        maior = cria_no_aluno(info, atual->dir, dir);
        
    }
    else if (info.matricula > atual->info1.matricula) {
        *sobe = info;
        maior = cria_no_aluno(atual->info2, dir, atual->dir);
    }
    else {
        *sobe = atual->info1;
        maior = cria_no_aluno(atual->info2, atual->cen, atual->dir);
        atual->info1 = info;
        atual->cen = dir;

    }
    atual->nInfo = 1;
    atual->dir = NULL;
    return maior;
}


// =======================
// CURSO
// =======================

// Funcao para alocar memoria e configurar um no de curso
Arv23_Curso *cria_no_curso(Curso info, Arv23_Curso *esq, Arv23_Curso *cen) {
    Arv23_Curso *no = (Arv23_Curso *)malloc(sizeof(Arv23_Curso));
    if (no != NULL) {
        no->info1 = info;
        no->nInfo = 1;
        no->esq = esq;
        no->cen = cen;
        no->dir = NULL;
    }
    return no;
}

// Funcao para acoplar dados de um curso em uma vaga disponivel de um no
void adiciona_curso(Arv23_Curso **no, Curso info, Arv23_Curso *sub) {
    Arv23_Curso *atual = *no;
    if (info.codigo > atual->info1.codigo) {
        atual->info2 = info;
        atual->dir = sub;
    }
    else {
        atual->info2 = atual->info1;
        atual->info1 = info;
        atual->dir = atual->cen;
        atual->cen = sub;
    }
    atual->nInfo = 2;
}

// Funcao para dividir um no de curso cheio em dois subnos
Arv23_Curso *quebra_curso(Arv23_Curso **no, Curso info, Curso *sobe, Arv23_Curso *dir) {
    Arv23_Curso *atual = *no;
    Arv23_Curso *maior = NULL;
    if (info.codigo > atual->info2.codigo) {
        *sobe = atual->info2;
        maior = cria_no_curso(info, atual->dir, dir);
    }
    else if (info.codigo > atual->info1.codigo) {
        *sobe = info;
        maior = cria_no_curso(atual->info2, dir, atual->dir);

    }
    else {
        *sobe = atual->info1;
        maior = cria_no_curso(atual->info2, atual->cen, atual->dir);
        atual->info1 = info;
        atual->cen = dir;        
    }
    atual->nInfo = 1;
    atual->dir = NULL;
    return maior;
}


// =======================
// DISCIPLINAS
// =======================

// Funcao para alocar e instanciar um no de disciplina
Arv23_Disciplina *cria_no_disciplina(Disciplina info, Arv23_Disciplina *F_esq, Arv23_Disciplina *F_cen) {
    Arv23_Disciplina *no = (Arv23_Disciplina *)malloc(sizeof(Arv23_Disciplina));
    if (no != NULL) {
        no->info1 = info;
        no->nInfo = 1;
        no->esq = F_esq;
        no->cen = F_cen;
        no->dir = NULL;
    }
    return no;
}

// Funcao para indexar dados de disciplina em slot vazio do no indicado
void adiciona_infos_disciplina(Arv23_Disciplina **no, Disciplina info, Arv23_Disciplina *Sub_Arv_Info) {
    Arv23_Disciplina *atual = *no;
    if (info.codigo > atual->info1.codigo) {
        atual->info2 = info;
        atual->dir = Sub_Arv_Info;
    } else {
        atual->info2 = atual->info1;
        atual->info1 = info;
        atual->dir = atual->cen;
        atual->cen = Sub_Arv_Info;
    }
    atual->nInfo = 2;
}

// Funcao encarregada de desmembrar um no de disciplina saturado
Arv23_Disciplina *quebra_no_disciplina(Arv23_Disciplina **no, Disciplina info, Disciplina *sobe, Arv23_Disciplina *F_dir) {
    Arv23_Disciplina *atual = *no;
    Arv23_Disciplina *maior = NULL;
    if (info.codigo > atual->info2.codigo) {
        *sobe = atual->info2;
        maior = cria_no_disciplina(info, atual->dir, F_dir);
    } else if (info.codigo > atual->info1.codigo) {
        *sobe = info;
        maior = cria_no_disciplina(atual->info2, F_dir, atual->dir);
    } else {
        *sobe = atual->info1;
        maior = cria_no_disciplina(atual->info2, atual->cen, atual->dir);
        atual->info1 = info;
        atual->cen = F_dir;
    }
    atual->nInfo = 1;
    atual->dir = NULL;
    return maior;
}