#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusões dos cabeçalhos do sistema
#include "../ABB_H/structs.h"
#include "../ABB_H/assinantes.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/formaAssinat.h"
#include "../ABB_H/generos.h"
#include "../ABB_H/livros.h"
#include "../ABB_H/auxiliares.h"


// Protótipos das funções de interface
void menu_das_opcoes();
void menu_da_repeticao();

int main() {
    // 1. INICIALIZAÇÃO DAS ESTRUTURAS DE DADOS
    Assinante *raiz_assinante = NULL;
    Assinatura *raiz_assinatura = NULL;
    forma_ass *lista_forma = NULL;
    
    // Árvore Global de Livros (necessária para os livros existirem antes dos gêneros)
    Livro *raiz_livros_global = NULL;
    
    int qtd_generos_cadastrados = 0; 
    int opc = -1;
    int repetir = 1;
    int resposta = 0;
    char cpf_busca[15];

    printf("====================================================\n");
    printf("        BEM-VINDO AO SISTEMA DE GESTAO DE LIVROS    \n");
    printf("====================================================\n");

    do {
        if (repetir == 1) {
            menu_das_opcoes();
            printf("\nEscolha uma opcao: ");
            opc = num_inteiro();

            switch (opc) {
                case 1: {
                    printf("\n--- CADASTRAR ASSINANTE ---\n");
                    Assinante *novo_assinante = cadastrar_assinante(NULL);
                    if(novo_assinante != NULL) {
                        resposta = inserir_assinante(&raiz_assinante, novo_assinante);
                        if(resposta == 1) printf("\nAssinante cadastrado com sucesso!\n");
                        else printf("\nErro: Assinante com este CPF ja existe no sistema.\n");
                    }
                    break;
                }
                
                case 2: {
                    printf("\n--- CADASTRAR FORMA DE ASSINATURA ---\n");
                    // TRAVA FASE 1: Precisa de Gênero
                    if (qtd_generos_cadastrados == 0) {
                        printf("Erro: Voce precisa cadastrar pelo menos 1 genero antes.\n");
                    } else {
                        lista_forma = cad_forma_assinatura(lista_forma, qtd_generos_cadastrados);
                    }
                    break;
                }
                
                case 3: {
                    printf("\n--- CADASTRAR ASSINATURA ---\n");
                    // TRAVA FASE 1: Precisa de Assinante e Forma
                    if (raiz_assinante == NULL || lista_forma == NULL) {
                        printf("Erro: Cadastre pelo menos 1 assinante e 1 forma de assinatura primeiro.\n");
                    } else {
                        cadastrar_assinatura(&raiz_assinatura, raiz_assinante, lista_forma);
                    }
                    break;
                }
                
                case 4: {
                    printf("\n--- CADASTRAR GENERO ---\n");
                    // TRAVA FASE 1: Precisa de Livro cadastrado antes
                    if (raiz_livros_global == NULL) {
                        printf("Erro: Voce precisa ter pelo menos um livro cadastrado no sistema antes de criar generos.\n");
                    } else if (qtd_generos_cadastrados >= MAX_GENEROS) {
                        printf("Erro: Limite maximo de generos atingido.\n");
                    } else {
                        printf("Digite o codigo do genero (numerico): ");
                        int cod_gen = num_inteiro();
                        
                        if (existe_livro_cad(lista_generos, qtd_generos_cadastrados, cod_gen)) {
                            printf("Erro: Ja existe um genero com este codigo.\n");
                        } else {
                            printf("Digite o nome do genero: ");
                            char *nome_gen = leitura_de_string();
                            if (nome_gen != NULL) {
                                Genero novo_gen = criar_genero(cod_gen, nome_gen);
                                inserir_genero(lista_generos, &qtd_generos_cadastrados, novo_gen);
                                printf("\nGenero cadastrado com sucesso!\n");
                                free(nome_gen);
                            }
                        }
                    }
                    break;
                }
                
                case 5: {
                    // FASE 2 e FASE 3: Cadastrar Livro com opção de vínculo
                    printf("\n--- CADASTRAR LIVRO ---\n");
                    Livro *novo_livro = cadastrar_livro(NULL);
                    if (novo_livro != NULL) {
                        
                        // Insere na árvore global de livros
                        if (inserir_livro(&raiz_livros_global, novo_livro)) {
                            printf("\nLivro cadastrado no sistema global com sucesso!\n");
                            
                            // Pergunta de vínculo (se houver gêneros)
                            if (qtd_generos_cadastrados > 0) {
                                printf("\nDeseja vincular este livro a um genero existente? (1 - Sim / 0 - Nao): ");
                                int vincular = num_inteiro();
                                
                                if (vincular == 1) {
                                    mostrar_generos(lista_generos, qtd_generos_cadastrados);
                                    printf("\nDigite o CODIGO do genero: ");
                                    int cod_busca = num_inteiro();
                                    
                                    int indice_genero = -1;
                                    for (int i = 0; i < qtd_generos_cadastrados; i++) {
                                        if (lista_generos[i].codigo == cod_busca) {
                                            indice_genero = i;
                                            break;
                                        }
                                    }
                                    
                                    if (indice_genero == -1) {
                                        printf("Erro: Genero nao encontrado. O livro ficara apenas no catalogo global.\n");
                                    } else {
                                        // Cria uma cópia independente do livro para a árvore do Gênero
                                        Livro *copia = aloca_livro(novo_livro->isbn, novo_livro->titulo, novo_livro->autor, novo_livro->editora, novo_livro->edicao, novo_livro->ano_publica);
                                        inserir_livro(&(lista_generos[indice_genero].colecao_livros), copia);
                                        printf("Livro vinculado ao genero %s com sucesso!\n", lista_generos[indice_genero].nome);
                                    }
                                }
                            }
                        } else {
                            printf("\nErro: Livro com este ISBN ja existe.\n");
                        }
                    }
                    break;
                }
                
                case 6:
                    printf("\n--- LISTA DE ASSINANTES ---\n");
                    if (mostrar_assinantes(raiz_assinante) == 0) printf("Nenhum assinante cadastrado na arvore.\n");
                    break;
                    
                case 7:
                    printf("\n--- LISTA DE ASSINATURAS ---\n");
                    if (raiz_assinatura == NULL) printf("Nenhuma assinatura cadastrada.\n");
                    else mostrar_assinaturas(raiz_assinatura);
                    break;
                    
                case 8:
                    printf("\n--- BUSCAR ASSINATURAS POR FORMA ---\n");
                    printf("Digite o codigo da forma de assinatura: ");
                    mostrar_assinaturas_por_forma(raiz_assinatura, num_inteiro());
                    break;
                    
                case 9:
                    mostrar_formas_assinatura(lista_forma);
                    break;
                    
                case 10:
                    mostrar_generos(lista_generos, qtd_generos_cadastrados);
                    break;
                    
                case 11:
                    if (raiz_assinatura == NULL || lista_forma == NULL) printf("\nNao ha assinaturas para verificar.\n");
                    else mostrar_generos_assinados(raiz_assinatura, lista_forma, lista_generos, qtd_generos_cadastrados);
                    break;
                    
                case 12:
                    printf("\n--- LIVROS POR GENERO ---\n");
                    printf("Digite o codigo do genero: ");
                    mostrar_livros_por_genero(lista_generos, qtd_generos_cadastrados, num_inteiro());
                    break;
                    
                case 13: {
                    printf("\n--- VENCIMENTO DE ASSINATURA ---\n");
                    if (pega_cpf(cpf_busca)) {
                        if (mostrar_vencimento_assinatura_cpf(raiz_assinatura, cpf_busca) == 0)
                            printf("Nenhuma assinatura encontrada para o CPF.\n");
                    }
                    break;
                }
                
                case 14: {
                    // TRAVA FASE 6: Exclui apenas se vencida
                    printf("\n--- REMOVER ASSINATURA ---\n");
                    if (pega_cpf(cpf_busca)) {
                        Assinatura *ass = buscar_assinatura(raiz_assinatura, cpf_busca);
                        if (ass == NULL) {
                            printf("Erro: Nenhuma assinatura encontrada.\n");
                        } else {
                            if (possui_assinatura_vencida(raiz_assinatura, cpf_busca)) {
                                remover_no_assinatura(&raiz_assinatura, cpf_busca);
                                printf("Operacao de Sucesso: Assinatura removida!\n");
                            } else {
                                printf("Operacao negada! A assinatura esta ATIVA e nao pode ser removida.\n");
                            }
                        }
                    }
                    break;
                }
                
                case 15: {
                    // TRAVA FASE 6: Exclui apenas sem assinaturas ativas
                    printf("\n--- REMOVER ASSINANTE ---\n");
                    char cpf_assinante[12];
                    if (pega_cpf(cpf_assinante)) {
                        Assinatura *ass = buscar_assinatura(raiz_assinatura, cpf_assinante);
                        if (ass != NULL && !possui_assinatura_vencida(raiz_assinatura, cpf_assinante)) {
                            printf("Operacao negada! O assinante possui assinatura ATIVA.\n");
                        } else {
                            if (remove_assinant(&raiz_assinante, cpf_assinante)) {
                                printf("Removido com sucesso! O usuario agora esta livre de pendencias.\n");
                            } else {
                                printf("Assinante nao encontrado.\n");
                            }
                        }
                    }
                    break;
                }
                // Dentro do main.c (exemplo de uso)

                case 99: {
                    printf("\n--- BATERIA DE TESTES: LETRA A ---\n");
                    executar_teste_letra_A(1000000); // 1 Milhão
                    executar_teste_letra_A(2000000); // 2 Milhões
                    executar_teste_letra_A(3000000); // 3 Milhões
                    executar_teste_letra_A(4000000); // 4 Milhões


                    printf("\n--- BATERIA DE TESTES: LETRA B ---\n");
                    executar_teste_letra_B(); // <-- ADICIONE AQUI
                    break;
            }
                
                case 0:
                    printf("\nLiberando memoria e finalizando...\n");
                    liberar_arvore_usuario(raiz_assinante);
                    liberar_arvore_assinaturas(raiz_assinatura);
                    liberar_lista_formas(lista_forma);
                    liberar_arvore_livros(raiz_livros_global);
                    for (int i = 0; i < qtd_generos_cadastrados; i++) {
                        liberar_arvore_livros(lista_generos[i].colecao_livros);
                    }
                    printf("Memoria liberada. Ate logo!\n");
                    repetir = 0; 
                    break;
                    
                default:
                    printf("\nOpcao invalida.\n");
                    break;
            }
        }

        if (opc != 0) {
            printf("\n--------------------------------------------------");
            menu_da_repeticao();
            printf("\nDeseja voltar ao menu principal? ");
            repetir = num_inteiro();
            printf("\n");
        }

    } while (opc != 0 && repetir == 1);

    return 0;
}

