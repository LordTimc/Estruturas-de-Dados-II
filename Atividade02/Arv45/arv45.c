#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BLOCO 1048576 // 1 Mbyte em bytes

// Estrutura do Segmento de Memoria
typedef struct {
    char status;     // 'O' para Ocupado, 'L' para Livre
    int blk_ini;     // Numero do bloco inicial
    int blk_fim;     // Numero do bloco final
    long end_ini;    // Endereco inicial
    long end_fim;    // Endereco final
} MemBlock;

MemBlock MEMBLOCK_NULL = {'\0', 0, 0, 0, 0};

// Estrutura do No da Arvore 4-5 adaptada
typedef struct Arv45 {
    MemBlock info1, info2, info3, info4;
    int nInfo; 
    struct Arv45 *esq, *f_cen1, *f_cen2, *f_cen3, *dir;
} Arv45;

// ================ PROTOTYPES ==================
Arv45 *cria_no_45(MemBlock info, Arv45 *F_esq, Arv45 *F_f_cen1);
int eh_folha_45(Arv45 *no);
void adiciona_chave_em_no_45(Arv45 *no_atual, MemBlock info_nova, Arv45 *sub_arv_dir);
Arv45 *quebra_no_45(Arv45 **no_original_ptr, MemBlock N, Arv45 *Nc, MemBlock *chave_promovida);
int insere_45_recursivo(Arv45 **raiz, MemBlock valor, MemBlock *sobe, Arv45 **maiorNo);
int insere_45(Arv45 **raiz, MemBlock valor);
void libera_arvore_45(Arv45 **raiz);
void imprime_arvore_visual(Arv45 *raiz, char *prefixo, int eh_ultimo, int eh_raiz);

// ================ FUNCOES BASE ARVORE ==================
Arv45 *cria_no_45(MemBlock info, Arv45 *F_esq, Arv45 *F_f_cen1) {
    Arv45 *no = (Arv45 *)malloc(sizeof(Arv45));
    if (no != NULL) {
        no->info1 = info;
        no->nInfo = 1;
        no->esq = F_esq;
        no->f_cen1 = F_f_cen1;
        no->f_cen2 = NULL;
        no->f_cen3 = NULL;
        no->dir = NULL;
        no->info2 = MEMBLOCK_NULL;
        no->info3 = MEMBLOCK_NULL;
        no->info4 = MEMBLOCK_NULL;
    }
    return no;
}

int eh_folha_45(Arv45 *no) {
    if (no != NULL && no->esq == NULL && no->f_cen1 == NULL && no->f_cen2 == NULL && no->f_cen3 == NULL && no->dir == NULL)
        return 1;
    return 0;
}

void adiciona_chave_em_no_45(Arv45 *no_atual, MemBlock info_nova, Arv45 *sub_arv_dir) {
    if (no_atual == NULL || no_atual->nInfo >= 4) return;
    
    int j;
    int pos = 0;

    if (no_atual->nInfo >= 1 && info_nova.blk_ini > no_atual->info1.blk_ini) pos = 1;
    if (no_atual->nInfo >= 2 && info_nova.blk_ini > no_atual->info2.blk_ini) pos = 2;
    if (no_atual->nInfo >= 3 && info_nova.blk_ini > no_atual->info3.blk_ini) pos = 3;

    for (j = no_atual->nInfo - 1; j >= pos; j--) {
        if (j == 2) no_atual->info4 = no_atual->info3;
        else if (j == 1) no_atual->info3 = no_atual->info2;
        else if (j == 0) no_atual->info2 = no_atual->info1;
    }

    for (j = no_atual->nInfo; j >= pos + 1; j--) {
        if (j == 3) no_atual->dir = no_atual->f_cen3;
        else if (j == 2) no_atual->f_cen3 = no_atual->f_cen2;
        else if (j == 1) no_atual->f_cen2 = no_atual->f_cen1;
    }

    if (pos == 0) { no_atual->info1 = info_nova; no_atual->f_cen1 = sub_arv_dir; }
    else if (pos == 1) { no_atual->info2 = info_nova; no_atual->f_cen2 = sub_arv_dir; }
    else if (pos == 2) { no_atual->info3 = info_nova; no_atual->f_cen3 = sub_arv_dir; }
    else if (pos == 3) { no_atual->info4 = info_nova; no_atual->dir = sub_arv_dir; }

    no_atual->nInfo++;
}

