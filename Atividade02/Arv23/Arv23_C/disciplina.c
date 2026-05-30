#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Arv23_H/disciplina.h"
#include "../Arv23_H/curso.h"

#include "../Arv23_H/structs.h"
#include "../Arv23_H/suporteArv23.h"


// Funcao para verificar ausenca de ramificacoes no de disciplina
int eh_folha_disciplina(Arv23_Disciplina *no) {
    return (no != NULL && no->esq == NULL);
}

// Funcao que gerencia o cadastro de uma disciplina na arvore 2-3
int cadastrar_disciplina(Arv23_Disciplina **raiz, Disciplina nova_disciplina) {
    int sucesso = 0;

    // Tenta realizar a insercao fisica da disciplina na arvore 2-3
    sucesso = insere_23_disciplina(raiz, nova_disciplina);

    // Ponto unico de saida retornando o status (1 para sucesso, 0 para erro)
    return sucesso;
}

// Funcao para recuperar o menor registro na ramificacao descrita
Arv23_Disciplina *buscar_menor_elemento_disciplina(Arv23_Disciplina *no) {
    Arv23_Disciplina *atual = no;
    while (atual != NULL && atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// Funcao de varredura para extrair dados da disciplina atraves de seu codigo
Disciplina *buscar_info_disciplina(Arv23_Disciplina *raiz, int codigo) {
    Disciplina *retorno = NULL;
    if (raiz != NULL) {
        if (raiz->info1.codigo == codigo)
            retorno = &(raiz->info1);
        else if (raiz->nInfo == 2 && raiz->info2.codigo == codigo)
            retorno = &(raiz->info2);
        else if (codigo < raiz->info1.codigo)
            retorno = buscar_info_disciplina(raiz->esq, codigo);
        else if (raiz->nInfo == 1 || codigo < raiz->info2.codigo)
            retorno = buscar_info_disciplina(raiz->cen, codigo);
        else
            retorno = buscar_info_disciplina(raiz->dir, codigo);
    }
    return retorno;
}


// Funcao recursiva de suporte para acomodar nova disciplina na arvore
int insere_23_recursivo_disciplina(Arv23_Disciplina **raiz, Disciplina valor, Disciplina *sobe, Arv23_Disciplina **maiorNo) {
    int sucesso = 0;
    Arv23_Disciplina *atual = *raiz;
    if (atual == NULL) {
        *raiz = cria_no_disciplina(valor, NULL, NULL);
        *maiorNo = NULL;
        sucesso = (*raiz != NULL);
    } else if (valor.codigo == atual->info1.codigo || (atual->nInfo == 2 && valor.codigo == atual->info2.codigo)) {
        *maiorNo = NULL;
        sucesso = 0;
    } else {
        if (eh_folha_disciplina(atual)) {
            if (atual->nInfo == 1) {
                adiciona_infos_disciplina(raiz, valor, NULL);
                *maiorNo = NULL;
                sucesso = 1;
            } else {
                *maiorNo = quebra_no_disciplina(raiz, valor, sobe, NULL);
                sucesso = (*maiorNo != NULL);
            }
        } else {
            Arv23_Disciplina **proximo_filho;
            if (valor.codigo < atual->info1.codigo)
                proximo_filho = &(atual->esq);
            else if (atual->nInfo == 1 || valor.codigo < atual->info2.codigo)
                proximo_filho = &(atual->cen);
            else
                proximo_filho = &(atual->dir);

            int sucesso_rec = insere_23_recursivo_disciplina(proximo_filho, valor, sobe, maiorNo);
            if (*maiorNo != NULL) {
                Disciplina chave_subiu = *sobe;
                Arv23_Disciplina *novo_filho = *maiorNo;
                *maiorNo = NULL;
                if (atual->nInfo == 1) {
                    adiciona_infos_disciplina(raiz, chave_subiu, novo_filho);
                    sucesso = 1;
                } else {
                    *maiorNo = quebra_no_disciplina(raiz, chave_subiu, sobe, novo_filho);
                    sucesso = (*maiorNo != NULL);
                }
            } else {
                sucesso = sucesso_rec;
            }
        }
    }
    return sucesso;
}

// Funcao publica para realizar a inclusao de disciplinas
int insere_23_disciplina(Arv23_Disciplina **raiz, Disciplina valor) {
    int sucesso = 0;
    Disciplina sobe;
    Arv23_Disciplina *maiorNo = NULL;
    if (raiz != NULL) {
        sucesso = insere_23_recursivo_disciplina(raiz, valor, &sobe, &maiorNo);
        if (maiorNo != NULL) {
            Arv23_Disciplina *nova_raiz = cria_no_disciplina(sobe, *raiz, maiorNo);
            if (nova_raiz != NULL)
                *raiz = nova_raiz;
            else
                sucesso = 0;
        }
    }
    return sucesso;
}

// Retorna o unico filho remanescente de um no deficiente.
// Prioriza o filho esquerdo; se nulo, retorna o filho central.
Arv23_Disciplina *pega_filho(Arv23_Disciplina *no) {
    Arv23_Disciplina *filho = NULL;

    // Verifica se o filho esquerdo existe e o usa
    if (no->esq != NULL) {
        filho = no->esq;
    } else {
        // Caso contrario, usa o filho central
        filho = no->cen;
    }

    return filho;
}

// Redistribui dados entre um filho deficiente e seu irmao esquerdo,
// fazendo uma chave do pai descer para o filho e uma chave do irmao
// esquerdo subir para o pai, reequilibrando a arvore 2-3.
int redistribuir_com_irmao_esquerdo_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq,
                                                int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Disciplina *filho = *ponteiro_filho;

    Disciplina chave_pai_desce;

    // Guarda o filho mais a direita do irmao, que sera transferido para o filho
    Arv23_Disciplina *filho_transferido = irmao_esq->dir;

    // Guarda o unico filho existente do no deficiente (esq tem prioridade sobre cen)
    Arv23_Disciplina *filho_original_unico = pega_filho(filho);

    // Determina qual chave do pai desce e qual chave do irmao sobe,
    // de acordo com a posicao do filho deficiente em relacao ao pai
    if (pos_filho == 1) {
        // Filho e o filho do meio: a chave da esquerda do pai desce
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_esq->info2;
    } else {
        // Filho e o filho da direita: a chave da direita do pai desce
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_esq->info2;
    }

    // Monta o filho deficiente com a chave que desceu do pai,
    // ajustando seus ponteiros para refletir a nova distribuicao
    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq   = filho_transferido;
    filho->cen   = filho_original_unico;
    filho->dir   = NULL;

    // Remove a chave e o filho transferido do irmao esquerdo,
    // que agora passa a ter apenas uma chave
    irmao_esq->nInfo = 1;
    irmao_esq->dir   = NULL;

    sucesso = 1;
    return sucesso;
}

// Redistribui dados entre um filho deficiente e seu irmao direito,
// fazendo uma chave do pai descer para o filho e uma chave do irmao
// direito subir para o pai, reequilibrando a arvore 2-3.
int redistribuir_com_irmao_direito_disciplina(Arv23_Disciplina **ponteiro_filho,
                                               Arv23_Disciplina *pai,
                                               Arv23_Disciplina *irmao_dir,
                                               int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Disciplina *filho = *ponteiro_filho;

    Disciplina chave_pai_desce;

    // Guarda o filho mais a esquerda do irmao, que sera transferido para o filho
    Arv23_Disciplina *filho_transferido    = irmao_dir->esq;

    // Guarda o unico filho existente do no deficiente (esq tem prioridade sobre cen)
    Arv23_Disciplina *filho_original_unico = pega_filho(filho);

    // Determina qual chave do pai desce e qual chave do irmao sobe,
    // de acordo com a posicao do filho deficiente em relacao ao pai
    if (pos_filho == 0) {
        // Filho e o filho da esquerda: a chave da esquerda do pai desce
        chave_pai_desce = pai->info1;
        pai->info1      = irmao_dir->info1;
    } else {
        // Filho e o filho do meio: a chave da direita do pai desce
        chave_pai_desce = pai->info2;
        pai->info2      = irmao_dir->info1;
    }

    // Monta o filho deficiente com a chave que desceu do pai,
    // ajustando seus ponteiros para refletir a nova distribuicao
    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq   = filho_original_unico;
    filho->cen   = filho_transferido;
    filho->dir   = NULL;

    // Compacta o irmao direito: promove sua segunda chave para a primeira
    // posicao e ajusta os ponteiros, removendo o filho transferido
    irmao_dir->info1 = irmao_dir->info2;
    irmao_dir->nInfo = 1;
    irmao_dir->esq   = irmao_dir->cen;
    irmao_dir->cen   = irmao_dir->dir;
    irmao_dir->dir   = NULL;

    sucesso = 1;
    return sucesso;
}

// Funde um filho deficiente com seu irmao esquerdo, fazendo uma chave
// do pai descer para o no fundido e liberando o filho deficiente.
// Retorna 0 se o pai entrou em underflow ou 1 se o pai permanece valido.
int fundir_com_irmao_esquerdo_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq,
                                          int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Disciplina *filho = *ponteiro_filho;

    Disciplina chave_pai_desce;

    // Guarda o unico filho remanescente do no deficiente (esq tem prioridade sobre cen)
    Arv23_Disciplina *filho_remanescente = pega_filho(filho);

    // Determina qual chave do pai desce e verifica se o pai
    // entrara em underflow apos perder sua unica chave
    if (pai->nInfo == 1) {
        // Pai so tem uma chave: ela desce e o pai fica vazio (underflow)
        chave_pai_desce = pai->info1;
        pai->nInfo = 0;
        // sucesso permanece 0 para sinalizar underflow no pai
    } else {
        // Pai tem duas chaves: determina qual desce conforme posicao do filho
        if (pos_filho == 1) {
            // Filho e o do meio: a chave da esquerda do pai desce
            // e a chave da direita ocupa o lugar da esquerda
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
        } else {
            // Filho e o da direita: a chave da direita do pai desce
            chave_pai_desce = pai->info2;
        }
        pai->nInfo = 1;
        sucesso    = 1;
    }

    // Incorpora a chave que desceu do pai ao irmao esquerdo,
    // que absorve tambem o filho remanescente do no deficiente
    irmao_esq->info2 = chave_pai_desce;
    irmao_esq->nInfo = 2;
    irmao_esq->dir = filho_remanescente;

    // Atualiza os ponteiros do pai para refletir a remocao do filho deficiente
    if (pos_filho == 1) {
        // Filho do meio foi removido: o filho da direita passa para o centro
        pai->cen = pai->dir;
    } 

    // Se o pai ficou vazio, anula tambem seus ponteiros filhos
    if (pai->nInfo == 0) {
        pai->cen = NULL;
    }
    // Filho do meio foi removido
    // Filho da direita foi removido
    // Ou Se o pai ficou vazio: anula o ponteiro direito tambem
    pai->dir = NULL;

    // Libera o no deficiente que foi absorvido pelo irmao
    free(filho);

    return sucesso;
}

