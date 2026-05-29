#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AVP_H/structs.h"
#include "../AVP_H/disciplinas.h"
#include "../AVP_H/auxiliares.h"

// Função para alocar um novo curso
Disciplina *alocou_disciplina(int *codigo, char *nome, int *bloco, int *ch){

    // Inicializa novo ponteiro
    Disciplina *novo = (Disciplina*) malloc(sizeof(Disciplina));
    
    novo->cod_disciplina = codigo;
    strcpy(novo->nome, nome);
    novo->bloco = bloco;
    novo->carga_horaria = ch;

    novo->cor = RED;
    novo->dir = NULL;
    novo->esq = NULL;

    return novo;
}

Disciplina *cadastrou_disciplina(){
    int cadastrou = 0;

    Disciplina *disciplina;
    int cod_displina;
    char *nome_displina;
    int bloco;
    int carga_horaria;

    disciplina = NULL;
    nome_displina = NULL;

    if(pega_cod(cod_displina)){
        printf("Entre com o nome da nova disciplina: ");
        nome_displina = leitura_de_string();
        
        if(nome_displina != NULL){
            printf("Entre com o numero do Bloco: ");
            bloco = num_inteiro();

            if(bloco){
                printf("Entre com a carga horaria: ");
                carga_horaria = num_inteiro;
                
                if(carga_horaria)
                    cadastrou = 1;
            }
        }
    }

    if(cadastrou){
        // Fazer a alocação de memória de disciplina
        disciplina = alocou_disciplina(cod_displina, nome_displina, bloco, carga_horaria);
    }else{
        if(nome_displina != NULL){
            free(nome_displina);
        }
    }
    return disciplina;
}

int *inseriu_no_disciplina(Disciplina **raiz, Disciplina *novo){
    int inseriu = 0;

    if (raiz == NULL){
        *raiz = novo;
        inseriu = 1;
    }
    else if(novo < (*raiz)->cod_disciplina){
        inseriu = inserir_disciplina(&((*raiz)->esq), novo);
    }else{
        inseriu = inserir_disciplina(&((*raiz)->dir), novo);
    }

    if(inseriu){
        balancear_VP_disciplina(raiz);
    }

    return inseriu;
}

int inseriu_disciplina(Disciplina **raiz, Disciplina *nova){
    int sucesso = 0;

    sucesso = inseriu_no_disciplina(*raiz, nova);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return sucesso; 
}

// ROTAÇÕES
void rotacao_esq_disciplina(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->esq->cor;
    (*raiz)->esq->cor = RED;
}

void rotacao_dir_disciplina(Aluno **raiz){
    Aluno *aux;

    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    (*raiz) = aux;

    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
}

int cor_disciplina(Aluno *aluno){
    int cor;
    if (aluno == NULL)
        cor = BLACK;
    else
        cor = aluno->cor;
    return cor;
}

void troca_cor_disciplina(Aluno *raiz){
    raiz->cor = !(raiz->cor);

    if (raiz->esq != NULL)
        raiz->esq->cor = !(raiz->esq->cor);

    if (raiz->dir != NULL)
        raiz->dir->cor = !(raiz->dir->cor);
}

void balancea_VP_disciplina(Disciplina **raiz){
    if(*raiz != NULL){
        if(cor_disciplina((*raiz)->dir) == RED && cor_disciplina((*raiz)->esq) == BLACK)
            rota_esq_disciplina(raiz);

        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->esq->esq) == RED)
            rota_dir_disciplina(raiz);
    
        if(cor_disciplina((*raiz)->esq) == RED && cor_disciplina((*raiz)->dir) == RED)
            troca_cor_disciplina(*raiz);
    }
}

// Funcao auxiliar para buscar um curso pelo codigo
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