Arv45 *quebra_no_45(Arv45 **no_original_ptr, MemBlock N, Arv45 *Nc, MemBlock *chave_promovida) {
    Arv45 *no_orig = *no_original_ptr;
    Arv45 *novo_no_dir = NULL;

    MemBlock i1 = no_orig->info1, i2 = no_orig->info2, i3 = no_orig->info3, i4 = no_orig->info4;
    Arv45 *c0 = no_orig->esq, *c1 = no_orig->f_cen1, *c2 = no_orig->f_cen2, *c3 = no_orig->f_cen3, *c4 = no_orig->dir;

    if (N.blk_ini < i1.blk_ini) {
        *chave_promovida = i2;
        no_orig->info1 = N; no_orig->info2 = i1; no_orig->nInfo = 2;
        no_orig->esq = c0; no_orig->f_cen1 = Nc; no_orig->f_cen2 = c1;
        novo_no_dir = cria_no_45(i3, c2, c3);
        if (novo_no_dir) { novo_no_dir->info2 = i4; novo_no_dir->f_cen2 = c4; novo_no_dir->nInfo = 2; }
    } else if (N.blk_ini < i2.blk_ini) {
        *chave_promovida = i2;
        no_orig->info1 = i1; no_orig->info2 = N; no_orig->nInfo = 2;
        no_orig->esq = c0; no_orig->f_cen1 = c1; no_orig->f_cen2 = Nc;
        novo_no_dir = cria_no_45(i3, c2, c3);
        if (novo_no_dir) { novo_no_dir->info2 = i4; novo_no_dir->f_cen2 = c4; novo_no_dir->nInfo = 2; }
    } else if (N.blk_ini < i3.blk_ini) {
        *chave_promovida = N;
        no_orig->info1 = i1; no_orig->info2 = i2; no_orig->nInfo = 2;
        no_orig->esq = c0; no_orig->f_cen1 = c1; no_orig->f_cen2 = c2;
        novo_no_dir = cria_no_45(i3, Nc, c3);
        if (novo_no_dir) { novo_no_dir->info2 = i4; novo_no_dir->f_cen2 = c4; novo_no_dir->nInfo = 2; }
    } else if (N.blk_ini < i4.blk_ini) {
        *chave_promovida = i3;
        no_orig->info1 = i1; no_orig->info2 = i2; no_orig->nInfo = 2;
        no_orig->esq = c0; no_orig->f_cen1 = c1; no_orig->f_cen2 = c2;
        novo_no_dir = cria_no_45(N, c3, Nc);
        if (novo_no_dir) { novo_no_dir->info2 = i4; novo_no_dir->f_cen2 = c4; novo_no_dir->nInfo = 2; }
    } else {
        *chave_promovida = i3;
        no_orig->info1 = i1; no_orig->info2 = i2; no_orig->nInfo = 2;
        no_orig->esq = c0; no_orig->f_cen1 = c1; no_orig->f_cen2 = c2;
        novo_no_dir = cria_no_45(i4, c3, c4);
        if (novo_no_dir) { novo_no_dir->info2 = N; novo_no_dir->f_cen2 = Nc; novo_no_dir->nInfo = 2; }
    }

    no_orig->info3 = MEMBLOCK_NULL; no_orig->info4 = MEMBLOCK_NULL;
    no_orig->f_cen3 = NULL; no_orig->dir = NULL;
    if (novo_no_dir != NULL) { novo_no_dir->f_cen3 = NULL; novo_no_dir->dir = NULL; }
    
    return novo_no_dir;
}