// Funde um filho deficiente com seu irmao direito, fazendo uma chave
// do pai descer para o no fundido e liberando o filho deficiente.
// Retorna 0 se o pai entrou em underflow ou 1 se o pai permanece valido.
int fundir_com_irmao_direito_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_dir,
                                         int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Disciplina *filho = *ponteiro_filho;

    Disciplina chave_pai_desce;

    // Guarda o unico filho remanescente do no deficiente
    Arv23_Disciplina *filho_remanescente = pega_filho(filho);

    // Determina qual chave do pai desce e verifica se o pai
    // entrara em underflow apos perder sua unica chave
    if (pai->nInfo == 1) {
        // Pai so tem uma chave: ela desce e o pai fica vazio (underflow)
        chave_pai_desce = pai->info1;
        pai->nInfo = 0;
        // sucesso permanece 0 para sinalizar underflow no pai
    } else {
        // Pai tem duas chaves: determina qual desce conforme posicao do filho
        if (pos_filho == 0) {
            // Filho e o da esquerda: a chave da esquerda do pai desce
            // e a chave da direita ocupa o lugar da esquerda
            chave_pai_desce = pai->info1;
            pai->info1 = pai->info2;
        } else {
            // Filho e o do meio: a chave da direita do pai desce
            chave_pai_desce = pai->info2;
        }
        pai->nInfo = 1;
        sucesso = 1;
    }

    // Incorpora a chave que desceu do pai ao irmao direito,
    // deslocando sua chave existente para a segunda posicao
    // e absorvendo o filho remanescente do no deficiente
    irmao_dir->info2 = irmao_dir->info1;
    irmao_dir->info1 = chave_pai_desce;
    irmao_dir->nInfo = 2;
    irmao_dir->dir = irmao_dir->cen;
    irmao_dir->cen = irmao_dir->esq;
    irmao_dir->esq = filho_remanescente;

    // Atualiza os ponteiros do pai para refletir a remocao do filho deficiente
    if (pos_filho == 0) {
        // Filho da esquerda foi removido: centro sobe para esquerda, direita sobe para centro
        pai->esq = pai->cen;
        pai->cen = pai->dir;
    } else {
        // Filho do meio foi removido: direita sobe para centro
        pai->cen = pai->dir;
    }

    // Se o pai ficou vazio, anula tambem seus ponteiros filhos
    if (pai->nInfo == 0) {
        pai->cen = NULL;
    }
    // Filho removido ou pai vazio: anula sempre o ponteiro direito
    pai->dir = NULL;

    // Libera o no deficiente que foi absorvido pelo irmao
    free(filho);

    return sucesso;
}


