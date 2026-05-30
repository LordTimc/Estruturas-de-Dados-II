#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/curso.h"
#include "../AVP_H/disciplinas.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"
#include "../AVP_H/suporteAVP.h"


Curso *aloca_curso(int cod, char *nome, int qtd_blocos, int semanas){
    Curso *curso = (Curso *)malloc(sizeof(Curso));

    if (curso != NULL){
        curso->cod_curso = cod;
        strcpy(curso->nome, nome);

        curso->quantidade_blocos = qtd_blocos;
        curso->semanas_por_disciplina = semanas;

        curso->raiz_disciplinas = NULL;

        curso->cor = RED;

        curso->esq = NULL;
        curso->dir = NULL;
        curso->pai = NULL;
    }

    return curso;
}

Curso *cadastra_curso() {
    Curso *novo = NULL;
    char *nome = NULL;
    int codigo = 0, blocos, semanas;
    int cadastrou = 0;

    printf("Digite o codigo do curso: ");
    codigo = num_inteiro();

    if (codigo) {
        printf("Digite o nome do curso: ");
        nome = leitura_de_string();

        if (nome != NULL) {
            printf("Digite a quantidade de blocos: ");
            blocos = num_inteiro();

            if (blocos) {
                printf("Digite semanas por disciplina: ");
                semanas = num_inteiro();

                if (semanas)
                    cadastrou = 1;
            }
        }
    }
    if (cadastrou) {
        novo = aloca_curso(codigo, nome, blocos, semanas);
    } else {
        if (nome != NULL)
            free(nome);
    }

    return novo;
}

int insere_no_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = 0;

    if (*raiz == NULL){
        *raiz = novo_curso;
        inseriu = 1;
    }
    else if (novo_curso->cod_curso < (*raiz)->cod_curso)
        inseriu = insere_no_curso(&((*raiz)->esq), novo_curso);
    else if (novo_curso->cod_curso > (*raiz)->cod_curso)
        inseriu = insere_no_curso(&((*raiz)->dir), novo_curso);

    if (inseriu)
        balancea_VP_curso(raiz);

    return inseriu;
}

int insere_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = insere_no_curso(raiz, novo_curso);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}


// Libera a memoria de um unico no de curso e aponta para NULL
void libera_no_curso(Curso **raiz){
    // Libera o no e anula o ponteiro
    free(*raiz);
    *raiz = NULL;
}

// Libera recursivamente todos os nos da arvore de cursos e suas disciplinas
void libera_arvore_curso(Curso **raiz){
    if (*raiz != NULL){
        // Percorre e libera a subarvore esquerda
        libera_arvore_curso(&(*raiz)->esq);

        // Percorre e libera a subarvore direita
        libera_arvore_curso(&(*raiz)->dir);

        // Libera a arvore de disciplinas vinculada ao curso atual
        libera_arvore_disciplina(&(*raiz)->raiz_disciplinas);

        // Libera o no atual
        libera_no_curso(raiz);
    }
}

// Funcao auxiliar para encontrar o no com o menor codigo em uma subarvore
// Percorre sempre para a esquerda até encontrar o menor elemento
// Retorna o ponteiro para o menor curso
Curso* encontra_menor_curso(Curso *no) {
    Curso *menor = no;
    
    if (menor != NULL) {
        while (menor->esq != NULL) {
            menor = menor->esq;
        }
    }
    
    return menor;
}

// Funcao que substitui as informacoes do no que o usuario quer apagar pelas informacoes do sucessor em-ordem (o menor no da subarvore direita) e depois apaga esse sucessor la na base da arvore, onde eh estruturalmente muito mais simples.
void substitui_informacoes_curso(Curso *no_atual, Curso *sucessor){
    if (no_atual != NULL && sucessor != NULL){

        // 1. Copia o nome do sucessor para o nó atual
        strcpy(no_atual->nome, sucessor->nome);

        // 2. Copia as informacoes numericas
        no_atual->cod_curso = sucessor->cod_curso;
        no_atual->quantidade_blocos = sucessor->quantidade_blocos;
        no_atual->semanas_por_disciplina = sucessor->semanas_por_disciplina;

        // 3. Copia a arvore de disciplinas (ponteiro)
        no_atual->raiz_disciplinas = sucessor->raiz_disciplinas;
    }

// NAO se copia os ponteiros (esq, dir, pai) e NEM a cor,
// pois 'no_atual' precisa manter a sua posicao fisica e a sua cor 
// na arvore para nao quebrar a estrutura e as regras de balancear.
}

