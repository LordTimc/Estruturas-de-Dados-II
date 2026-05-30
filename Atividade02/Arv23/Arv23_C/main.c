#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Arv23_H/curso.h"
#include "../Arv23_H/disciplina.h"
#include "../Arv23_H/aluno.h"

#include "../Arv23_H/structs.h"
#include "../Arv23_H/auxiliares.h"
#include "../Arv23_H/suporteArv23.h"


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
    Arv23_Curso  *raiz_cursos = NULL;
    Arv23_Aluno  *raiz_alunos = NULL;

    int opcao    = -1;  /* opcao escolhida pelo usuario    */
    int executou =  0;  /* flag de controle de saida unica */

    while (opcao != 0) {
        menu();
        opcao = num_inteiro();
        executou = 0;

        switch (opcao) {

            /* -------------------------------------------------- */
            /* OPCAO 1 - Cadastrar Curso                           */
            /* -------------------------------------------------- */
            case 1: {
                Curso novo_curso;
                char *nome_lido = NULL;

                printf("Digite o codigo do curso: ");
                novo_curso.codigo = num_inteiro();

                printf("Digite o nome do curso: ");
                nome_lido = leitura_de_string();

                if (nome_lido != NULL) {
                    strncpy(novo_curso.nome, nome_lido, 99);
                    novo_curso.nome[99] = '\0';
                    free(nome_lido);

                    printf("Digite a quantidade de blocos: ");
                    novo_curso.qtd_blocos = num_inteiro();

                    printf("Digite a quantidade de semanas por disciplina: ");
                    novo_curso.semanas = num_inteiro();

                    novo_curso.arv_disciplinas = NULL;

                    executou = cadastrar_curso(&raiz_cursos, novo_curso);

                    if (executou) {
                        printf("\nCurso cadastrado com sucesso!\n");
                    } else {
                        printf("\nErro: curso ja existente ou dados invalidos.\n");
                    }
                } else {
                    printf("\nErro na leitura do nome. Cadastro cancelado.\n");
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 2 - Cadastrar Aluno                           */
            /* -------------------------------------------------- */
            case 2: {
                Aluno novo_aluno;
                char *nome_lido = NULL;

                printf("Digite a matricula do aluno: ");
                novo_aluno.matricula = num_inteiro();

                printf("Digite o nome do aluno: ");
                nome_lido = leitura_de_string();

                if (nome_lido != NULL) {
                    strncpy(novo_aluno.nome, nome_lido, 99);
                    novo_aluno.nome[99] = '\0';
                    free(nome_lido);

                    printf("Digite o codigo do curso do aluno: ");
                    novo_aluno.cod_curso = num_inteiro();

                    printf("Digite o ano de ingresso: ");
                    novo_aluno.ano_ingresso = num_inteiro();

                    printf("Digite o semestre de ingresso (1 ou 2): ");
                    novo_aluno.semestre_ingresso = num_inteiro();

                    executou = cadastrar_aluno(&raiz_alunos, raiz_cursos, novo_aluno);

                    if (executou) {
                        printf("\nAluno cadastrado com sucesso!\n");
                    } else {
                        printf("\nErro: curso nao encontrado ou aluno ja existente.\n");
                    }
                } else {
                    printf("\nErro na leitura do nome. Cadastro cancelado.\n");
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 3 - Cadastrar Disciplina                      */
            /* -------------------------------------------------- */
            case 3: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado. Cadastre um curso primeiro.\n");
                } else {
                    printf("Digite o codigo do curso ao qual a disciplina pertence: ");
                    int cod_curso3 = num_inteiro();

                    Curso *curso_alvo = buscar_info_curso(raiz_cursos, cod_curso3);

                    if (curso_alvo != NULL) {
                        Disciplina nova_disc;
                        char *nome_lido = NULL;

                        printf("Digite o codigo da disciplina: ");
                        nova_disc.codigo = num_inteiro();

                        printf("Digite o nome da disciplina: ");
                        nome_lido = leitura_de_string();

                        if (nome_lido != NULL) {
                            strncpy(nova_disc.nome, nome_lido, 99);
                            nova_disc.nome[99] = '\0';
                            free(nome_lido);

                            printf("Digite o numero do bloco: ");
                            nova_disc.bloco = num_inteiro();

                            printf("Digite a carga horaria: ");
                            nova_disc.carga_horaria = num_inteiro();

                            executou = cadastrar_disciplina(&(curso_alvo->arv_disciplinas), nova_disc);

                            if (executou) {
                                printf("\nDisciplina cadastrada com sucesso no curso '%s'!\n",
                                       curso_alvo->nome);
                            } else {
                                printf("\nErro: disciplina ja existente ou dados invalidos.\n");
                            }
                        } else {
                            printf("\nErro na leitura do nome. Cadastro cancelado.\n");
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod_curso3);
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
                    imprime_alunos_curso(raiz_alunos, cod4);
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
                    imprime_alunos_curso_ano(raiz_alunos, cod5, ano5);
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

                    int total6 = conta_alunos_curso(raiz_alunos, cod6);
                    printf("\nTotal de alunos no curso %d: %d\n", cod6, total6);
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
                    imprime_23_em_ordem_curso(raiz_cursos);
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

                    Curso *curso8 = buscar_info_curso(raiz_cursos, cod8);

                    if (curso8 != NULL) {
                        printf("\n--- Dados do Curso ---\n");
                        printf("Codigo  : %d\n", curso8->codigo);
                        printf("Nome    : %s\n", curso8->nome);
                        printf("Blocos  : %d\n", curso8->qtd_blocos);
                        printf("Semanas : %d\n", curso8->semanas);
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod8);
                    }
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

                    printf("\n--- Cursos com %d bloco(s) ---\n", blocos9);
                    imprime_cursos_blocos(raiz_cursos, blocos9);
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

                    Curso *curso10 = buscar_info_curso(raiz_cursos, cod10);

                    if (curso10 != NULL) {
                        printf("\n--- Disciplinas do curso '%s' ---\n", curso10->nome);
                        if (curso10->arv_disciplinas == NULL) {
                            printf("Nenhuma disciplina cadastrada neste curso.\n");
                        } else {
                            imprime_23_em_ordem_disciplina(curso10->arv_disciplinas);
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod10);
                    }
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

                    Curso *curso11 = buscar_info_curso(raiz_cursos, cod11c);

                    if (curso11 != NULL) {
                        printf("Digite o codigo da disciplina: ");
                        int cod11d = num_inteiro();

                        Disciplina *disc11 = buscar_info_disciplina(curso11->arv_disciplinas, cod11d);

                        if (disc11 != NULL) {
                            printf("\n--- Dados da Disciplina ---\n");
                            printf("Codigo        : %d\n", disc11->codigo);
                            printf("Nome          : %s\n", disc11->nome);
                            printf("Bloco         : %d\n", disc11->bloco);
                            printf("Carga horaria : %d h\n", disc11->carga_horaria);
                        } else {
                            printf("\nDisciplina com codigo %d nao encontrada no curso '%s'.\n",
                                   cod11d, curso11->nome);
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod11c);
                    }
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

                    Curso *curso12 = buscar_info_curso(raiz_cursos, cod12);

                    if (curso12 != NULL) {
                        printf("Digite o numero do bloco: ");
                        int bloco12 = num_inteiro();

                        printf("\n--- Disciplinas do bloco %d no curso '%s' ---\n",
                               bloco12, curso12->nome);
                        imprime_disciplinas_bloco(curso12->arv_disciplinas, bloco12);
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod12);
                    }
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

                    Curso *curso13 = buscar_info_curso(raiz_cursos, cod13);

                    if (curso13 != NULL) {
                        printf("Digite a carga horaria: ");
                        int ch13 = num_inteiro();

                        printf("\n--- Disciplinas com %d h no curso '%s' ---\n",
                               ch13, curso13->nome);
                        imprime_disciplinas_carga(curso13->arv_disciplinas, ch13);
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod13);
                    }
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

                    Curso *curso14 = buscar_info_curso(raiz_cursos, cod14c);

                    if (curso14 != NULL) {
                        if (curso14->arv_disciplinas == NULL) {
                            printf("\nO curso '%s' nao possui disciplinas cadastradas.\n",
                                   curso14->nome);
                        } else {
                            printf("Digite o codigo da disciplina a remover: ");
                            int cod14d = num_inteiro();

                            executou = remover_23_disciplina(&(curso14->arv_disciplinas), cod14d);

                            if (executou == 1) {
                                printf("\nDisciplina removida com sucesso!\n");
                            } else {
                                printf("\nDisciplina com codigo %d nao encontrada no curso '%s'.\n",
                                       cod14d, curso14->nome);
                            }
                        }
                    } else {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod14c);
                    }
                }
                break;
            }

            /* -------------------------------------------------- */
            /* OPCAO 15 - Remover curso sem disciplinas            */
            /* -------------------------------------------------- */
            case 15: {
                if (raiz_cursos == NULL) {
                    printf("\nNenhum curso cadastrado.\n");
                } else {
                    printf("Digite o codigo do curso a remover: ");
                    int cod15 = num_inteiro();

                    Curso *curso15 = buscar_info_curso(raiz_cursos, cod15);

                    if (curso15 == NULL) {
                        printf("\nCurso com codigo %d nao encontrado.\n", cod15);
                    } else if (curso15->arv_disciplinas != NULL) {
                        printf("\nNao e possivel remover o curso '%s': possui disciplinas cadastradas.\n",
                               curso15->nome);
                    } else {
                        executou = remover_23_curso(&raiz_cursos, cod15);

                        if (executou == 1) {
                            printf("\nCurso removido com sucesso!\n");
                        } else {
                            printf("\nErro ao remover o curso com codigo %d.\n", cod15);
                        }
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