// Verifica se o filho esta em underflow e resolve redistribuindo ou fundindo
// com o irmao disponivel. Retorna 1 se resolvido sem underflow no pai,
// 0 se o pai tambem entrou em underflow, e -1 se nao foi possivel tratar.
int tratar_underflow_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai) {
    int sucesso = 1;

    Arv23_Disciplina *filho = *ponteiro_filho;

    if (filho != NULL && filho->nInfo == 0 && pai == NULL) {
        // Filho vazio sem pai: underflow na raiz, nao ha como resolver
        sucesso = 0;
    } else if (filho != NULL && filho->nInfo == 0) {
        // Filho esta em underflow: identifica posicao e irmaos disponiveis
        Arv23_Disciplina *irmao_esq = NULL;
        Arv23_Disciplina *irmao_dir = NULL;
        int pos_filho = -1;

        // Determina a posicao do filho deficiente e seus irmaos adjacentes
        if (pai->esq == filho) {
            pos_filho = 0;
            irmao_dir = pai->cen;
        } else if (pai->cen == filho) {
            pos_filho = 1;
            irmao_esq = pai->esq;
            if (pai->nInfo == 2)
                irmao_dir = pai->dir;
        } else {
            pos_filho = 2;
            irmao_esq = pai->cen;
        }

        // Tenta redistribuir ou fundir com o irmao disponivel,
        // priorizando redistribuicao (irmao com 2 chaves) sobre fusao
        if (irmao_dir != NULL && irmao_dir->nInfo == 2) {
            sucesso = redistribuir_com_irmao_direito_disciplina(ponteiro_filho, pai, irmao_dir, pos_filho);
        } else if (irmao_esq != NULL && irmao_esq->nInfo == 2) {
            sucesso = redistribuir_com_irmao_esquerdo_disciplina(ponteiro_filho, pai, irmao_esq, pos_filho);
        } else if (irmao_dir != NULL && irmao_dir->nInfo == 1) {
            sucesso = fundir_com_irmao_direito_disciplina(ponteiro_filho, pai, irmao_dir, pos_filho);
        } else if (irmao_esq != NULL && irmao_esq->nInfo == 1) {
            sucesso = fundir_com_irmao_esquerdo_disciplina(ponteiro_filho, pai, irmao_esq, pos_filho);
        } else {
            // Nenhum irmao disponivel para resolver o underflow
            sucesso = -1;
        }
    }
    // Se filho e NULL ou nInfo > 0, nao ha underflow: sucesso permanece 1

    return sucesso;
}