void menu_das_opcoes() {
    printf("\n============ MENU PRINCIPAL ============\n");
    printf(" 1 - Cadastrar Assinantes\n");
    printf(" 2 - Cadastrar Forma de Assinaturas\n");
    printf(" 3 - Cadastrar Assinaturas\n");
    printf(" 4 - Cadastrar Generos\n");
    printf(" 5 - Cadastrar Livros\n");
    printf("----------------------------------------\n");
    printf(" 6 - Mostrar todos assinantes cadastrados\n");
    printf(" 7 - Mostrar todas as assinaturas cadastradas\n");
    printf(" 8 - Mostrar todas as assinaturas de uma determinada forma\n");
    printf(" 9 - Mostrar todas as formas cadastradas\n");
    printf("10 - Mostrar todos os generos cadastrados\n");
    printf("11 - Mostrar todos os generos assinados\n");
    printf("12 - Mostrar todos os livros de um determinado genero\n");
    printf("13 - Mostrar data de vencimento de uma assinatura\n");
    printf("----------------------------------------\n");
    printf("14 - Remover uma assinatura pelo CPF\n");
    printf("15 - Remover um assinante pelo CPF\n");
    printf(" 0 - Finalizar o sistema\n");
    printf("========================================\n");
}

void menu_da_repeticao() {
    printf("\n 1 - Sim");
    printf("\n 2 - Nao (Finalizar programa)");
}