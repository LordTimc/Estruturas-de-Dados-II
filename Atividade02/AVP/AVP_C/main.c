#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../AVP_H/aluno.h"
#include "../AVP_H/curso.h"
#include "../AVP_H/disciplinas.h"
#include "../AVP_H/structs.h"
#include "../AVP_H/auxiliares.h"
#include "../AVP_H/main.h"

void menu(){
    printf("\n 1  - Cadastrar Curso\n");
    printf(" 2  - Cadastrar Aluno\n");
    printf(" 3  - Cadastrar Disciplina\n");
    printf(" 4  - Listar alunos de um curso (por codigo do curso)\n");
    printf(" 5  - Listar alunos de um curso por ano de ingresso\n");
    printf(" 6  - Contar alunos de um curso\n");
    printf(" 7  - Listar cursos em ordem crescente (por codigo)\n");
    printf(" 8  - Exibir dados de um curso (por codigo)\n");
    printf(" 9  - Listar cursos com determinada quantidade de blocos\n");
    printf(" 10 - Listar disciplinas de um curso (ordem crescente)\n");
    printf(" 11 - Exibir dados de uma disciplina (por codigo do curso e da disciplina)\n");
    printf(" 12 - Listar disciplinas de um bloco de um curso\n");
    printf(" 13 - Listar disciplinas de um curso com determinada carga horaria\n");
    printf(" 14 - Remover uma disciplina de um curso\n");
    printf(" 15 - Remover um curso (somente se nao houver disciplinas)\n");
    printf(" 0  - Sair\n");
    printf("===================================================\n");
    printf("Opcao: ");
}