// Percorre recursivamente a arvore para localizar e remover a disciplina
// com o codigo informado. Retorna 1 se removeu sem problemas, 0 se o no
// ficou vazio (underflow), -1 se nao encontrou e -2 se houve outro erro.
int remover_recursivo_disciplina(Arv23_Disciplina **ponteiro_no_atual, int codigo) {
    int sucesso = -1;

    Arv23_Disciplina *atual = *ponteiro_no_atual;

    if (atual == NULL) {
        // Codigo nao existe na arvore
        sucesso = -1;
    } else {
        Arv23_Disciplina **prox_ptr = NULL;
        int achou  = 0;
        int indice = -1;

        // Verifica se o codigo esta no no atual e em qual posicao
        if (codigo == atual->info1.codigo) {
            achou  = 1;
            indice = 0;
        } else if (atual->nInfo == 2 && codigo == atual->info2.codigo) {
            achou  = 1;
            indice = 1;
        } else if (codigo < atual->info1.codigo) {
            // Codigo esta na subarvore esquerda
            prox_ptr = &(atual->esq);
        } else if (atual->nInfo == 1 || codigo < atual->info2.codigo) {
            // Codigo esta na subarvore central
            prox_ptr = &(atual->cen);
        } else {
            // Codigo esta na subarvore direita
            prox_ptr = &(atual->dir);
        }

        if (achou) {
            if (eh_folha_disciplina(atual)) {
                // No e folha: remove diretamente sem precisar de sucessor
                if (atual->nInfo == 2) {
                    // No tem duas chaves: apenas descarta a chave removida
                    if (indice == 0)
                        atual->info1 = atual->info2;
                    atual->nInfo = 1;
                    sucesso = 1;
                } else {
                    // No tem uma chave: fica vazio, sinaliza underflow
                    atual->nInfo = 0;
                    sucesso = 0;
                }
            } else {
                // No interno: substitui pelo sucessor em-ordem e remove o sucessor
                Arv23_Disciplina  *sucessor = NULL;
                Arv23_Disciplina **ptr_sub  = NULL;

                // Localiza o sucessor na subarvore correspondente a chave removida
                if (indice == 0) {
                    sucessor = buscar_menor_elemento_disciplina(atual->cen);
                    ptr_sub  = &(atual->cen);
                } else {
                    sucessor = buscar_menor_elemento_disciplina(atual->dir);
                    ptr_sub  = &(atual->dir);
                }

                if (sucessor == NULL) {
                    // Nao encontrou sucessor, situacao inesperada
                    sucesso = -2;
                } else {
                    // Copia o valor do sucessor para o lugar da chave removida
                    Disciplina valor_suc = sucessor->info1;

                    if (indice == 0)
                        atual->info1 = valor_suc;
                    else
                        atual->info2 = valor_suc;

                    // Remove o sucessor recursivamente na subarvore
                    int stat_suc = remover_recursivo_disciplina(ptr_sub, valor_suc.codigo);

                    if (stat_suc == 0) {
                        // Subarvore entrou em underflow: trata antes de retornar
                        sucesso = tratar_underflow_disciplina(ptr_sub, atual);
                    } else {
                        sucesso = stat_suc;
                    }
                }
            }
        } else {
            // Codigo nao esta no no atual: continua descendo na subarvore correta
            int stat_rec = remover_recursivo_disciplina(prox_ptr, codigo);

            if (stat_rec == 0) {
                // Subarvore entrou em underflow: trata antes de retornar
                sucesso = tratar_underflow_disciplina(prox_ptr, atual);
            } else {
                sucesso = stat_rec;
            }
        }
    }

    return sucesso;
}


