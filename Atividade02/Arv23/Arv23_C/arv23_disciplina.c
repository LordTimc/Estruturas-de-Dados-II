#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv23_disciplina.h"

Arv23_Disciplina *cria_no_DISCIPLINA(DISCIPLINA info, Arv23_Disciplina *F_esq, Arv23_Disciplina *F_cen) {
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

int eh_folha_DISCIPLINA(Arv23_Disciplina *no) {
    return (no != NULL && no->esq == NULL);
}

Arv23_Disciplina *buscar_menor_elemento_DISCIPLINA(Arv23_Disciplina *no) {
    Arv23_Disciplina *atual = no;
    while (atual != NULL && atual->esq != NULL) atual = atual->esq;
    return atual;
}

DISCIPLINA *buscar_info_disciplina(Arv23_Disciplina *raiz, int codigo) {
    DISCIPLINA *retorno = NULL;
    if (raiz != NULL) {
        if (raiz->info1.codigo == codigo) retorno = &(raiz->info1);
        else if (raiz->nInfo == 2 && raiz->info2.codigo == codigo) retorno = &(raiz->info2);
        else if (codigo < raiz->info1.codigo) retorno = buscar_info_disciplina(raiz->esq, codigo);
        else if (raiz->nInfo == 1 || codigo < raiz->info2.codigo) retorno = buscar_info_disciplina(raiz->cen, codigo);
        else retorno = buscar_info_disciplina(raiz->dir, codigo);
    }
    return retorno;
}

void adiciona_infos_DISCIPLINA(Arv23_Disciplina **no, DISCIPLINA info, Arv23_Disciplina *Sub_Arv_Info) {
    Arv23_Disciplina *no_atual = *no;
    if (info.codigo > no_atual->info1.codigo) {
        no_atual->info2 = info;
        no_atual->dir = Sub_Arv_Info;
    } else {
        no_atual->info2 = no_atual->info1;
        no_atual->info1 = info;
        no_atual->dir = no_atual->cen;
        no_atual->cen = Sub_Arv_Info;
    }
    no_atual->nInfo = 2;
}

Arv23_Disciplina *quebra_no_DISCIPLINA(Arv23_Disciplina **no, DISCIPLINA info, DISCIPLINA *sobe, Arv23_Disciplina *F_dir) {
    Arv23_Disciplina *no_atual = *no;
    Arv23_Disciplina *maior = NULL;
    if (info.codigo > no_atual->info2.codigo) {
        *sobe = no_atual->info2;
        maior = cria_no_DISCIPLINA(info, no_atual->dir, F_dir);
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    } else if (info.codigo > no_atual->info1.codigo) {
        *sobe = info;
        maior = cria_no_DISCIPLINA(no_atual->info2, F_dir, no_atual->dir);
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    } else {
        *sobe = no_atual->info1;
        maior = cria_no_DISCIPLINA(no_atual->info2, no_atual->cen, no_atual->dir);
        no_atual->info1 = info;
        no_atual->cen = F_dir;
        no_atual->nInfo = 1;
        no_atual->dir = NULL;
    }
    return maior;
}

static int insere_23_recursivo_DISCIPLINA(Arv23_Disciplina **raiz, DISCIPLINA valor, DISCIPLINA *sobe, Arv23_Disciplina **maiorNo) {
    int sucesso = 0;
    Arv23_Disciplina *no_atual = *raiz;
    if (no_atual == NULL) {
        *raiz = cria_no_DISCIPLINA(valor, NULL, NULL);
        *maiorNo = NULL;
        sucesso = (*raiz != NULL);
    } else if (valor.codigo == no_atual->info1.codigo || (no_atual->nInfo == 2 && valor.codigo == no_atual->info2.codigo)) {
        *maiorNo = NULL;
        sucesso = 0;
    } else {
        if (eh_folha_DISCIPLINA(no_atual)) {
            if (no_atual->nInfo == 1) {
                adiciona_infos_DISCIPLINA(raiz, valor, NULL);
                *maiorNo = NULL;
                sucesso = 1;
            } else {
                *maiorNo = quebra_no_DISCIPLINA(raiz, valor, sobe, NULL);
                sucesso = (*maiorNo != NULL);
            }
        } else {
            Arv23_Disciplina **proximo_filho;
            if (valor.codigo < no_atual->info1.codigo) proximo_filho = &(no_atual->esq);
            else if (no_atual->nInfo == 1 || valor.codigo < no_atual->info2.codigo) proximo_filho = &(no_atual->cen);
            else proximo_filho = &(no_atual->dir);

            int sucesso_rec = insere_23_recursivo_DISCIPLINA(proximo_filho, valor, sobe, maiorNo);
            if (*maiorNo != NULL) {
                DISCIPLINA chave_subiu = *sobe;
                Arv23_Disciplina *novo_filho = *maiorNo;
                *maiorNo = NULL;
                if (no_atual->nInfo == 1) {
                    adiciona_infos_DISCIPLINA(raiz, chave_subiu, novo_filho);
                    sucesso = 1;
                } else {
                    *maiorNo = quebra_no_DISCIPLINA(raiz, chave_subiu, sobe, novo_filho);
                    sucesso = (*maiorNo != NULL);
                }
            } else {
                sucesso = sucesso_rec;
            }
        }
    }
    return sucesso;
}

int insere_23_DISCIPLINA(Arv23_Disciplina **raiz, DISCIPLINA valor) {
    int sucesso = 0;
    DISCIPLINA sobe;
    Arv23_Disciplina *maiorNo = NULL;
    if (raiz != NULL) {
        sucesso = insere_23_recursivo_DISCIPLINA(raiz, valor, &sobe, &maiorNo);
        if (maiorNo != NULL) {
            Arv23_Disciplina *nova_raiz = cria_no_DISCIPLINA(sobe, *raiz, maiorNo);
            if (nova_raiz != NULL) *raiz = nova_raiz;
            else sucesso = 0;
        }
    }
    return sucesso;
}

// ==== LÓGICA DE REMOÇÃO (SEGUINDO SEU MOLDE) ====
static StatusRemocao redistribuir_com_irmao_esquerdo_DISCIPLINA(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq, int pos_filho) {
    Arv23_Disciplina *filho = *ponteiro_filho;
    DISCIPLINA chave_pai_desce;
    Arv23_Disciplina *filho_transferido = irmao_esq->dir;
    Arv23_Disciplina *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

    if (pos_filho == 1) {
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_esq->info2;
    } else {
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_esq->info2;
    }

    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_transferido;
    filho->cen = filho_original_unico;
    filho->dir = NULL;

    irmao_esq->nInfo = 1;
    irmao_esq->dir = NULL;
    return OK;
}

static StatusRemocao redistribuir_com_irmao_direito_DISCIPLINA(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_dir, int pos_filho) {
    Arv23_Disciplina *filho = *ponteiro_filho;
    DISCIPLINA chave_pai_desce;
    Arv23_Disciplina *filho_transferido = irmao_dir->esq;
    Arv23_Disciplina *filho_original_unico = (filho->esq != NULL) ? filho->esq : filho->cen;

    if (pos_filho == 0) {
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_dir->info1;
    } else {
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_dir->info1;
    }

    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_original_unico;
    filho->cen = filho_transferido;
    filho->dir = NULL;

    irmao_dir->info1 = irmao_dir->info2;
    irmao_dir->nInfo = 1;
    irmao_dir->esq = irmao_dir->cen;
    irmao_dir->cen = irmao_dir->dir;
    irmao_dir->dir = NULL;
    return OK;
}

static StatusRemocao fundir_com_irmao_esquerdo_DISCIPLINA(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq, int pos_filho) {
    Arv23_Disciplina *filho_underflow = *ponteiro_filho;
    DISCIPLINA chave_pai_desce;
    StatusRemocao status_pai = OK;
    Arv23_Disciplina *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;

    if (pai->nInfo == 1) {
        chave_pai_desce = pai->info1;
        pai->nInfo = 0;
        status_pai = UNDERFLOW;
    } else {
        if (pos_filho == 1) {
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
        } else chave_pai_desce = pai->info2;
        pai->nInfo = 1;
    }

    irmao_esq->info2 = chave_pai_desce;
    irmao_esq->nInfo = 2;
    irmao_esq->dir = filho_u_remanescente;

    if (pos_filho == 1) { pai->cen = pai->dir; pai->dir = NULL; }
    else pai->dir = NULL;
    if (status_pai == UNDERFLOW) { pai->cen = NULL; pai->dir = NULL; }

    free(filho_underflow);
    return status_pai;
}

static StatusRemocao fundir_com_irmao_direito_DISCIPLINA(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_dir, int pos_filho) {
    Arv23_Disciplina *filho_underflow = *ponteiro_filho;
    DISCIPLINA chave_pai_desce;
    StatusRemocao status_pai = OK;
    Arv23_Disciplina *filho_u_remanescente = (filho_underflow->esq != NULL) ? filho_underflow->esq : filho_underflow->cen;

    if (pai->nInfo == 1) {
        chave_pai_desce = pai->info1;
        pai->nInfo = 0;
        status_pai = UNDERFLOW;
    } else {
        if (pos_filho == 0) {
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
        } else chave_pai_desce = pai->info2;
        pai->nInfo = 1;
    }

    irmao_dir->info2 = irmao_dir->info1;
    irmao_dir->info1 = chave_pai_desce;
    irmao_dir->nInfo = 2;
    irmao_dir->dir = irmao_dir->cen;
    irmao_dir->cen = irmao_dir->esq;
    irmao_dir->esq = filho_u_remanescente;

    if (pos_filho == 0) { pai->esq = pai->cen; pai->cen = pai->dir; pai->dir = NULL; }
    else { pai->cen = pai->dir; pai->dir = NULL; }
    if (status_pai == UNDERFLOW) { pai->cen = NULL; pai->dir = NULL; }

    free(filho_underflow);
    return status_pai;
}

static StatusRemocao tratar_underflow_DISCIPLINA(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai) {
    StatusRemocao status_final = OK;
    Arv23_Disciplina *filho = *ponteiro_filho;

    if (filho == NULL || filho->nInfo > 0) status_final = OK;
    else if (pai == NULL) status_final = UNDERFLOW;
    else {
        Arv23_Disciplina *irmao_esq = NULL;
        Arv23_Disciplina *irmao_dir = NULL;
        int pos_filho = -1;

        if (pai->esq == filho) { pos_filho = 0; irmao_dir = pai->cen; }
        else if (pai->cen == filho) { pos_filho = 1; irmao_esq = pai->esq; if (pai->nInfo == 2) irmao_dir = pai->dir; }
        else { pos_filho = 2; irmao_esq = pai->cen; }

        if (irmao_dir != NULL && irmao_dir->nInfo == 2) status_final = redistribuir_com_irmao_direito_DISCIPLINA(ponteiro_filho, pai, irmao_dir, pos_filho);
        else if (irmao_esq != NULL && irmao_esq->nInfo == 2) status_final = redistribuir_com_irmao_esquerdo_DISCIPLINA(ponteiro_filho, pai, irmao_esq, pos_filho);
        else if (irmao_dir != NULL && irmao_dir->nInfo == 1) status_final = fundir_com_irmao_direito_DISCIPLINA(ponteiro_filho, pai, irmao_dir, pos_filho);
        else if (irmao_esq != NULL && irmao_esq->nInfo == 1) status_final = fundir_com_irmao_esquerdo_DISCIPLINA(ponteiro_filho, pai, irmao_esq, pos_filho);
        else status_final = NAO_FOI_POSSIVEL_T_UNDERFLOW;
    }
    return status_final;
}

static StatusRemocao remover_recursivo_DISCIPLINA(Arv23_Disciplina **ponteiro_no_atual, int codigo) {
    StatusRemocao status_final = OK;
    Arv23_Disciplina *no_atual = *ponteiro_no_atual;

    if (no_atual == NULL) status_final = INFO_NAO_ENCONTRADA;
    else {
        Arv23_Disciplina **prox_ptr = NULL;
        int achou = 0, indice = -1;

        if (codigo == no_atual->info1.codigo) { achou = 1; indice = 0; }
        else if (no_atual->nInfo == 2 && codigo == no_atual->info2.codigo) { achou = 1; indice = 1; }
        else if (codigo < no_atual->info1.codigo) prox_ptr = &(no_atual->esq);
        else if (no_atual->nInfo == 1 || codigo < no_atual->info2.codigo) prox_ptr = &(no_atual->cen);
        else prox_ptr = &(no_atual->dir);

        if (achou) {
            if (eh_folha_DISCIPLINA(no_atual)) {
                if (no_atual->nInfo == 2) {
                    if (indice == 0) no_atual->info1 = no_atual->info2;
                    no_atual->nInfo = 1;
                    status_final = OK;
                } else {
                    no_atual->nInfo = 0;
                    status_final = UNDERFLOW;
                }
            } else {
                Arv23_Disciplina *sucessor = NULL;
                Arv23_Disciplina **ptr_sub = NULL;
                if (indice == 0) {
                    sucessor = buscar_menor_elemento_DISCIPLINA(no_atual->cen);
                    ptr_sub = &(no_atual->cen);
                } else {
                    sucessor = buscar_menor_elemento_DISCIPLINA(no_atual->dir);
                    ptr_sub = &(no_atual->dir);
                }

                if (sucessor == NULL) status_final = SUCESSOR_NAO_ENCONTRADO;
                else {
                    DISCIPLINA valor_suc = sucessor->info1;
                    if (indice == 0) no_atual->info1 = valor_suc;
                    else no_atual->info2 = valor_suc;
                    
                    StatusRemocao stat_suc = remover_recursivo_DISCIPLINA(ptr_sub, valor_suc.codigo);
                    if (stat_suc == UNDERFLOW) status_final = tratar_underflow_DISCIPLINA(ptr_sub, no_atual);
                    else status_final = stat_suc;
                }
            }
        } else {
            StatusRemocao stat_rec = remover_recursivo_DISCIPLINA(prox_ptr, codigo);
            if (stat_rec == UNDERFLOW) status_final = tratar_underflow_DISCIPLINA(prox_ptr, no_atual);
            else status_final = stat_rec;
        }
    }
    return status_final;
}

StatusRemocao remover_23_DISCIPLINA(Arv23_Disciplina **raiz, int codigo) {
    StatusRemocao status_geral = OK;
    if (raiz == NULL || *raiz == NULL) status_geral = ARVORE_VAZIA;
    else {
        status_geral = remover_recursivo_DISCIPLINA(raiz, codigo);
        if (*raiz != NULL && (*raiz)->nInfo == 0) {
            Arv23_Disciplina *antiga = *raiz;
            *raiz = antiga->esq ? antiga->esq : antiga->cen;
            free(antiga);
            status_geral = OK;
        }
    }
    return status_geral;
}

void imprime_23_em_ordem_DISCIPLINA(Arv23_Disciplina *raiz) {
    if (raiz != NULL) {
        imprime_23_em_ordem_DISCIPLINA(raiz->esq);
        printf("- Disciplina [%d]: %s (Bloco %d | %dh)\n", raiz->info1.codigo, raiz->info1.nome, raiz->info1.bloco, raiz->info1.carga_horaria);
        imprime_23_em_ordem_DISCIPLINA(raiz->cen);
        if (raiz->nInfo == 2) {
            printf("- Disciplina [%d]: %s (Bloco %d | %dh)\n", raiz->info2.codigo, raiz->info2.nome, raiz->info2.bloco, raiz->info2.carga_horaria);
            imprime_23_em_ordem_DISCIPLINA(raiz->dir);
        }
    }
}