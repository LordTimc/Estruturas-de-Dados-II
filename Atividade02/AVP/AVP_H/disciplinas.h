#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "../AVP_H/structs.h"
// =========================
// FUNÇÕES DE CRIAÇÃO
// =========================

// Aloca memória para uma nova disciplina e inicializa seus campos
Disciplina *aloca_disciplina(int *codigo, char *nome, int *bloco, int *ch);

// Realiza o cadastro de uma disciplina com entrada de dados do usuário
Disciplina *cadastra_disciplina();


// =========================
// FUNÇÕES DE INSERÇÃO
// =========================

// Insere um nó disciplina na árvore rubro-negra
int insere_no_disciplina(Disciplina **raiz, Disciplina *novo);

// Função principal de inserção na árvore
int insere_disciplina(Disciplina **raiz, Disciplina *nova);


// =========================
// ROTAÇÕES (ÁRVORE RUBRO-NEGRA)
// =========================

// Realiza rotação à esquerda na árvore
void rotacao_esq_disciplina(Disciplina **raiz);

// Realiza rotação à direita na árvore
void rotacao_dir_disciplina(Disciplina **raiz);


// =========================
// CONTROLE DE CORES
// =========================

// Retorna a cor do nó
int cor_disciplina(Disciplina *aluno);

// Inverte a cor do nó e de seus filhos
void troca_cor_disciplina(Disciplina *raiz);


// =========================
// BALANCEAMENTO
// =========================

// Realiza o balanceamento da árvore rubro-negra após inserção ou remoção
void balancea_VP_disciplina(Disciplina **raiz);


// =========================
// IMPRESSÃO (DISCIPLINAS)
// =========================

// Percorre a árvore de disciplinas em ordem crescente (em-ordem)
void percorre_disciplinas_em_ordem(Disciplina *raiz);


// =========================
// FILTROS
// =========================

// Percorre a árvore e imprime apenas disciplinas de um determinado bloco
void percorre_por_bloco(Disciplina *raiz, int bloco);


// Percorre a árvore e imprime disciplinas com determinada carga horária
void percorre_por_carga_horaria(Disciplina *raiz, int carga_horaria);


// =========================
// LIBERAÇÃO DE MEMÓRIA
// =========================

// Libera um único nó de disciplina da memória
void libera_no_disciplina(Disciplina **raiz);

// Libera recursivamente todos os nos da árvore de disciplinas (pós-ordem)
void libera_arvore_disciplina(Disciplina **raiz);


// =========================
// CONSULTA 
// =========================

// Verifica se uma disciplina existe na árvore pelo código
int consulta_disciplina(Disciplina *raiz, int codigo_disc);

// =========================
// FUNÇÕES AUXILIARES PARA REMOCAO
// =========================

// Encontra o nó com o menor código em uma subárvore
Disciplina* encontra_menor_disciplina(Disciplina *no);

// Troca as informações entre duas disciplinas
void substitui_informacoes_disciplinas(Disciplina *no_atual, Disciplina *sucessor);


// =========================
// MOVIMENTAÇÃO REMOÇÃO VP
// =========================

// Move um nó vermelho para a esquerda durante o processo de remoção
void move2_esquerda_disciplina(Disciplina **raiz);

// Move um nó vermelho para a direita durante o processo de remoção
void move2_direita_disciplina(Disciplina **raiz);


// =========================
// REMOÇÃO AUXILIAR
// =========================

// Remove o menor nó da árvore de disciplinas
void remove_menor_disciplina_arv(Disciplina **raiz);

// Função recursiva para remover uma disciplina da árvore
int remove_disciplina_no(Disciplina **raiz, int cod_disciplina);


// =========================
// FUNÇÃO PRINCIPAL DE REMOÇÃO
// =========================

// Remove uma disciplina da árvore pelo código
int remove_disciplina_arvore(Disciplina **raiz, int codigo);

#endif