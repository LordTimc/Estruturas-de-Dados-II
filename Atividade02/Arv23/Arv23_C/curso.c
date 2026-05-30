#include <stdio.h>
#include <stdlib.h>
#include "../Arv23_H/curso.h"
#include "../Arv23_H/disciplina.h"

#include "../Arv23_H/structs.h"
#include "../Arv23_H/suporteArv23.h"


// Funcao para validar se o no de curso nao possui ramificacoes
int eh_folha_curso(Arv23_Curso *no) {
    return (no != NULL && no->esq == NULL);
}

// Funcao que gerencia o cadastro de um curso na arvore 2-3
int cadastrar_curso(Arv23_Curso **raiz, Curso novo_curso) {
    int sucesso = 0;

    // Garante que a arvore de disciplinas do novo curso inicie vazia
    novo_curso.arv_disciplinas = NULL;

    // Tenta realizar a insercao fisica do curso na arvore 2-3
    sucesso = insere_23_curso(raiz, novo_curso);

    // Ponto unico de saida retornando o status (1 para sucesso, 0 para erro)
    return sucesso;
}

// Funcao para localizar o menor registro a partir do no de curso fornecido
Arv23_Curso *buscar_menor_curso(Arv23_Curso *no) {
    Arv23_Curso *atual = no;
    while (atual && atual->esq)
        atual = atual->esq;
    return atual;
}

// Funcao de pesquisa para retornar o ponteiro de dados do curso correspondente ao codigo
Curso *buscar_info_curso(Arv23_Curso *raiz, int codigo) {
    Curso *ret = NULL;
    if (raiz != NULL) {
        if (raiz->info1.codigo == codigo)
            ret = &(raiz->info1);
        else if (raiz->nInfo == 2 && raiz->info2.codigo == codigo)
            ret = &(raiz->info2);
        else if (codigo < raiz->info1.codigo)
            ret = buscar_info_curso(raiz->esq, codigo);
        else if (raiz->nInfo == 1 || codigo < raiz->info2.codigo)
            ret = buscar_info_curso(raiz->cen, codigo);
        else
            ret = buscar_info_curso(raiz->dir, codigo);
    }
    return ret;
}


// Funcao recursiva para coordenar a insercao de um curso
int insere_rec_curso(Arv23_Curso **raiz, Curso valor, Curso *sobe, Arv23_Curso **maior) {
    int sucesso = 0;
    Arv23_Curso *atual = *raiz;
    if (atual == NULL) {
        *raiz = cria_no_curso(valor, NULL, NULL);
        *maior = NULL;
        sucesso = (*raiz != NULL);
    }
    else if (valor.codigo == atual->info1.codigo || (atual->nInfo == 2 && valor.codigo == atual->info2.codigo)) {
        *maior = NULL;
        sucesso = 0;
    }
    else {
        if (eh_folha_curso(atual)) {
            if (atual->nInfo == 1) {
                adiciona_curso(raiz, valor, NULL);
                *maior = NULL;
                sucesso = 1;
            }
            else {
                *maior = quebra_curso(raiz, valor, sobe, NULL);
                sucesso = (*maior != NULL);
            }
        } else {
            Arv23_Curso **prox;
            if (valor.codigo < atual->info1.codigo)
                prox = &(atual->esq);
            else if (atual->nInfo == 1 || valor.codigo < atual->info2.codigo)
                prox = &(atual->cen);
            else
                prox = &(atual->dir);
            
            int suc_rec = insere_rec_curso(prox, valor, sobe, maior);
            if (*maior != NULL) {
                Curso carga_horaria = *sobe;
                Arv23_Curso *nf = *maior;
                *maior = NULL;
                if (atual->nInfo == 1) {
                    adiciona_curso(raiz, carga_horaria, nf);
                    sucesso = 1;
                }
                else {
                    *maior = quebra_curso(raiz, carga_horaria, sobe, nf);
                    sucesso = (*maior != NULL);
                }
            } else
                sucesso = suc_rec;
        }
    }
    return sucesso;
}

// Funcao para incluir um curso no sistema
int insere_23_curso(Arv23_Curso **raiz, Curso valor) {
    int sucesso = 0;
    Curso sobe;
    Arv23_Curso *maior = NULL;
    if (raiz != NULL) {
        sucesso = insere_rec_curso(raiz, valor, &sobe, &maior);
        if (maior != NULL) {
            Arv23_Curso *nova = cria_no_curso(sobe, *raiz, maior);
            if (nova)
                *raiz = nova;
            else
                sucesso = 0;
        }
    }
    return sucesso;
}

