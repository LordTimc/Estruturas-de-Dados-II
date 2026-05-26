#include <stdio.h>
#include <stdlib.h>
#include "../Arv23_H/structs.h"
#include "../Arv23_H/arv23_curso.h"
#include "../Arv23_H/arv23_disciplina.h"
#include "../Arv23_H/arv23_aluno.h"
#include "../Arv23_H/operacoes.h"

void mensagens_remocao(StatusRemocao status) {
    switch (status) {
        case OK: printf("Removido com sucesso!\n"); break;
        case INFO_NAO_ENCONTRADA: printf("Erro: Codigo nao encontrado.\n"); break;
        case UNDERFLOW: printf("Removido (com underflow resolvido).\n"); break;
        case ARVORE_VAZIA: printf("Arvore vazia!\n"); break;
        default: printf("Ocorreu um erro na exclusao.\n"); break;
    }
}

int main() {
    Arv23_Curso *arvCursos = NULL;
    Arv23_Aluno *arvAlunos = NULL;
    int opcao = 0;

    while (opcao != 16) {
        printf("\n=========================================\n");
        printf("1. Cadastrar Curso\n");
        printf("2. Cadastrar Disciplina\n");
        printf("3. Cadastrar Aluno\n");
        printf("4. Imprimir alunos de um curso\n");
        printf("5. Imprimir alunos de um curso por ano\n");
        printf("6. Mostrar qtd de alunos de um curso\n");
        printf("7. Imprimir arvore de cursos\n");
        printf("8. Imprimir dados de um curso\n");
        printf("9. Imprimir cursos com mesma qtd blocos\n");
        printf("10. Imprimir arvore de disciplinas\n");
        printf("11. Imprimir dados de uma disciplina\n");
        printf("12. Imprimir disciplinas de um bloco\n");
        printf("13. Imprimir disciplinas por CH\n");
        printf("14. Excluir uma disciplina\n");
        printf("15. Excluir um curso\n");
        printf("16. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            CURSO c;
            printf("Codigo: "); scanf("%d", &c.codigo);
            printf("Nome: "); scanf(" %[^\n]s", c.nome);
            printf("Qtd Blocos: "); scanf("%d", &c.qtd_blocos);
            printf("Semanas: "); scanf("%d", &c.semanas);
            c.arv_disciplinas = NULL;
            
            if (insere_23_CURSO(&arvCursos, c)) printf("Curso inserido!\n");
            else printf("Erro: Curso ja existe.\n");
        } 
        else if (opcao == 2) {
            int c_cod; printf("Cod Curso: "); scanf("%d", &c_cod);
            CURSO *curso = buscar_info_curso(arvCursos, c_cod);
            if (curso) {
                DISCIPLINA d;
                printf("Codigo Disc: "); scanf("%d", &d.codigo);
                printf("Nome: "); scanf(" %[^\n]s", d.nome);
                printf("Bloco: "); scanf("%d", &d.bloco);
                printf("Carga Horaria: "); scanf("%d", &d.carga_horaria);
                
                if (d.bloco >= curso->qtd_blocos) printf("Erro: Bloco invalido!\n");
                else if (d.carga_horaria % curso->semanas != 0) printf("Erro: CH deve ser multipla de %d!\n", curso->semanas);
                else {
                    if(insere_23_DISCIPLINA(&(curso->arv_disciplinas), d)) printf("Disciplina inserida!\n");
                    else printf("Erro: Disciplina ja existe!\n");
                }
            } else printf("Curso nao encontrado!\n");
        }
        else if (opcao == 3) {
            ALUNO a;
            printf("Matricula: "); scanf("%d", &a.matricula);
            printf("Nome: "); scanf(" %[^\n]s", a.nome);
            printf("Cod Curso: "); scanf("%d", &a.cod_curso);
            
            if (buscar_info_curso(arvCursos, a.cod_curso)) {
                printf("Ano: "); scanf("%d", &a.ano_ingresso);
                printf("Semestre: "); scanf("%d", &a.semestre_ingresso);
                if (insere_23_ALUNO(&arvAlunos, a)) printf("Aluno inserido!\n");
                else printf("Erro: Matricula ja existe!\n");
            } else printf("Erro: Curso inexistente!\n");
        }
        else if (opcao == 4) {
            int c; printf("Curso: "); scanf("%d", &c);
            req_imprimir_alunos_curso(arvAlunos, c);
        }
        else if (opcao == 5) {
            int c, ano; printf("Curso e Ano: "); scanf("%d %d", &c, &ano);
            req_imprimir_alunos_curso_ano(arvAlunos, c, ano);
        }
        else if (opcao == 6) {
            int c; printf("Curso: "); scanf("%d", &c);
            printf("Total: %d\n", req_contar_alunos_curso(arvAlunos, c));
        }
        else if (opcao == 7) {
            imprime_23_em_ordem_CURSO(arvCursos);
        }
        else if (opcao == 8) {
            int c; printf("Curso: "); scanf("%d", &c);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) printf("Curso [%d] %s\n", curso->codigo, curso->nome);
            else printf("Nao encontrado.\n");
        }
        else if (opcao == 9) {
            int b; printf("Blocos: "); scanf("%d", &b);
            req_imprimir_cursos_blocos(arvCursos, b);
        }
        else if (opcao == 10) {
            int c; printf("Curso: "); scanf("%d", &c);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) imprime_23_em_ordem_DISCIPLINA(curso->arv_disciplinas);
        }
        else if (opcao == 11) {
            int c, d; printf("Cod Curso e Disc: "); scanf("%d %d", &c, &d);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) {
                DISCIPLINA *disc = buscar_info_disciplina(curso->arv_disciplinas, d);
                if(disc) printf("Disciplina [%d] %s\n", disc->codigo, disc->nome);
            }
        }
        else if (opcao == 12) {
            int c, b; printf("Cod Curso e Bloco: "); scanf("%d %d", &c, &b);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) req_imprimir_disciplinas_bloco(curso->arv_disciplinas, b);
        }
        else if (opcao == 13) {
            int c, ch; printf("Cod Curso e CH: "); scanf("%d %d", &c, &ch);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) req_imprimir_disciplinas_carga(curso->arv_disciplinas, ch);
        }
        else if (opcao == 14) {
            int c, d; printf("Cod Curso e Cod Disc a excluir: "); scanf("%d %d", &c, &d);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) {
                StatusRemocao st = remover_23_DISCIPLINA(&(curso->arv_disciplinas), d);
                mensagens_remocao(st);
            } else printf("Curso nao encontrado.\n");
        }
        else if (opcao == 15) {
            int c; printf("Cod Curso a excluir: "); scanf("%d", &c);
            CURSO *curso = buscar_info_curso(arvCursos, c);
            if (curso) {
                if (curso->arv_disciplinas == NULL) {
                    StatusRemocao st = remover_23_CURSO(&arvCursos, c);
                    mensagens_remocao(st);
                } else printf("Erro: Curso possui disciplinas cadastradas.\n");
            } else printf("Curso nao encontrado.\n");
        }
    }
    return 0;
}