// Funcao recursiva auxiliar para percorrer as disciplinas em ordem crescente
void percorre_disciplinas_em_ordem(Disciplina *raiz) {
    if (raiz != NULL) {
        percorre_disciplinas_em_ordem(raiz->esq);
        printf("Codigo: %d | Nome: %s | Bloco: %d | Carga Horaria: %d\n", 
               raiz->cod_disciplina, raiz->nome, raiz->bloco, raiz->carga_horaria);
        percorre_disciplinas_em_ordem(raiz->dir);
    }
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

// Funcao recursiva auxiliar para filtrar disciplinas por bloco
void percorre_por_bloco(Disciplina *raiz, int bloco) {
    if (raiz != NULL) {
        percorre_por_bloco(raiz->esq, bloco);
        if (raiz->bloco == bloco) {
            printf("Codigo: %d | Nome: %s | Bloco: %d\n", 
                   raiz->cod_disciplina, raiz->nome, raiz->bloco);
        }
        percorre_por_bloco(raiz->dir, bloco);
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

// Funcao recursiva auxiliar para filtrar disciplinas por carga horaria
void percorre_por_carga_horaria(Disciplina *raiz, int carga_horaria){
    if (raiz != NULL){
        percorre_por_carga_horaria(raiz->esq, carga_horaria);
        if (raiz->carga_horaria == carga_horaria) {
            printf("Codigo: %d | Nome: %s | Carga Horaria: %d horas\n", 
                   raiz->cod_disciplina, raiz->nome, raiz->carga_horaria);
        }
        percorre_por_carga_horaria(raiz->dir, carga_horaria);
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

// LIBERACAO
// Funcao para desalocar completamente uma disciplina
void libera_no_disciplina(Disciplina **raiz){
    if (*raiz != NULL){
        if ((*raiz)->nome != NULL)
        {
            free(*raiz);
            *raiz = NULL;
        }

        free(*raiz);
        *raiz = NULL;
    }
}

// Funcao para desalocar toda a árvore de disciplina
void libera_arvore_disciplina(Disciplina **raiz){
    if (*raiz != NULL){
        liberar_arvore_disciplina(&((*raiz)->esq));
        liberar_arvore_disciplina(&((*raiz)->dir));
        liberar_no_disciplina(raiz);
    }
}

// 
int consulta_disciplina(Disciplina *raiz, int codigo_disc){
    int resultado = 0;

    if (raiz != NULL){
        if (raiz->cod_disciplina == codigo_disc)
            resultado = 1;
        else if (raiz->cod_disciplina < codigo_disc)
            resultado = consulta_disciplina(raiz->esq, codigo_disc);
        else
            resultado = consulta_disciplina(raiz->dir, codigo_disc);
    }
    return resultado;
}

// REMOCAO 
// Funcao auxiliar para encontrar o no com o menor codigo em uma subarvore
Disciplina* encontra_menor_disciplina(Disciplina *no) {
    Disciplina *menor = no;
    
    if (menor != NULL) {
        while (menor->esq != NULL) {
            menor = menor->esq;
        }
    }
    
    return menor;
}

void troca_informacoes_disciplinas(Disciplina *disciplina1, Disciplina *disciplina2){
    if (disciplina1 != NULL && disciplina2 != NULL)
    {
        // Troca os nomes
        char *temp_nome = disciplina1->nome;
        strcpy(disciplina1->nome, disciplina2->nome);
        strcpy(disciplina2->nome, temp_nome);

        // Troca os cod_disciplina
        disciplina1->cod_disciplina = disciplina2->cod_disciplina;

        // Troca os blocos
        disciplina1->bloco = disciplina2->bloco;

        // Troca as cargas_horarias
        disciplina1->carga_horaria = disciplina2->carga_horaria;
    }
}

// Função para mover um nó vermelho para a esquerda durante a remoção
void move2_esquerda_disciplina(Disciplina **raiz){
    troca_cor_disciplina(*raiz);

    if ((*raiz)->dir != NULL && cor_disciplina((*raiz)->dir->esq) == RED)
    {
        rotacao_direita_disciplina(&((*raiz)->dir));
        rotacao_esquerda_disciplina(raiz);
        troca_cor_disciplina(*raiz);
    }
}

// Funcao para mover um no vermelho para a direita durante a remocao
void move2_direita_disciplina(Disciplina **raiz){
    troca_cor_disciplina(*raiz);

    if ((*raiz)->esq != NULL && cor_disciplina((*raiz)->esq->esq) == RED)
    {
        rotacao_direita_disciplina(raiz);
        troca_cor_disciplina(*raiz);
    }
}

// Funcao para remover a menor disciplina da arvore
void remove_menor_disciplina_arv(Disciplina **raiz){
    if ((*raiz)->esq == NULL)
        liberar_no_disciplina(raiz);
    else
    {
        if (cor_disciplina((*raiz)->esq) == BLACK && cor_disciplina((*raiz)->esq->esq) == BLACK)
            move2_esquerda_disciplina(raiz);

        remove_menor_disciplina_arv(&((*raiz)->esq));
        balancea_VP_disciplina(raiz);
    }
}

// Funcao recursiva para remover o no da disciplina
int remove_disciplina_no(Disciplina **raiz, int cod_disciplina) {
    int removeu = 1;

    if ((*raiz) != NULL) {
        if (cod_disciplina < (*raiz)->cod_disciplina) {
            if ((*raiz)->esq != NULL) {
                if (cor_disciplina((*raiz)->esq) == BLACK && cor_disciplina((*raiz)->esq->esq) == BLACK) {
                    move2_esquerda_disciplina(raiz);
                }
            }
            removeu = remove_disciplina_no(&((*raiz)->esq), cod_disciplina);
        } else {
            if (cor_disciplina((*raiz)->esq) == RED) {
                rotacao_dir_disciplina(raiz);
            }

            if (cod_disciplina == (*raiz)->cod_disciplina && (*raiz)->dir == NULL) {
                libera_no_disciplina(raiz);
            } else {
                if ((*raiz)->dir != NULL) {
                    if (cor_disciplina((*raiz)->dir) == BLACK && cor_disciplina((*raiz)->dir->esq) == BLACK) {
                        move2_direita_disciplina(raiz);
                    }
                }

                if (cod_disciplina == (*raiz)->cod_disciplina) {
                    Disciplina *menor = encontra_menor_disciplina((*raiz)->dir);
                    troca_informacoes_disciplinas(*raiz, menor);
                    remove_menor_disciplina_arv(&((*raiz)->dir));
                } else {
                    removeu = remove_disciplina_no(&((*raiz)->dir), cod_disciplina);
                }
            }
        }

        // Rebalanceia a arvore se o no atual ainda existe
        if (*raiz != NULL) {
            balancea_VP_disciplina(raiz);
        }
    } else {
        removeu = 0;
    }

    return removeu;
}

// Função principal para remoção - mantém a raiz preta
int remover_disciplina_arvore(Disciplina **raiz, int *codigo){
    int removeu = consulta_disciplina(*raiz, codigo);

    if (removeu)
        removeu = remover_disciplina_no(raiz, codigo);

    if (*raiz != NULL)
        (*raiz)->cor = BLACK;

    return removeu;
}