void menu_geral(){
    /* Arvores principais do sistema */
    Curso *raiz_cursos = NULL;
    Aluno *raiz_alunos = NULL;

    int opcao    = -1;  /* opcao escolhida pelo usuario     */
    int executou =  0;  /* flag de controle de saida unica  */

    while (opcao != 0) {
        menu();
        opcao = num_inteiro();
        executou = 0;

        switch (opcao) {

            /* -------------------------------------------------- */
            /* OPCAO 1 - Cadastrar Curso                           */
            /* -------------------------------------------------- */
            case 1: {
                Curso *novo_curso = cadastra_curso();

                if (novo_curso != NULL) {
                    executou = insere_curso(&raiz_cursos, novo_curso);

                    if (executou) {
                        printf("\nCurso cadastrado com sucesso!\n");
                    } else {
                        printf("\nErro: curso ja existente ou nao foi possivel inserir.\n");
                        free(novo_curso);
                    }
                } else {
                    printf("\nCadastro cancelado ou dados invalidos.\n");
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 2 - Cadastrar Aluno                           */
            /* -------------------------------------------------- */
            case 2: {
                Aluno *novo_aluno = cadastra_aluno();

                if (novo_aluno != NULL) {
                    /* Verifica se o curso informado existe antes de inserir */
                    Curso *curso_ref = busca_curso(raiz_cursos, novo_aluno->codigo_Curso);

                    if (curso_ref != NULL) {
                        executou = insere_aluno(&raiz_alunos, novo_aluno);

                        if (executou) {
                            printf("\nAluno cadastrado com sucesso!\n");
                        } else {
                            printf("\nErro: aluno ja existente ou nao foi possivel inserir.\n");
                            free(novo_aluno);
                        }
                    } else {
                        printf("\nErro: curso com codigo %d nao encontrado. Aluno nao cadastrado.\n",
                               novo_aluno->codigo_Curso);
                        free(novo_aluno);
                    }
                } else {
                    printf("\nCadastro cancelado ou dados invalidos.\n");
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 3 - Cadastrar Disciplina em um Curso          */
            /* -------------------------------------------------- */
            case 3: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado. Cadastre um curso primeiro.\n");
                } else {
                    printf("Digite o codigo do curso ao qual a disciplina pertence: ");
                    int cod_curso_disc = num_inteiro();

                    Curso *curso_alvo = busca_curso(raiz_cursos, cod_curso_disc);

                    if (curso_alvo != NULL) {
                        Disciplina *nova_disc = cadastra_disciplina();

                        if (nova_disc != NULL) {
                            executou = insere_disciplina(&(curso_alvo->raiz_disciplinas), nova_disc);

                            if (executou) {
                                printf("\nDisciplina cadastrada com sucesso no curso '%s'!\n",
                                       curso_alvo->nome);
                            } else {
                                printf("\nErro: disciplina ja existente ou nao foi possivel inserir.\n");
                                free(nova_disc);
                            }
                        } else {
                            printf("\nCadastro cancelado ou dados invalidos.\n");
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod_curso_disc);
                    }
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 4 - Listar alunos de um curso                 */
            /* -------------------------------------------------- */
            case 4: {
                if (raiz_alunos == NULL) {
                    printf("\nNenhum aluno cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod4 = num_inteiro();

                    printf("\n--- Alunos do curso %d ---\n", cod4);
                    imprime_alunos_por_curso(raiz_alunos, cod4);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 5 - Listar alunos de um curso por ano         */
            /* -------------------------------------------------- */
            case 5: {
                if (raiz_alunos == NULL) {
                    printf("\nNenhum aluno cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod5 = num_inteiro();

                    printf("Digite o ano de ingresso: ");
                    int ano5 = num_inteiro();

                    printf("\n--- Alunos do curso %d ingressados em %d ---\n", cod5, ano5);
                    imprime_alunos_por_curso_ano(raiz_alunos, cod5, ano5);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 6 - Contar alunos de um curso                 */
            /* -------------------------------------------------- */
            case 6: {
                if (raiz_alunos == NULL) {
                    printf("\nNenhum aluno cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod6 = num_inteiro();

                    mostra_qtd_alunos_por_curso(raiz_alunos, cod6);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 7 - Listar cursos em ordem crescente          */
            /* -------------------------------------------------- */
            case 7: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("\n--- Cursos em ordem crescente ---\n");
                    imprime_cursos_crescente(raiz_cursos);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 8 - Exibir dados de um curso                  */
            /* -------------------------------------------------- */
            case 8: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod8 = num_inteiro();

                    imprime_curso_por_codigo(raiz_cursos, cod8);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 9 - Listar cursos por quantidade de blocos    */
            /* -------------------------------------------------- */
            case 9: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite a quantidade de blocos: ");
                    int blocos9 = num_inteiro();

                    lista_cursos_por_qtd_blocos(raiz_cursos, blocos9);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 10 - Listar disciplinas de um curso (ord. cres.) */
            /* -------------------------------------------------- */
            case 10: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod10 = num_inteiro();

                    imprime_disciplinas_ordem_crescente(raiz_cursos, cod10);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 11 - Exibir dados de uma disciplina           */
            /* -------------------------------------------------- */
            case 11: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod11c = num_inteiro();

                    printf("Digite o codigo da disciplina: ");
                    int cod11d = num_inteiro();

                    imprime_dados_disciplina(raiz_cursos, cod11c, cod11d);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 12 - Listar disciplinas de um bloco           */
            /* -------------------------------------------------- */
            case 12: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod12 = num_inteiro();

                    printf("Digite o numero do bloco: ");
                    int bloco12 = num_inteiro();

                    imprime_disciplinas_por_bloco(raiz_cursos, cod12, bloco12);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 13 - Listar disciplinas por carga horaria     */
            /* -------------------------------------------------- */
            case 13: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod13 = num_inteiro();

                    printf("Digite a carga horaria: ");
                    int ch13 = num_inteiro();

                    imprime_disciplinas_por_carga_horaria(raiz_cursos, cod13, ch13);
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 14 - Remover disciplina de um curso           */
            /* -------------------------------------------------- */
            case 14: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso: ");
                    int cod14c = num_inteiro();

                    Curso *curso14 = busca_curso(raiz_cursos, cod14c);

                    if (curso14 != NULL) {
                        printf("Digite o codigo da disciplina a remover: ");
                        int cod14d = num_inteiro();

                        executou = remove_disciplina_arvore(&(curso14->raiz_disciplinas), cod14d);

                        if (executou) {
                            printf("\nDisciplina removida com sucesso!\n");
                        } else {
                            printf("\nDisciplina com codigo %d nao encontrada no curso '%s'.\n",
                                   cod14d, curso14->nome);
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod14c);
                    }
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 15 - Remover curso (sem disciplinas)          */
            /* -------------------------------------------------- */
            case 15: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso a remover: ");
                    int cod15 = num_inteiro();

                    executou = remove_curso_arvore(&raiz_cursos, cod15);

                    if (executou) {
                        printf("\nCurso removido com sucesso!\n");
                    } else {
                        printf("\nNao foi possivel remover o curso %d.\n", cod15);
                        printf("Verifique se o curso existe e se nao possui disciplinas cadastradas.\n");
                    }
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 0 - Sair                                      */
            /* -------------------------------------------------- */
            case 0: {
                printf("\nEncerrando o sistema. Liberando memoria...\n");
                libera_arvore_curso(&raiz_cursos);
                libera_arvore_aluno(&raiz_alunos);
                printf("Memoria liberada. Ate logo!\n");
                break;
            }

            /* -------------------------------------------------- */
            /* Opcao invalida                                       */
            /* -------------------------------------------------- */
            default: {
                printf("\nOpcao invalida. Digite um numero entre 0 e 15.\n");
                break;
            }
        }
    }
}

int main(){
    menu_geral();
    return 0;
}