int insere_45_recursivo(Arv45 **raiz_ptr, MemBlock valor, MemBlock *chave_promovida, Arv45 **novo_irmao_dir) {
    int status_operacao = 0;
    Arv45 *no_atual = (raiz_ptr != NULL) ? *raiz_ptr : NULL;
    *chave_promovida = MEMBLOCK_NULL;
    *novo_irmao_dir = NULL;

    if (no_atual == NULL) {
        *chave_promovida = valor;
        status_operacao = 1;
    } else {
        if (eh_folha_45(no_atual)) {
            if (no_atual->nInfo < 4) {
                adiciona_chave_em_no_45(no_atual, valor, NULL);
                status_operacao = 1;
            } else {
                *novo_irmao_dir = quebra_no_45(raiz_ptr, valor, NULL, chave_promovida);
                status_operacao = 1;
            }
        } else {
            Arv45 **prox_filho = NULL;
            if (valor.blk_ini < no_atual->info1.blk_ini) prox_filho = &(no_atual->esq);
            else if (no_atual->nInfo == 1 || (no_atual->nInfo >= 2 && valor.blk_ini < no_atual->info2.blk_ini)) prox_filho = &(no_atual->f_cen1);
            else if (no_atual->nInfo == 2 || (no_atual->nInfo >= 3 && valor.blk_ini < no_atual->info3.blk_ini)) prox_filho = &(no_atual->f_cen2);
            else if (no_atual->nInfo == 3 || (no_atual->nInfo >= 4 && valor.blk_ini < no_atual->info4.blk_ini)) prox_filho = &(no_atual->f_cen3);
            else prox_filho = &(no_atual->dir);

            MemBlock chave_baixo = MEMBLOCK_NULL;
            Arv45 *filho_dir_baixo = NULL;

            if (insere_45_recursivo(prox_filho, valor, &chave_baixo, &filho_dir_baixo)) {
                if (chave_baixo.status != '\0') {
                    if (no_atual->nInfo < 4) {
                        adiciona_chave_em_no_45(no_atual, chave_baixo, filho_dir_baixo);
                        status_operacao = 1;
                    } else {
                        *novo_irmao_dir = quebra_no_45(raiz_ptr, chave_baixo, filho_dir_baixo, chave_promovida);
                        status_operacao = 1;
                    }
                } else {
                    status_operacao = 1;
                }
            }
        }
    }
    return status_operacao;
}

int insere_45(Arv45 **raiz, MemBlock valor) {
    int sucesso = 0;
    MemBlock chave_promovida = MEMBLOCK_NULL;
    Arv45 *novo_irmao = NULL;

    if (*raiz == NULL) {
        *raiz = cria_no_45(valor, NULL, NULL);
        sucesso = (*raiz != NULL);
    } else {
        if (insere_45_recursivo(raiz, valor, &chave_promovida, &novo_irmao)) {
            if (chave_promovida.status != '\0') {
                Arv45 *antiga_raiz = *raiz;
                *raiz = cria_no_45(chave_promovida, antiga_raiz, novo_irmao);
                sucesso = (*raiz != NULL);
            } else {
                sucesso = 1;
            }
        }
    }
    return sucesso;
}