// Retorna o unico filho remanescente de um no deficiente de curso.
// Prioriza o filho esquerdo; se nulo, retorna o filho central.
Arv23_Curso *pega_filho_curso(Arv23_Curso *no) {
    Arv23_Curso *filho = NULL;

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
int redistribuir_com_irmao_esquerdo_curso(Arv23_Curso **ponteiro_filho,
                                           Arv23_Curso *pai,
                                           Arv23_Curso *irmao_esq,
                                           int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Curso *filho = *ponteiro_filho;

    Curso chave_pai_desce;

    // Guarda o filho mais a direita do irmao, que sera transferido para o filho
    Arv23_Curso *filho_transferido    = irmao_esq->dir;

    // Guarda o unico filho existente do no deficiente
    Arv23_Curso *filho_original_unico = pega_filho_curso(filho);

    // Determina qual chave do pai desce e qual chave do irmao sobe,
    // de acordo com a posicao do filho deficiente em relacao ao pai
    if (pos_filho == 1) {
        // Filho e o do meio: a chave da esquerda do pai desce
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_esq->info2;
    } else {
        // Filho e o da direita: a chave da direita do pai desce
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_esq->info2;
    }

    // Monta o filho deficiente com a chave que desceu do pai,
    // ajustando seus ponteiros para refletir a nova distribuicao
    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_transferido;
    filho->cen = filho_original_unico;
    filho->dir = NULL;

    // Remove a chave e o filho transferido do irmao esquerdo,
    // que agora passa a ter apenas uma chave
    irmao_esq->nInfo = 1;
    irmao_esq->dir = NULL;

    sucesso = 1;
    return sucesso;
}


// Redistribui dados entre um filho deficiente e seu irmao direito,
// fazendo uma chave do pai descer para o filho e uma chave do irmao
// direito subir para o pai, reequilibrando a arvore 2-3.
int redistribuir_com_irmao_direito_curso(Arv23_Curso **ponteiro_filho,
                                          Arv23_Curso *pai,
                                          Arv23_Curso *irmao_dir,
                                          int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Curso *filho = *ponteiro_filho;

    Curso chave_pai_desce;

    // Guarda o filho mais a esquerda do irmao, que sera transferido para o filho
    Arv23_Curso *filho_transferido = irmao_dir->esq;

    // Guarda o unico filho existente do no deficiente
    Arv23_Curso *filho_original_unico = pega_filho_curso(filho);

    // Determina qual chave do pai desce e qual chave do irmao sobe,
    // de acordo com a posicao do filho deficiente em relacao ao pai
    if (pos_filho == 0) {
        // Filho e o da esquerda: a chave da esquerda do pai desce
        chave_pai_desce = pai->info1;
        pai->info1 = irmao_dir->info1;
    } else {
        // Filho e o do meio: a chave da direita do pai desce
        chave_pai_desce = pai->info2;
        pai->info2 = irmao_dir->info1;
    }

    // Monta o filho deficiente com a chave que desceu do pai,
    // ajustando seus ponteiros para refletir a nova distribuicao
    filho->info1 = chave_pai_desce;
    filho->nInfo = 1;
    filho->esq = filho_original_unico;
    filho->cen = filho_transferido;
    filho->dir = NULL;

    // Compacta o irmao direito: promove sua segunda chave para a primeira
    // posicao e ajusta os ponteiros, removendo o filho transferido
    irmao_dir->info1 = irmao_dir->info2;
    irmao_dir->nInfo = 1;
    irmao_dir->esq = irmao_dir->cen;
    irmao_dir->cen = irmao_dir->dir;
    irmao_dir->dir = NULL;

    sucesso = 1;
    return sucesso;
}


// Funde um filho deficiente com seu irmao esquerdo, fazendo uma chave
// do pai descer para o no fundido e liberando o filho deficiente.
// Retorna 0 se o pai entrou em underflow ou 1 se o pai permanece valido.
int fundir_com_irmao_esquerdo_curso(Arv23_Curso **ponteiro_filho,
                                     Arv23_Curso *pai,
                                     Arv23_Curso *irmao_esq,
                                     int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Curso *filho = *ponteiro_filho;

    Curso chave_pai_desce;

    // Guarda o unico filho remanescente do no deficiente
    Arv23_Curso *filho_remanescente = pega_filho_curso(filho);

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
        sucesso = 1;
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
    // Filho removido ou pai vazio: anula sempre o ponteiro direito
    pai->dir = NULL;

    // Libera o no deficiente que foi absorvido pelo irmao
    free(filho);

    return sucesso;
}


// Funde um filho deficiente com seu irmao direito, fazendo uma chave
// do pai descer para o no fundido e liberando o filho deficiente.
// Retorna 0 se o pai entrou em underflow ou 1 se o pai permanece valido.
int fundir_com_irmao_direito_curso(Arv23_Curso **ponteiro_filho,
                                    Arv23_Curso *pai,
                                    Arv23_Curso *irmao_dir,
                                    int pos_filho) {
    int sucesso = 0;

    // Acessa o filho deficiente via ponteiro duplo
    Arv23_Curso *filho = *ponteiro_filho;

    Curso chave_pai_desce;

    // Guarda o unico filho remanescente do no deficiente
    Arv23_Curso *filho_remanescente = pega_filho_curso(filho);

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
int tratar_underflow_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai) {
    int sucesso = 1;

    Arv23_Curso *filho = *ponteiro_filho;

    if (filho != NULL && filho->nInfo == 0 && pai == NULL) {
        // Filho vazio sem pai: underflow na raiz, nao ha como resolver
        sucesso = 0;
    } else if (filho != NULL && filho->nInfo == 0) {
        // Filho esta em underflow: identifica posicao e irmaos disponiveis
        Arv23_Curso *irmao_esq = NULL;
        Arv23_Curso *irmao_dir = NULL;
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
            sucesso = redistribuir_com_irmao_direito_curso(ponteiro_filho, pai, irmao_dir, pos_filho);
        } else if (irmao_esq != NULL && irmao_esq->nInfo == 2) {
            sucesso = redistribuir_com_irmao_esquerdo_curso(ponteiro_filho, pai, irmao_esq, pos_filho);
        } else if (irmao_dir != NULL && irmao_dir->nInfo == 1) {
            sucesso = fundir_com_irmao_direito_curso(ponteiro_filho, pai, irmao_dir, pos_filho);
        } else if (irmao_esq != NULL && irmao_esq->nInfo == 1) {
            sucesso = fundir_com_irmao_esquerdo_curso(ponteiro_filho, pai, irmao_esq, pos_filho);
        } else {
            // Nenhum irmao disponivel para resolver o underflow
            sucesso = -1;
        }
    }
    // Se filho e NULL ou nInfo > 0, nao ha underflow: sucesso permanece 1

    return sucesso;
}


