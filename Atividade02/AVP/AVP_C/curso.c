#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/curso.h"
#include "../AVP_H/disciplinas.h"

#include "../AVP_H/auxiliares.h"
#include "../AVP_H/structs.h"

int inserir_no_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = 0;

    if (*raiz == NULL)
    {
        *raiz = novo_curso;
        inseriu = 1;
    }
    else if (novo_curso->cod_curso < (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->esq), novo_curso);
    else if (novo_curso->cod_curso > (*raiz)->cod_curso)
        inseriu = inserir_no_curso(&((*raiz)->dir), novo_curso);

    if (inseriu)
        balancear_RB_curso(raiz);

    return inseriu;
}

int inserir_curso(Curso **raiz, Curso *novo_curso){
    int inseriu = inserir_no_curso(raiz, novo_curso);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return inseriu;
}

Curso *aloca_curso(int cod, char *nome, int qtd_blocos, int semanas){
    Curso *curso = (Curso *)malloc(sizeof(Curso));

    if (curso != NULL)
    {
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

Curso *cadastrar_curso(){
    Curso *novo = NULL;
    char *nome;
    int cod, blocos, semanas;
    int ok = 1;

    printf("Digite o codigo do curso: ");
    cod = digitar_int();

    printf("Digite o nome do curso: ");
    nome = ler_string();

    if (nome == NULL)
        ok = 0;

    if (ok){
        printf("Digite a quantidade de blocos: ");
        blocos = digitar_int();

        printf("Digite semanas por disciplina: ");
        semanas = digitar_int();
    }

    if (ok)
        novo = aloca_curso(cod, nome, blocos, semanas);
    else if (nome != NULL)
        free(nome);

    return novo;
}

void rotacao_esquerda_curso(Curso **raiz){
    Curso *aux = (*raiz)->dir;

    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacao_direita_curso(Curso **raiz){
    Curso *aux = (*raiz)->esq;

    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

int cor_aluno(Curso *curso){
    int cor;
    if (curso == NULL)
        cor = BLACK;
    else
        cor = curso->cor;
    return cor;
}

void trocar_cor_curso(Curso *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir)
        raiz->dir->cor = !(raiz->dir->cor);
}

void balancear_RB_curso(Curso **raiz){
    if (*raiz != NULL){
        if (cor_curso((*raiz)->esq) == BLACK && cor_curso((*raiz)->dir) == RED)
            rotacao_esquerda_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->esq->esq) == RED)
            rotacao_direita_curso(raiz);

        if (cor_curso((*raiz)->esq) == RED && cor_curso((*raiz)->dir) == RED)
            trocar_cor_curso(*raiz);
    }
}

// --- FUNCAO AUXILIAR DE CONTAGEM  ---
int contar_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total = 0;

    if (raiz != NULL) {
        int atual = 0;
        
        // Verifica se o aluno atual pertence ao curso buscado
        if (raiz->codigo_Curso == cod_curso) {
            atual = 1;
        }
        
        // Soma o aluno atual com os resultados das subarvores esquerda e direita
        total = atual + 
                contar_alunos_por_curso(raiz->esq, cod_curso) + 
                contar_alunos_por_curso(raiz->dir, cod_curso);
    }

    return total; 
}

// --- FUNcaO PRINCIPAL PARA MOSTRAR O RESULTADO ---
void mostrar_qtd_alunos_por_curso(Aluno *raiz, int cod_curso) {
    int total_alunos = contar_alunos_por_curso(raiz, cod_curso);

    if (total_alunos > 0) {
        printf("O curso com codigo %d possui %d aluno(s) matriculado(s).\n", cod_curso, total_alunos);
    } else {
        printf("Nenhum aluno encontrado para o curso com codigo %d.\n", cod_curso);
    }
}

// --- FUNCAO PARA IMPRIMIR OS CURSOS EM ORDEM CRESCENTE ---
void imprimir_cursos_crescente(Curso *raiz) {
    
    if (raiz != NULL) {
        // 1. Visita a subarvore esquerda 
        imprimir_cursos_crescente(raiz->esq);
        
        // 2. Visita a raiz atual 
        printf("Codigo: %-5d | Nome: %-30s | Blocos: %d\n", 
               raiz->cod_curso, 
               raiz->nome, 
               raiz->quantidade_blocos);
        
        // 3. Visita a subarvore direita 
        imprimir_cursos_crescente(raiz->dir);
    }
}

void imprimir_curso_por_codigo(Curso *raiz, int cod_curso) {
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

// Funcao auxiliar para buscar um curso pelo codigo
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

Curso* remover_curso(Curso *raiz, int cod_curso) {
    Curso *curso = NULL;
    Curso *resultado = raiz;

    // 1. Buscar curso
    curso = busca_curso(raiz, cod_curso);

    // 2. Verifica se existe
    if (curso != NULL) {

        // 3. Verifica se tem disciplinas
        if (curso->raiz_disciplinas == NULL) {

            Curso *pai = curso->pai;
            Curso *filho = NULL;

            // CASO 1: folha
            if (curso->esq == NULL && curso->dir == NULL) {

                if (pai == NULL) {
                    resultado = NULL; // era raiz
                } else {
                    if (pai->esq == curso) {
                        pai->esq = NULL;
                    } else {
                        pai->dir = NULL;
                    }
                }
            }

            // CASO 2: um filho
            else if (curso->esq == NULL || curso->dir == NULL) {

                if (curso->esq != NULL) {
                    filho = curso->esq;
                } else {
                    filho = curso->dir;
                }

                if (pai == NULL) {
                    resultado = filho;
                } else {
                    if (pai->esq == curso) {
                        pai->esq = filho;
                    } else {
                        pai->dir = filho;
                    }
                }

                filho->pai = pai;
            }

            // CASO 3: dois filhos
            else {
                Curso *sucessor = curso->dir;

                while (sucessor->esq != NULL) {
                    sucessor = sucessor->esq;
                }

                // copia dados
                curso->cod_curso = sucessor->cod_curso;
                strcpy(curso->nome, sucessor->nome);

                // remove sucessor (recursivo simplificado)
                curso->dir = remover_curso(curso->dir, sucessor->cod_curso);
            }

            free(curso);
        }
    }

    return resultado;
}