// Realiza a remocao completa de uma disciplina pela raiz da arvore.
// Ajusta a raiz caso ela fique vazia apos a remocao.
// Retorna 1 se removeu com sucesso, 0 ou negativo em caso de erro.
int remover_23_disciplina(Arv23_Disciplina **raiz, int codigo) {
    int sucesso = 0;

    if (raiz == NULL || *raiz == NULL) {
        // Arvore vazia: nada a remover
        sucesso = -1;
    } else {
        sucesso = remover_recursivo_disciplina(raiz, codigo);

        // Se a raiz ficou sem chaves apos a remocao, promove o filho como nova raiz
        if (*raiz != NULL && (*raiz)->nInfo == 0) {
            Arv23_Disciplina *antiga = *raiz;

            if (antiga->esq != NULL) {
                *raiz = antiga->esq;
            } else {
                *raiz = antiga->cen;
            }

            free(antiga);
            sucesso = 1;
        }
    }

    return sucesso;
}

// Funcao para realizar a impressao sequencial in-order das disciplinas
void imprime_23_em_ordem_disciplina(Arv23_Disciplina *raiz) {
    if (raiz != NULL) {
        imprime_23_em_ordem_disciplina(raiz->esq);
        printf("- Disciplina [%d]: %s (Bloco %d | %dh)\n", raiz->info1.codigo, raiz->info1.nome, raiz->info1.bloco, raiz->info1.carga_horaria);
        imprime_23_em_ordem_disciplina(raiz->cen);
        if (raiz->nInfo == 2) {
            printf("- Disciplina [%d]: %s (Bloco %d | %dh)\n", raiz->info2.codigo, raiz->info2.nome, raiz->info2.bloco, raiz->info2.carga_horaria);
            imprime_23_em_ordem_disciplina(raiz->dir);
        }
    }
}