// Percorre recursivamente a arvore para localizar e remover o curso
// com o codigo informado. Retorna 1 se removeu sem problemas, 0 se o no
// ficou vazio (underflow), -1 se nao encontrou e -2 se houve outro erro.
int remover_recursivo_curso(Arv23_Curso **ponteiro_no_atual, int codigo) {
    int sucesso = -1;

    Arv23_Curso *atual = *ponteiro_no_atual;

    if (atual == NULL) {
        // Codigo nao existe na arvore
        sucesso = -1;
    } else {
        Arv23_Curso **prox_ptr = NULL;
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
            if (eh_folha_curso(atual)) {
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
                Arv23_Curso  *sucessor = NULL;
                Arv23_Curso **ptr_sub  = NULL;

                // Localiza o sucessor na subarvore correspondente a chave removida
                if (indice == 0) {
                    sucessor = buscar_menor_curso(atual->cen);
                    ptr_sub  = &(atual->cen);
                } else {
                    sucessor = buscar_menor_curso(atual->dir);
                    ptr_sub  = &(atual->dir);
                }

                if (sucessor == NULL) {
                    // Nao encontrou sucessor, situacao inesperada
                    sucesso = -2;
                } else {
                    // Copia o valor do sucessor para o lugar da chave removida
                    Curso valor_suc = sucessor->info1;

                    if (indice == 0)
                        atual->info1 = valor_suc;
                    else
                        atual->info2 = valor_suc;

                    // Remove o sucessor recursivamente na subarvore
                    int stat_suc = remover_recursivo_curso(ptr_sub, valor_suc.codigo);

                    if (stat_suc == 0) {
                        // Subarvore entrou em underflow: trata antes de retornar
                        sucesso = tratar_underflow_curso(ptr_sub, atual);
                    } else {
                        sucesso = stat_suc;
                    }
                }
            }
        } else {
            // Codigo nao esta no no atual: continua descendo na subarvore correta
            int stat_rec = remover_recursivo_curso(prox_ptr, codigo);

            if (stat_rec == 0) {
                // Subarvore entrou em underflow: trata antes de retornar
                sucesso = tratar_underflow_curso(prox_ptr, atual);
            } else {
                sucesso = stat_rec;
            }
        }
    }

    return sucesso;
}