// Função para mover um nó vermelho para a esquerda durante a remoção
void move2_esquerda_curso(Curso **raiz){
    troca_cor_curso(*raiz);

    if ((*raiz)->dir != NULL && cor_curso((*raiz)->dir->esq) == RED){
        rotacao_dir_curso(&((*raiz)->dir));
        rotacao_esq_curso(raiz);
        troca_cor_curso(*raiz);
    }
}

// Funcao para mover um no vermelho para a direita durante a remocao
void move2_direita_curso(Curso **raiz){
    troca_cor_curso(*raiz);

    if ((*raiz)->esq != NULL && cor_curso((*raiz)->esq->esq) == RED){
        rotacao_dir_curso(raiz);
        troca_cor_curso(*raiz);
    }
}

// --- FUNCAO AUXILIAR DE CONTAGEM  ---
int conta_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total = 0;

    if (raiz != NULL) {
        int atual = 0;
        
        // Verifica se o aluno atual pertence ao curso buscado
        if (raiz->codigo_Curso == cod_curso) {
            atual = 1;
        }
        
        // Soma o aluno atual com os resultados das subarvores esquerda e direita
        total = atual + 
                conta_alunos_por_curso(raiz->esq, cod_curso) + 
                conta_alunos_por_curso(raiz->dir, cod_curso);
    }

    return total; 
}

// --- FUNcaO PRINCIPAL PARA MOSTRAR O RESULTADO ---
void mostra_qtd_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total_alunos = conta_alunos_por_curso(raiz, cod_curso);

    if (total_alunos > 0) {
        printf("O curso com codigo %d possui %d aluno(s) matriculado(s).\n", cod_curso, total_alunos);
    } else {
        printf("Nenhum aluno encontrado para o curso com codigo %d.\n", cod_curso);
    }
}

// --- FUNCAO PARA IMPRIMIR OS CURSOS EM ORDEM CRESCENTE ---
void imprime_cursos_crescente(Curso *raiz) {
    
    if (raiz != NULL) {
        // 1. Visita a subarvore esquerda 
        imprime_cursos_crescente(raiz->esq);
        
        // 2. Visita a raiz atual 
        printf("Codigo: %-5d | Nome: %-30s | Blocos: %d\n", 
               raiz->cod_curso, 
               raiz->nome, 
               raiz->quantidade_blocos);
        
        // 3. Visita a subarvore direita 
        imprime_cursos_crescente(raiz->dir);
    }
}

