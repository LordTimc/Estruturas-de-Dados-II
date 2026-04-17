#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ajuste os caminhos conforme a sua estrutura de diretórios
#include "../AVL_H/structs.h"
#include "../AVL_H/auxiliares.h"
#include "../AVL_H/assinantes.h"
#include "../AVL_H/assinaturas.h"
#include "../AVL_H/formaAssinat.h"
#include "../AVL_H/generos.h"
#include "../AVL_H/livros.h"
#include "../AVL_H/suporteAVL.h"

void exibir_menu() {
    printf("\n======================================================\n");
    printf("                  SISTEMA DE GESTAO                   \n");
    printf("======================================================\n");
    printf(" 1 - Cadastrar Assinante\n");
    printf(" 2 - Cadastrar Forma de Assinatura\n");
    printf(" 3 - Cadastrar Assinatura\n");
    printf(" 4 - Cadastrar Genero\n");
    printf(" 5 - Cadastrar Livro\n");
    printf(" 6 - Mostrar todos os assinantes\n");
    printf(" 7 - Mostrar todas as assinaturas\n");
    printf(" 8 - Mostrar assinaturas por forma\n");
    printf(" 9 - Mostrar formas de assinatura cadastradas\n");
    printf("10 - Mostrar todos os generos\n");
    printf("11 - Mostrar generos atualmente assinados\n");
    printf("12 - Mostrar livros de um determinado genero\n");
    printf("13 - Mostrar vencimento de uma assinatura (por CPF)\n");
    printf("14 - Remover assinatura (somente vencidas)\n");
    printf("15 - Remover assinante (somente sem assinatura ativa)\n");
    printf(" 0 - Sair\n");
    printf("======================================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    // Inicialização das estruturas do sistema
    Assinante *raiz_usuarios = NULL;
    forma_ass *lista_formas = NULL;
    Assinatura *raiz_assinaturas = NULL;
    Livro *raiz_livros_global = NULL; // Árvore AVL geral para organizar todos os livros por ISBN
    int qtd_generos = 0;

    int opcao;
    char cpf_busca[15];
    int codigo_busca;

    do {
        exibir_menu();
        opcao = num_inteiro();

        switch (opcao) {
            case 1: { // Cadastrar Assinantes
                Assinante *novo_usuario = cadastrar_assinante(NULL);
                if (novo_usuario != NULL) {
                    if (inserir_assinante(&raiz_usuarios, novo_usuario)) {
                        printf("\n>>> Assinante cadastrado com sucesso!\n");
                    } else {
                        printf("\n>>> Erro: Cadastro cancelado. Assinante com este CPF ja existe.\n");
                    }
                }
                break;
            }
            case 2: { // Cadastrar Forma de Assinatura
                if (qtd_generos == 0) {
                    printf("\n>>> Erro: E necessario cadastrar pelo menos um genero antes de criar uma forma de assinatura.\n");
                } else {
                    lista_formas = cad_forma_assinatura(lista_formas, qtd_generos);
                }
                break;
            }
            case 3: { // Cadastrar Assinaturas
                if (raiz_usuarios == NULL) {
                    printf("\n>>> Erro: Nenhum assinante cadastrado no sistema.\n");
                } else if (lista_formas == NULL) {
                    printf("\n>>> Erro: Nenhuma forma de assinatura cadastrada no sistema.\n");
                } else {
                    cadastrar_assinatura(&raiz_assinaturas);
                }
                break;
            }
            case 4: { // Cadastrar Generos
                if (raiz_livros_global == NULL) {
                    printf("\n>>> Erro: E necessario ter pelo menos um livro cadastrado no sistema antes de criar um genero.\n");
                } else {
                    int cod_gen;
                    char nome_gen[50];
                    printf("Digite o codigo numérico do genero: ");
                    cod_gen = num_inteiro();
                    
                    if (existe_livro_cad(lista_generos, qtd_generos, cod_gen)) {
                        printf("\n>>> Erro: Genero com este codigo ja esta cadastrado.\n");
                    } else {
                        printf("Digite o nome do genero: ");
                        char *nome_lido = leitura_de_string();
                        if (nome_lido != NULL) {
                            strncpy(nome_gen, nome_lido, 49);
                            nome_gen[49] = '\0';
                            free(nome_lido);
                            
                            Genero novo_gen = criar_genero(cod_gen, nome_gen);
                            if (inserir_genero(lista_generos, &qtd_generos, novo_gen)) {
                                printf("\n>>> Genero cadastrado com sucesso!\n");
                            }
                        }
                    }
                }
                break;
            }
            case 5: { // Cadastrar Livros
                Livro *novo_livro = cadastrar_livro(NULL);
                if (novo_livro != NULL) {
                    if (inserir_livro(&raiz_livros_global, novo_livro)) {
                        printf("\n>>> Livro cadastrado na base de dados com sucesso!\n");
                        
                        if (qtd_generos > 0) {
                            printf("\nDeseja vincular este livro a um genero existente? (1 - Sim / 0 - Nao): ");
                            int vincular = num_inteiro();
                            if (vincular == 1) {
                                printf("Digite o codigo do genero: ");
                                int cod_gen = num_inteiro();
                                int encontrado = 0;
                                for (int i = 0; i < qtd_generos; i++) {
                                    if (lista_generos[i].codigo == cod_gen) {
                                        // Cria uma cópia do nó para a árvore AVL interna do gênero específico
                                        Livro *livro_genero = aloca_livro(novo_livro->isbn, novo_livro->titulo, novo_livro->autor, novo_livro->editora, novo_livro->edicao, novo_livro->ano_publica);
                                        inserir_livro(&(lista_generos[i].colecao_livros), livro_genero);
                                        printf("\n>>> Livro vinculado ao genero '%s'!\n", lista_generos[i].nome);
                                        encontrado = 1;
                                        break;
                                    }
                                }
                                if (!encontrado) printf("\n>>> Genero nao encontrado.\n");
                            }
                        }
                    } else {
                        printf("\n>>> Erro: Livro com este ISBN ja cadastrado.\n");
                    }
                }
                break;
            }
            case 6: // Mostrar todos assinantes
                if (raiz_usuarios == NULL) printf("\n>>> Nenhum assinante cadastrado.\n");
                else mostrar_assinantes(raiz_usuarios);
                break;
            case 7: // Mostrar todas assinaturas
                if (raiz_assinaturas == NULL) printf("\n>>> Nenhuma assinatura cadastrada.\n");
                else mostrar_assinaturas(raiz_assinaturas);
                break;
            case 8: // Mostrar assinaturas de uma forma
                printf("Digite o codigo da forma de assinatura: ");
                codigo_busca = num_inteiro();
                mostrar_assinaturas_por_forma(raiz_assinaturas, codigo_busca);
                break;
            case 9: // Mostrar formas cadastradas
                mostrar_formas_assinatura(lista_formas);
                break;
            case 10: // Mostrar todos os gêneros
                mostrar_generos(lista_generos, qtd_generos);
                break;
            case 11: // Mostrar gêneros assinados
                mostrar_generos_assinados(raiz_assinaturas, lista_formas, lista_generos, qtd_generos);
                break;
            case 12: // Mostrar livros de um gênero
                if (qtd_generos == 0) {
                    printf("\n>>> Nenhum genero cadastrado.\n");
                } else {
                    printf("Digite o codigo do genero: ");
                    codigo_busca = num_inteiro();
                    mostrar_livros_por_genero(lista_generos, qtd_generos, codigo_busca);
                }
                break;
            case 13: // Mostrar data de vencimento
                if (pega_cpf(cpf_busca)) {
                    if (!mostrar_vencimento_assinatura_cpf(raiz_assinaturas, cpf_busca)) {
                        printf("\n>>> Nenhuma assinatura encontrada para o CPF informado.\n");
                    }
                }
                break;
            case 14: { // Remover assinatura (somente vencida)
                if (pega_cpf(cpf_busca)) {
                    Assinatura *ass = buscar_assinatura(raiz_assinaturas, cpf_busca);
                    if (ass != NULL) {
                        Data data_atual;
                        pegar_data_de_hoje(&data_atual);
                        
                        // compara_datas retorna < 0 se a primeira data for no passado
                        if (comparar_datas(ass->data_vencimento, data_atual) < 0) {
                            if (remover_no_assinatura(&raiz_assinaturas, cpf_busca)) {
                                printf("\n>>> Assinatura vencida removida com sucesso!\n");
                            } else {
                                printf("\n>>> Erro ao tentar remover a assinatura.\n");
                            }
                        } else {
                            printf("\n>>> Operacao negada: A assinatura ainda esta ativa (vence apenas no futuro).\n");
                        }
                    } else {
                        printf("\n>>> Assinatura nao encontrada no sistema.\n");
                    }
                }
                break;
            }
            case 15: { // Remover assinante (somente sem assinatura ativa)
                if (pega_cpf(cpf_busca)) {
                    Assinatura *ass = buscar_assinatura(raiz_assinaturas, cpf_busca);
                    if (ass != NULL) {
                        Data data_atual;
                        pegar_data_de_hoje(&data_atual);
                        
                        // Se a assinatura for hoje ou no futuro, está ativa
                        if (comparar_datas(ass->data_vencimento, data_atual) >= 0) {
                            printf("\n>>> Operacao negada: O assinante possui uma assinatura ativa.\n");
                        } else {
                            // Tem assinatura, mas está vencida
                            if (remove_assinant(&raiz_usuarios, cpf_busca)) {
                                printf("\n>>> Assinante removido com sucesso (assinaturas anteriores estavam vencidas)!\n");
                            } else {
                                printf("\n>>> Erro ao remover assinante.\n");
                            }
                        }
                    } else {
                        // Não tem nenhuma assinatura cadastrada
                        if (remove_assinant(&raiz_usuarios, cpf_busca)) {
                            printf("\n>>> Assinante removido com sucesso!\n");
                        } else {
                            printf("\n>>> Erro: Assinante nao encontrado.\n");
                        }
                    }
                }
                break;
            }
            case 0:
                printf("\nEncerrando o sistema e limpando memorias...\n");
                // Aqui você pode chamar liberar_arvore_usuario(raiz_usuarios) e similares 
                break;
            default:
                printf("\n>>> Opcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}