// Realiza a remocao completa de um curso pela raiz da arvore.
// Ajusta a raiz caso ela fique vazia apos a remocao.
// Retorna 1 se removeu com sucesso, 0 ou negativo em caso de erro.
int remover_23_curso(Arv23_Curso **raiz, int codigo) {
    int sucesso = 0;

    if (raiz == NULL || *raiz == NULL) {
        // Arvore vazia: nada a remover
        sucesso = -1;
    } else {
        sucesso = remover_recursivo_curso(raiz, codigo);

        // Se a raiz ficou sem chaves apos a remocao, promove o filho como nova raiz
        if (*raiz != NULL && (*raiz)->nInfo == 0) {
            Arv23_Curso *antiga = *raiz;

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

// Funcao para percorrer a estrutura exibindo todos os cursos ordenadamente
void imprime_23_em_ordem_curso(Arv23_Curso *raiz) {
    if (raiz != NULL) {
        imprime_23_em_ordem_curso(raiz->esq);
        printf("Curso [%d]: %s (Blocos: %d | Semanas: %d)\n", raiz->info1.codigo, raiz->info1.nome, raiz->info1.qtd_blocos, raiz->info1.semanas);
        imprime_23_em_ordem_curso(raiz->cen);
        if (raiz->nInfo == 2) {
            printf("Curso [%d]: %s (Blocos: %d | Semanas: %d)\n", raiz->info2.codigo, raiz->info2.nome, raiz->info2.qtd_blocos, raiz->info2.semanas);
            imprime_23_em_ordem_curso(raiz->dir);
        }
    }
}

void imprime_cursos_blocos(Arv23_Curso *raiz, int blocos) {
    if (raiz != NULL) {
        imprime_cursos_blocos(raiz->esq, blocos);
        if (raiz->info1.qtd_blocos == blocos) 
            printf("Curso [%d]: %s\n", raiz->info1.codigo, raiz->info1.nome);
        imprime_cursos_blocos(raiz->cen, blocos);
        if (raiz->nInfo == 2) {
            if (raiz->info2.qtd_blocos == blocos) 
                printf("Curso [%d]: %s\n", raiz->info2.codigo, raiz->info2.nome);
            imprime_cursos_blocos(raiz->dir, blocos);
        }
    }
}

// Libera a memória interna de um único nó de curso (incluindo suas disciplinas) e aponta para NULL
void libera_no_curso(Arv23_Curso **raiz) {
    if (raiz && *raiz != NULL) {
        // Todo nó válido possui pelo menos a info1. Libera suas disciplinas:
        libera_arvore_disciplina(&(*raiz)->info1.arv_disciplinas);

        // Se o nó possuir duas informações (nInfo == 2), libera também as disciplinas do segundo curso
        if ((*raiz)->nInfo == 2) {
        // ATENÇÃO: o nó de disciplina está sendo liberado dentro dessa função lá no arquivo disciplina!
            libera_arvore_disciplina(&(*raiz)->info2.arv_disciplinas);
        }

        // Libera o nó da árvore de cursos propriamente dito e anula o ponteiro
        free(*raiz);
        *raiz = NULL;
    }
}

// Libera recursivamente todos os nós da árvore 2-3 de cursos e todas as suas disciplinas vinculadas
void libera_arvore_curso(Arv23_Curso **raiz) {
    if (raiz && *raiz != NULL) {
        // Percorre e libera as três subárvores da árvore 2-3 de cursos
        libera_arvore_curso(&(*raiz)->esq);
        libera_arvore_curso(&(*raiz)->cen);
        libera_arvore_curso(&(*raiz)->dir);

        // Libera o nó de curso atual (o que automaticamente limpará as disciplinas internas dele)
        libera_no_curso(raiz);
    }
}