void imprime_curso_por_codigo(Curso *raiz, int cod_curso) {
    Curso *atual = raiz;
    int encontrado = 0;

    // Busca controlada por ponteiro e flag 
    while (atual != NULL && !encontrado) {
        if (atual->cod_curso == cod_curso) {
            printf("\n   CURSO ENCONTRADO   \n");
            printf("Codigo do Curso: %d\n", atual->cod_curso);
            printf("Nome do Curso: %s\n", atual->nome);
            printf("Quantidade de Blocos: %d\n", atual->quantidade_blocos);
            printf("Semanas por Disciplina: %d\n", atual->semanas_por_disciplina);
            printf("==================================================\n");
            encontrado = 1; 
        } else if (cod_curso < atual->cod_curso) {
            atual = atual->esq; // Vai para a esquerda se o codigo for menor
        } else {
            atual = atual->dir; // Vai para a direita se o codigo for maior
        }
    }

    // Se varreu a arvore e nao achou
    if (!encontrado) {
        printf("Aviso: Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// --- FUNCAO AUXILIAR DE CONTAGEM E IMPRESSAO ---
int busca_imprime_por_blocos(Curso *raiz, int qtd_blocos) {
    int total_encontrados = 0;

    if (raiz != NULL) {
        int atual = 0;

        // Verifica se o no atual atende ao criterio informado pelo usuário
        if (raiz->quantidade_blocos == qtd_blocos) {
            printf("Codigo: %-5d | Nome: %-30s | Blocos: %d\n", 
                   raiz->cod_curso, raiz->nome, raiz->quantidade_blocos);
            atual = 1;
        }

        // Acumula o atual com o resultado das subarvores esquerda e direita
        total_encontrados = atual + 
                            busca_imprime_por_blocos(raiz->esq, qtd_blocos) + 
                            busca_imprime_por_blocos(raiz->dir, qtd_blocos);
    }

    return total_encontrados;
}

// --- FUNCAO PRINCIPAL CHAMADA PELO USUARIO ---
void lista_cursos_por_qtd_blocos(Curso *raiz, int qtd_blocos) {
    printf("\n--- Buscando cursos com %d blocos ---\n", qtd_blocos);
    
    int total = busca_imprime_por_blocos(raiz, qtd_blocos);

    if (total == 0) {
        printf("Nenhum curso foi encontrado com a quantidade de %d blocos.\n", qtd_blocos);
    } else {
        printf("Total de cursos listados: %d\n", total);
    }
}

// =========================
// BUSCA
// =========================

// Funcao auxiliar para buscar um curso pelo codigo e verifica se ele existe
// Essa funcao será usado na funcao imprime_disciplinas_ordem_crescente junto com a funcao percorre_disciplinas_em_ordem para conseguir 
Curso* busca_curso(Curso *raiz, int cod_curso) {
    Curso *atual = raiz;
    Curso *resultado = NULL;

    // enquanto houver nos na arvore e o resultado nao for encontrado
    while (atual != NULL && resultado == NULL) {
        
        // Verifica se o codigo do no atual eh exatamente o que o usuario busca
        if (atual->cod_curso == cod_curso) {
            resultado = atual; // Guarda o ponteiro do curso e quebra a condicao do while
        } 
        // Se o codigo for menor que o atual, vai para a esquerd
        else if (cod_curso < atual->cod_curso) {
            atual = atual->esq;
        } 
        // Se o codigo for maior que o atual, vai para direita
        else {
            atual = atual->dir;
        }
    }
    return resultado;
}

// 1. Imprimir a arvore de disciplinas em ordem crescente pelo codigo das disciplinas dado o codigo do curso
void imprime_disciplinas_ordem_crescente(Curso *raiz_cursos, int cod_curso) {
    Curso *curso_encontrado = busca_curso(raiz_cursos, cod_curso);

    if (curso_encontrado != NULL) {
        printf("\n--- Disciplinas do Curso: %s ---\n", curso_encontrado->nome);
        percorre_disciplinas_em_ordem(curso_encontrado->raiz_disciplinas);
    } else {
        printf("Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// 2. Imprimir os dados de uma disciplina dado o codigo dela e do curso ao qual ela pertence
void imprime_dados_disciplina(Curso *raiz_cursos, int cod_curso, int cod_disciplina) {
    Curso *curso_encontrado = busca_curso(raiz_cursos, cod_curso);

    if (curso_encontrado != NULL) {
        Disciplina *atual = curso_encontrado->raiz_disciplinas;
        Disciplina *disciplina_encontrada = NULL;

        while (atual != NULL && disciplina_encontrada == NULL) {
            if (atual->cod_disciplina == cod_disciplina) {
                disciplina_encontrada = atual;
            } else if (cod_disciplina < atual->cod_disciplina) {
                atual = atual->esq;
            } else {
                atual = atual->dir;
            }
        }

        if (disciplina_encontrada != NULL) {
            printf("\n--- Dados da Disciplina ---\n");
            printf("Codigo: %d\n", disciplina_encontrada->cod_disciplina);
            printf("Nome: %s\n", disciplina_encontrada->nome);
            printf("Bloco: %d\n", disciplina_encontrada->bloco);
            printf("Carga Horaria: %d\n", disciplina_encontrada->carga_horaria);
        } else {
            printf("Disciplina com o codigo %d nao existe neste curso.\n", cod_disciplina);
        }
    } else {
        printf("Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// 3. Imprimir as disciplinas de um determinado bloco de um curso, dado o bloco e o codigo do curso
void imprime_disciplinas_por_bloco(Curso *raiz_cursos, int cod_curso, int bloco){
    Curso *curso_encontrado = busca_curso(raiz_cursos, cod_curso);

    if (curso_encontrado != NULL) {
        printf("\n--- Disciplinas do Bloco %d do Curso: %s ---\n", bloco, curso_encontrado->nome);
        percorre_por_bloco(curso_encontrado->raiz_disciplinas, bloco);
    } else {
        printf("Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// 4. Imprimir todas as disciplinas de um determinado curso com a mesma carga horaria
void imprime_disciplinas_por_carga_horaria(Curso *raiz_cursos, int cod_curso, int carga_horaria){
    Curso *curso_encontrado = busca_curso(raiz_cursos, cod_curso);

    if (curso_encontrado != NULL) {
        printf("\n--- Disciplinas com %d horas do Curso: %s ---\n", carga_horaria, curso_encontrado->nome);
        percorre_por_carga_horaria(curso_encontrado->raiz_disciplinas, carga_horaria);
    } else {
        printf("Curso com o codigo %d nao foi encontrado.\n", cod_curso);
    }
}

// REMOCAO
// Funcao que remove o nó com o menor cod_curso da árvore.
void remove_menor_curso(Curso **raiz){
    
    // verifica se a arvore nao esta vazia
    if (*raiz != NULL){

        // caso base: encontrou o menor (nao tem filho a esquerda)
        if ((*raiz)->esq == NULL){
            libera_no_curso(raiz);     
        }
        else{
            // garante que existe um no vermelho no caminho a esquerda
            if (cor_curso((*raiz)->esq) == BLACK &&
                cor_curso((*raiz)->esq->esq) == BLACK){
                move2_esquerda_curso(raiz);
            }
            remove_menor_curso(&((*raiz)->esq));
            balancea_VP_curso(raiz);
        }
    }
}

int remove_curso(Curso **raiz, int cod_curso) {
    int removeu = 1;

    if ((*raiz) != NULL) {
        
        // Se encontrou logo de início e tem disciplinas, aborta a remoção
        if (cod_curso == (*raiz)->cod_curso && (*raiz)->raiz_disciplinas != NULL) {
            removeu = 0; 
        }
        // Caminha para a subárvore esquerda
        else if (cod_curso < (*raiz)->cod_curso) {
            if ((*raiz)->esq != NULL) {
                if (cor_curso((*raiz)->esq) == BLACK && cor_curso((*raiz)->esq->esq) == BLACK) {
                    move2_esquerda_curso(raiz);
                }
            }
            removeu = remove_curso(&((*raiz)->esq), cod_curso);
        } 
        // Caminha para a direita ou encontrou o nó correspondente
        else {
            // Garante a inclinação correta da árvore para a esquerda
            if (cor_curso((*raiz)->esq) == RED) {
                rotacao_dir_curso(raiz);
            }

            // Caso a rotação tenha trazido o nó alvo para a raiz local
            if (cod_curso == (*raiz)->cod_curso && (*raiz)->raiz_disciplinas != NULL) {
                removeu = 0;
            }
            // CASO 1: Encontrou o nó, ele NÃO tem disciplinas e é uma folha (sem filho à direita)
            else if (cod_curso == (*raiz)->cod_curso && (*raiz)->dir == NULL) {
                free(*raiz);
                *raiz = NULL;
            } 
            // CASO 2: O nó possui filhos à direita ou o alvo está mais abaixo
            else {
                if ((*raiz)->dir != NULL) {
                    if (cor_curso((*raiz)->dir) == BLACK && cor_curso((*raiz)->dir->esq) == BLACK) {
                        move2_direita_curso(raiz);
                    }
                }

                // Encontrou o nó a ser removido (garantido como nó interno)
                if (cod_curso == (*raiz)->cod_curso) {
                    // Verifica novamente se o nó atual possui disciplinas após o movimento da árvore
                    if ((*raiz)->raiz_disciplinas != NULL) {
                        removeu = 0;
                    } else {
                        // Busca o sucessor em-ordem (menor da subárvore direita)
                        Curso *menor = encontra_menor_curso((*raiz)->dir);
                        
                        // O nó atual adota a identidade do sucessor.
                        // A função substitui_informacoes deve copiar os dados E também o ponteiro raiz_disciplinas do sucessor!
                        substitui_informacoes_curso(*raiz, menor);
                        
                        // Elimina o nó menor físico duplicado que ficou na base da árvore
                        remove_menor_curso(&((*raiz)->dir));
                    }
                } 
                // Continua a busca descendo pela subárvore direita
                else {
                    removeu = remove_curso(&((*raiz)->dir), cod_curso);
                }
            }
        }

        //Mesmo que a remoção tenha sido negada (removeu = 0),
        // se a árvore sofreu rotações temporárias na descida, precisamos balancear na subida!
        if (*raiz != NULL) {
            balancea_VP_curso(raiz);
        }
        
    } else {
        removeu = 0; // Curso não encontrado
    }
    return removeu;
}

// Função principal para remoção de curso - garante a integridade da árvore
int remove_curso_arvore(Curso **raiz, int cod_curso) {
    // Verifica se o curso sequer existe na árvore antes de tentar mexer na estrutura
    Curso *encontrado = busca_curso(*raiz, cod_curso);

    int removeu = 0;
    if (encontrado != NULL) {  // Comparação explícita com NULL
        removeu = remove_curso(raiz, cod_curso);
    }

    if (*raiz != NULL) {
        //Garante que a raiz permaneça preta após as modificações
        (*raiz)->cor = BLACK;
    }
    return removeu; // Retorna 1 se removeu com sucesso, ou 0 caso contrário
}