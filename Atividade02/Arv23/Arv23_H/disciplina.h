#ifndef ARV23_DISCIPLINA_H
#define ARV23_DISCIPLINA_H
#include "../Arv23_H/structs.h"


// Verifica a ausencia de ramificacoes em um no de disciplina
int eh_folha_disciplina(Arv23_Disciplina *no);

// Gerencia o cadastro de uma disciplina na arvore 2-3
int cadastrar_disciplina(Arv23_Disciplina **raiz, Disciplina nova_disciplina);

// Recupera o menor registro na ramificacao indicada
Arv23_Disciplina *buscar_menor_elemento_disciplina(Arv23_Disciplina *no);

// Busca os dados de uma disciplina atraves do seu codigo
Disciplina *buscar_info_disciplina(Arv23_Disciplina *raiz, int codigo);

// Insere de forma recursiva uma nova disciplina na arvore
int insere_23_recursivo_disciplina(Arv23_Disciplina **raiz, Disciplina valor, Disciplina *sobe, Arv23_Disciplina **maiorNo);

// Insere uma disciplina na arvore 2-3
int insere_23_disciplina(Arv23_Disciplina **raiz, Disciplina valor);

// Retorna o unico filho remanescente de um no deficiente
Arv23_Disciplina *pega_filho(Arv23_Disciplina *no);

// Redistribui dados entre um filho deficiente e seu irmao esquerdo
int redistribuir_com_irmao_esquerdo_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq, int pos_filho);

// Redistribui dados entre um filho deficiente e seu irmao direito
int redistribuir_com_irmao_direito_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_dir, int pos_filho);

// Funde um filho deficiente com seu irmao esquerdo
int fundir_com_irmao_esquerdo_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_esq, int pos_filho);

// Funde um filho deficiente com seu irmao direito
int fundir_com_irmao_direito_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai, Arv23_Disciplina *irmao_dir, int pos_filho);

// Trata o underflow em um no filho redistribuindo ou fundindo chaves
int tratar_underflow_disciplina(Arv23_Disciplina **ponteiro_filho, Arv23_Disciplina *pai);

// Remove de forma recursiva uma disciplina da arvore 2-3 pelo codigo
int remover_recursivo_disciplina(Arv23_Disciplina **ponteiro_no_atual, int codigo);

// Remove uma disciplina da arvore 2-3 pelo seu codigo e ajusta a raiz se necessario
int remover_23_disciplina(Arv23_Disciplina **raiz, int codigo);

// Percorre e exibe todas as disciplinas da arvore em ordem crescente de codigo
void imprime_23_em_ordem_disciplina(Arv23_Disciplina *raiz);

// Funcao que imprime as disciplinas de um curso pertencentes a um bloco especifico
void imprime_disciplinas_bloco(Arv23_Disciplina *raiz, int bloco);

// Funcao que imprime as disciplinas que possuem uma determinada carga horaria
void imprime_disciplinas_carga(Arv23_Disciplina *raiz, int carga);

// Libera recursivamente toda a arvore 2-3 de disciplinas
void libera_arvore_disciplina(Arv23_Disciplina **raiz);

#endif