#ifndef ARV23_CURSO_H
#define ARV23_CURSO_H
#include "../Arv23_H/structs.h"


// Valida se o no de curso nao possui ramificacoes
int eh_folha_curso(Arv23_Curso *no);

// Gerencia o cadastro de um curso na arvore 2-3
int cadastrar_curso(Arv23_Curso **raiz, Curso novo_curso);

// Localiza o menor registro a partir do no de curso fornecido
Arv23_Curso *buscar_menor_curso(Arv23_Curso *no);

// Retorna o ponteiro de dados do curso correspondente ao codigo
Curso *buscar_info_curso(Arv23_Curso *raiz, int codigo);

// Coordena de forma recursiva a insercao de um curso
int insere_rec_curso(Arv23_Curso **raiz, Curso valor, Curso *sobe, Arv23_Curso **maior);

// Insere um curso na arvore 2-3
int insere_23_curso(Arv23_Curso **raiz, Curso valor);

// Retorna o unico filho remanescente de um no deficiente de curso
Arv23_Curso *pega_filho_curso(Arv23_Curso *no);

// Redistribui chaves entre um no deficiente de curso e seu irmao esquerdo
int redistribuir_com_irmao_esquerdo_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai, Arv23_Curso *irmao_esq, int pos_filho);

// Redistribui as chaves entre o no deficiente, o pai e o irmao direito
int redistribuir_com_irmao_direito_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai, Arv23_Curso *irmao_dir, int pos_filho);

// Funde o no deficiente com seu irmao esquerdo e faz uma chave do pai descer
int fundir_com_irmao_esquerdo_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai, Arv23_Curso *irmao_esq, int pos_filho);

// Funde o no deficiente com seu irmao direito e faz uma chave do pai descer
int fundir_com_irmao_direito_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai, Arv23_Curso *irmao_dir, int pos_filho);

// Trata o underflow em um no filho redistribuindo ou fundindo chaves com os irmaos
int tratar_underflow_curso(Arv23_Curso **ponteiro_filho, Arv23_Curso *pai);

// Remove de forma recursiva um curso da arvore 2-3 pelo seu codigo
int remover_recursivo_curso(Arv23_Curso **ponteiro_no_atual, int codigo);

// Remove um curso da arvore 2-3 pelo seu codigo e ajusta a raiz se necessario
int remover_23_curso(Arv23_Curso **raiz, int codigo);

// Percorre e exibe todos os cursos da arvore em ordem crescente de codigo
void imprime_23_em_ordem_curso(Arv23_Curso *raiz);

// Funcao que imprime os cursos que possuem uma determinada quantidade de blocos
void imprime_cursos_blocos(Arv23_Curso *raiz, int blocos);

// Libera a memoria de um unico no de curso e de suas disciplinas vinculadas
void libera_no_curso(Arv23_Curso **raiz);

// Libera recursivamente toda a arvore 2-3 de cursos e todas as suas disciplinas
void libera_arvore_curso(Arv23_Curso **raiz);

#endif