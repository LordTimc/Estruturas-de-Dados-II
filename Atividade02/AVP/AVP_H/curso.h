// =========================
// BUSCA
// =========================

// Busca um curso na árvore de cursos a partir do código informado
// Essa funcao será usado nas 4 funcoes a seguir  
Curso* busca_curso(Curso *raiz, int cod_curso);

// JUSTIFICATIVA: embora essas funções sejam sobre disciplinas, estão no arquivo CURSO para manter a COESÃO, uma vez que o ponto de entrada é na arvore de curso, para depois acessar a raiz disciplinas presente dentro da Struct Curso.

// Imprime todas as disciplinas de um curso em ordem crescente pelo código
// Primeiro busca o curso e depois percorre sua árvore de disciplinas
void imprime_disciplinas_ordem_crescente(Curso *raiz_cursos, int cod_curso);

// Busca e imprime os dados de uma disciplina específica
// Requer o código do curso e o código da disciplina
void imprime_dados_disciplina(Curso *raiz_cursos, int cod_curso, int cod_disciplina);

// Imprime disciplinas de um curso filtradas por bloco
void imprime_disciplinas_por_bloco(Curso *raiz_cursos, int cod_curso, int bloco);

// Imprime disciplinas de um curso com mesma carga horária
void imprime_disciplinas_por_carga_horaria(Curso *raiz_cursos, int cod_curso, int carga_horaria);