void libera_arvore_45(Arv45 **raiz) {
    if (raiz != NULL && *raiz != NULL) {
        libera_arvore_45(&((*raiz)->esq));
        libera_arvore_45(&((*raiz)->f_cen1));
        libera_arvore_45(&((*raiz)->f_cen2));
        libera_arvore_45(&((*raiz)->f_cen3));
        libera_arvore_45(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
}

// ================ GERENCIADOR DE MEMORIA (ARRAY REBUILD TACTIC) ==================

// 1. Extrai a arvore em ordem logica
void extrair_em_ordem(Arv45 *raiz, MemBlock *array, int *contador) {
    if (raiz != NULL) {
        extrair_em_ordem(raiz->esq, array, contador);
        if (raiz->nInfo >= 1) array[(*contador)++] = raiz->info1;
        extrair_em_ordem(raiz->f_cen1, array, contador);
        if (raiz->nInfo >= 2) array[(*contador)++] = raiz->info2;
        extrair_em_ordem(raiz->f_cen2, array, contador);
        if (raiz->nInfo >= 3) array[(*contador)++] = raiz->info3;
        extrair_em_ordem(raiz->f_cen3, array, contador);
        if (raiz->nInfo == 4) array[(*contador)++] = raiz->info4;
        extrair_em_ordem(raiz->dir, array, contador);
    }
}

// 2. Concatena nos adjacentes que possuem o mesmo status e reconstrói a árvore
void reconstruir_e_consolidar(Arv45 **raiz, MemBlock *array, int qtd) {
    MemBlock consolidado[1000];
    int cont_cons = 0;

    if (qtd > 0) {
        consolidado[0] = array[0];
        cont_cons = 1;
        for (int i = 1; i < qtd; i++) {
            // Se o status for o mesmo e forem vizinhos (bloco fim atual + 1 == bloco ini proximo)
            if (consolidado[cont_cons - 1].status == array[i].status &&
                consolidado[cont_cons - 1].blk_fim + 1 == array[i].blk_ini) {
                // Fundir
                consolidado[cont_cons - 1].blk_fim = array[i].blk_fim;
                consolidado[cont_cons - 1].end_fim = array[i].end_fim;
            } else {
                consolidado[cont_cons++] = array[i];
            }
        }
    }

    libera_arvore_45(raiz); // Limpa arvore atual
    for (int i = 0; i < cont_cons; i++) {
        insere_45(raiz, consolidado[i]); // Recria respeitando o balanceamento natural da B-Tree
    }
}

// 3. Cadastrar Memória
void cadastrar_memoria(Arv45 **raiz, long max_end) {
    char status_atual;
    long end_ini, end_fim;

    printf("\nStatus do primeiro no (L ou O): ");
    scanf(" %c", &status_atual);
    printf("Endereco inicial do primeiro no: ");
    scanf("%ld", &end_ini);
    printf("Endereco final do primeiro no: ");
    scanf("%ld", &end_fim);

    if (end_fim > max_end) end_fim = max_end;

    MemBlock mb = {status_atual, (int)(end_ini / TAM_BLOCO), (int)(end_fim / TAM_BLOCO), end_ini, end_fim};
    insere_45(raiz, mb);

    while (end_fim < max_end) {
        status_atual = (status_atual == 'L') ? 'O' : 'L';
        end_ini = end_fim + 1;
        
        printf("\nO proximo no e '%c'. Inicia no endereco %ld.\n", status_atual, end_ini);
        printf("Informe o endereco final deste no (Ate %ld): ", max_end);
        scanf("%ld", &end_fim);

        if (end_fim >= max_end) end_fim = max_end;

        mb.status = status_atual;
        mb.blk_ini = (int)(end_ini / TAM_BLOCO);
        mb.blk_fim = (int)(end_fim / TAM_BLOCO);
        mb.end_ini = end_ini;
        mb.end_fim = end_fim;

        insere_45(raiz, mb);
    }
    printf("\n[ Cadastro Concluido com Sucesso ]\n");
}

// 4. Alocar
void alocar_memoria(Arv45 **raiz, int blocos_solicitados) {
    MemBlock array[1000];
    int cont = 0;
    extrair_em_ordem(*raiz, array, &cont);

    int alocado = 0;
    for (int i = 0; i < cont; i++) {
        if (array[i].status == 'L') {
            int blocos_disp = array[i].blk_fim - array[i].blk_ini + 1;
            
            if (blocos_disp == blocos_solicitados) {
                // Encaixe perfeito
                array[i].status = 'O';
                alocado = 1;
                printf("\nAlocacao exata no bloco %d a %d.\n", array[i].blk_ini, array[i].blk_fim);
                break;
            } else if (blocos_disp > blocos_solicitados) {
                // Quebra necessaria, o atual vira 'O', e criamos o resto 'L' à direita
                for (int j = cont; j > i; j--) {
                    array[j] = array[j - 1]; // Shift para abrir espaco
                }
                cont++;

                array[i].status = 'O';
                array[i].blk_fim = array[i].blk_ini + blocos_solicitados - 1;
                array[i].end_fim = array[i].end_ini + (blocos_solicitados * TAM_BLOCO) - 1;

                array[i + 1].status = 'L';
                array[i + 1].blk_ini = array[i].blk_fim + 1;
                array[i + 1].end_ini = array[i].end_fim + 1;

                alocado = 1;
                printf("\nAlocacao com quebra realizada no bloco %d a %d.\n", array[i].blk_ini, array[i].blk_fim);
                break;
            }
        }
    }

    if (alocado) {
        reconstruir_e_consolidar(raiz, array, cont);
    } else {
        printf("\nFalha: Nao ha espaco contiguo suficiente para %d blocos.\n", blocos_solicitados);
    }
}

// 5. Liberar
void liberar_memoria(Arv45 **raiz, int blocos_liberar) {
    MemBlock array[1000];
    int cont = 0;
    extrair_em_ordem(*raiz, array, &cont);

    int liberados_restantes = blocos_liberar;

    for (int i = 0; i < cont && liberados_restantes > 0; i++) {
        if (array[i].status == 'O') {
            int qtd_neste_bloco = array[i].blk_fim - array[i].blk_ini + 1;
            
            if (qtd_neste_bloco <= liberados_restantes) {
                // Libera o no inteiro
                array[i].status = 'L';
                liberados_restantes -= qtd_neste_bloco;
                printf("Blocos do no B%d-B%d totalmente liberados.\n", array[i].blk_ini, array[i].blk_fim);
            } else {
                // Libera apenas parte (quebra)
                for (int j = cont; j > i; j--) array[j] = array[j - 1];
                cont++;

                array[i].status = 'L';
                array[i].blk_fim = array[i].blk_ini + liberados_restantes - 1;
                array[i].end_fim = array[i].end_ini + (liberados_restantes * TAM_BLOCO) - 1;

                array[i + 1].blk_ini = array[i].blk_fim + 1;
                array[i + 1].end_ini = array[i].end_fim + 1;
                
                liberados_restantes = 0;
                printf("Quebra parcial de no feita. Liberados os blocos B%d-B%d.\n", array[i].blk_ini, array[i].blk_fim);
                break;
            }
        }
    }

    if (blocos_liberar > liberados_restantes) {
        reconstruir_e_consolidar(raiz, array, cont);
    } else {
        printf("\nNenhum bloco ocupado encontrado para liberar.\n");
    }
}

void imprime_arvore_visual(Arv45 *raiz, char *prefixo, int eh_ultimo, int eh_raiz) {
    if (raiz != NULL) {
        printf("%s", prefixo);
        if (!eh_raiz) printf("%s", eh_ultimo ? "`------ " : "+------ ");
        else printf(" Raiz--> ");

        printf("[");
        if (raiz->nInfo >= 1) printf("%c(B%d-B%d)", raiz->info1.status, raiz->info1.blk_ini, raiz->info1.blk_fim);
        if (raiz->nInfo >= 2) printf(", %c(B%d-B%d)", raiz->info2.status, raiz->info2.blk_ini, raiz->info2.blk_fim);
        if (raiz->nInfo >= 3) printf(", %c(B%d-B%d)", raiz->info3.status, raiz->info3.blk_ini, raiz->info3.blk_fim);
        if (raiz->nInfo == 4) printf(", %c(B%d-B%d)", raiz->info4.status, raiz->info4.blk_ini, raiz->info4.blk_fim);
        printf("]\n");

        char novo_prefixo[1024];
        sprintf(novo_prefixo, "%s%s", prefixo, eh_raiz ? "         " : (eh_ultimo ? "         " : "|        "));

        int num_filhos = (raiz->esq?1:0) + (raiz->f_cen1?1:0) + (raiz->f_cen2?1:0) + (raiz->f_cen3?1:0) + (raiz->dir?1:0);
        int impressos = 0;

        if (raiz->esq) { impressos++; imprime_arvore_visual(raiz->esq, novo_prefixo, impressos == num_filhos, 0); }
        if (raiz->f_cen1) { impressos++; imprime_arvore_visual(raiz->f_cen1, novo_prefixo, impressos == num_filhos, 0); }
        if (raiz->f_cen2) { impressos++; imprime_arvore_visual(raiz->f_cen2, novo_prefixo, impressos == num_filhos, 0); }
        if (raiz->f_cen3) { impressos++; imprime_arvore_visual(raiz->f_cen3, novo_prefixo, impressos == num_filhos, 0); }
        if (raiz->dir) { impressos++; imprime_arvore_visual(raiz->dir, novo_prefixo, impressos == num_filhos, 0); }
    }
}

// ================ MAIN ==================
int main() {
    Arv45 *raiz = NULL;
    long max_memoria;
    
    printf("=========================================\n");
    printf("   GERENCIADOR DE MEMORIA (ARVORE 4-5)   \n");
    printf("=========================================\n");
    printf("Informe o limite maximo de memoria (bytes): ");
    scanf("%ld", &max_memoria);

    cadastrar_memoria(&raiz, max_memoria);

    int opcao = 0;
    do {
        printf("\n=====================================\n");
        printf("Estrutura atual da memoria:\n");
        imprime_arvore_visual(raiz, "", 1, 1);
        printf("=====================================\n");
        printf("1. Alocar Blocos\n");
        printf("2. Liberar Blocos (por quantidade)\n");
        printf("3. Sair\n");
        printf("Opcao: ");
        
        if(scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        if (opcao == 1) {
            int blocos;
            printf("Quantos blocos de 1MB deseja alocar? ");
            scanf("%d", &blocos);
            alocar_memoria(&raiz, blocos);
        } else if (opcao == 2) {
            int blocos;
            printf("Quantos blocos deseja liberar? ");
            scanf("%d", &blocos);
            liberar_memoria(&raiz, blocos);
        }

    } while (opcao != 3);

    libera_arvore_45(&raiz);
    printf("\nMemoria liberada. Encerrando o SO...\n");
    return 0;
}