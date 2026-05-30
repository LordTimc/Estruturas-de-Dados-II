#ifndef CURSO_H
#define CURSO_H

#include "../AVP_H/structs.h"

// =========================
// FUNÇÕES DE CRIAÇÃO
// =========================

// Aloca e inicializa um novo no de curso com os dados fornecidos
Curso *aloca_curso(int cod, char *nome, int qtd_blocos, int semanas);

// Lê os dados do usuario e retorna um novo curso alocado, ou NULL em caso de falha
Curso *cadastra_curso();


// =========================
// FUNÇÕES DE INSERÇÃO
// =========================

// Insere recursivamente um curso na arvore e aciona o balanceamento
int insere_no_curso(Curso **raiz, Curso *novo_curso);

// Insere um curso na arvore e garante que a raiz permaneca preta
int insere_curso(Curso **raiz, Curso *novo_curso);


// =========================
// LIBERAÇÃO DE MEMÓRIA
// =========================

// Libera a memoria de um unico no de curso e aponta para NULL
void libera_no_curso(Curso **raiz);

// Libera recursivamente todos os nos da arvore de cursos e suas disciplinas
void libera_arvore_curso(Curso **raiz);


// =========================
// FUNÇÕES AUXILIARES PARA REMOCAO
// =========================

// Retorna o no com o menor codigo em uma subarvore
Curso *encontra_menor_curso(Curso *no);

// Copia os dados do sucessor para o no atual, mantendo estrutura e cor intactas
void substitui_informacoes_curso(Curso *no_atual, Curso *sucessor);


// =========================
// MOVIMENTAÇÃO REMOÇÃO VP
// =========================

// Move um no vermelho para a esquerda durante o processo de remocao
void move2_esquerda_curso(Curso **raiz);

// Move um no vermelho para a direita durante o processo de remocao
void move2_direita_curso(Curso **raiz);

// Conta quantos alunos de uma arvore pertencem a um curso especifico
int conta_alunos_por_curso(Aluno *raiz, int cod_curso);


// =========================
// IMPRESSÃO
// =========================

// Exibe no terminal a quantidade de alunos matriculados em um curso
void mostra_qtd_alunos_por_curso(Aluno *raiz, int cod_curso);

// Imprime todos os cursos em ordem crescente de codigo
void imprime_cursos_crescente(Curso *raiz);

// Busca e exibe os dados de um curso pelo codigo, ou avisa se nao encontrado
void imprime_curso_por_codigo(Curso *raiz, int cod_curso);

// Percorre a arvore, imprime e conta os cursos com a quantidade de blocos informada
int busca_imprime_por_blocos(Curso *raiz, int qtd_blocos);

// Exibe no terminal todos os cursos com uma quantidade especifica de blocos
void lista_cursos_por_qtd_blocos(Curso *raiz, int qtd_blocos);

// =========================
// BUSCA
// =========================

// Busca um curso na árvore de cursos a partir do código informado
// Essa funcao será usado nas 4 funcoes a seguir  
Curso* busca_curso(Curso *raiz, int cod_curso);

// JUSTIFICATIVA: embora essas funções sejam sobre disciplinas, estão no arquivo CURSO para manter a COESÃO, uma vez que o ponto de entrada é na arvore de curso, para depois acessar a raiz disciplinas presente dentro da Struct Curso.

// Imprime todas as disciplinas de um curso em ordem crescente pelo código
void imprime_disciplinas_ordem_crescente(Curso *raiz_cursos, int cod_curso);

// Busca e imprime os dados de uma disciplina específica
// Requer o código do curso e o código da disciplina
void imprime_dados_disciplina(Curso *raiz_cursos, int cod_curso, int cod_disciplina);

// Imprime disciplinas de um curso filtradas por bloco
void imprime_disciplinas_por_bloco(Curso *raiz_cursos, int cod_curso, int bloco);

// Imprime disciplinas de um curso com mesma carga horária
void imprime_disciplinas_por_carga_horaria(Curso *raiz_cursos, int cod_curso, int carga_horaria);

// =========================
// REMOÇÃO AUXILIAR
// =========================

// Remove o no com o menor codigo da arvore, liberando sua memoria
void remove_menor_curso(Curso **raiz);

// Remove o no com o codigo informado da arvore, abortando se houver disciplinas vinculadas
int remove_curso(Curso **raiz, int cod_curso);


// =========================
// FUNÇÃO PRINCIPAL DE REMOÇÃO
// =========================

// Ponto de entrada para remocao: valida existencia e garante raiz preta apos a operacao
int remove_curso_arvore(Curso **raiz, int cod_curso);

#endif