void imprime_disciplinas_bloco(Arv23_Disciplina *raiz, int bloco) {
    if (raiz != NULL) {
        imprime_disciplinas_bloco(raiz->esq, bloco);
        if (raiz->info1.bloco == bloco) 
            printf("Disciplina [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        imprime_disciplinas_bloco(raiz->cen, bloco);
        if (raiz->nInfo == 2) {
            if (raiz->info2.bloco == bloco) 
                printf("Disciplina [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            imprime_disciplinas_bloco(raiz->dir, bloco);
        }
    }
}

void imprime_disciplinas_carga(Arv23_Disciplina *raiz, int carga) {
    if (raiz != NULL) {
        imprime_disciplinas_carga(raiz->esq, carga);
        if (raiz->info1.carga_horaria == carga) 
            printf("Disciplina [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        imprime_disciplinas_carga(raiz->cen, carga);
        if (raiz->nInfo == 2) {
            if (raiz->info2.carga_horaria == carga) 
                printf("Disciplina [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            imprime_disciplinas_carga(raiz->dir, carga);
        }
    }
}

// Libera recursivamente todos os nós da árvore 2-3 de disciplinas
void libera_arvore_disciplina(Arv23_Disciplina **raiz) {
    if (raiz && *raiz != NULL) {
        // Percorre e libera as três subárvores (esquerda, centro e direita)
        libera_arvore_disciplina(&(*raiz)->esq);
        libera_arvore_disciplina(&(*raiz)->cen);
        libera_arvore_disciplina(&(*raiz)->dir);

        // Libera o nó de disciplina atual
        free(*raiz);
        *raiz = NULL;
    }
}