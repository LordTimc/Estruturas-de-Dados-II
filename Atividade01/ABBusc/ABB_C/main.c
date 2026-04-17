#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ABB_H/assinantes.h"
#include "../ABB_H/assinaturas.h"
#include "../ABB_H/formaAssinat.h"
#include "../ABB_H/generos.h"
#include "../ABB_H/livros.h"

#include "../ABB_H/structs.h"
#include "../ABB_H/auxiliares.h"

void menu_das_opcoes(){
    printf("\n 1 - Cadastrar Assinantes\n");
    printf("\n 2 - Cadastrar Forma de Assinaturas\n");
    printf("\n 3 - Cadastrar Assinaturas\n");
    printf("\n 4 - Cadastrar Generos\n");
    printf("\n 5 - Cadastrar Livros\n");
    printf("\n 6 - Mostrar todos assinantes cadastrados\n");
    printf("\n 7 - Mostrar todas as assinaturas cadastrada\n");
    printf("\n 8 - Mostrar todas as assinaturas de um determinada forma\n");
    printf("\n 9 - Mostrar todas as formas cadastradas e seus respectivos valores mensais e anuais\n");
    printf("\n 10 - Mostrar todos os generos cadastrados\n");
    printf("\n 11 - Mostrar todos os generos assinados\n");
    printf("\n 12 - Mostrar todos os livros de um determinado gênero\n");
    printf("\n 13 - Mostrar data de vencimento de uma assinatura\n");
    printf("\n 14 - Remover uma assinatura dado o CPF do assinante\n");
    printf("\n 15 - Remover um assinante pelo CPF do assinante\n");
    printf("\n 0 - Finalizar tudo\n");
}

void menu_da_repeticao(){
    printf("\n 1 - Sim");
    printf("\n 2 - Nao");
}

void menu(){
    Assinante *raiz_assinante, *no_assinante;
    raiz_assinante = NULL;
    no_assinante = NULL;

    Assinatura *raiz_assinatura, *no_assinatura;
    raiz_assinatura = NULL;
    no_assinatura = NULL;

    forma_ass *lista_forma, *no_forma;
    lista_forma = NULL;
    no_forma = NULL;

    int opc, repetir, resposta = 0;
    do{
        menu_das_opcoes();
        printf("Escolha uma opcao: ");
        opc = num_inteiro();
        menu_da_repeticao();
        repetir = num_inteiro();

        if(repetir == 1){
            switch (opc)
            {
            case 1:
                /*Cadastrar Assinantes: cadastrar dados de assinantes organizados em uma árvore binária pelo CPF do assinante, um usuário pode cadastrar um assinante a qualquer momento, não permita cadastro repetido.*/
                no_assinante = cadastrar_assinante(&no_assinante);
                if(no_assinante == NULL)
                    printf("\nErro na alocacao de memoria.\n");
                else{
                    resposta = inserir_assinante(&raiz_assinante, no_assinante);
                    if(resposta == 1)
                        printf("\nO assinante foi cadastrado.\n");
                    else
                        printf("\nAssinante nao cadastrado, pois eh repetido\n");
                }
                break;
            case 2:
            {
                /*Cadastrar Forma de Assinaturas: cadastrar dados da lista dinâmica da forma de assinaturas, quantidade livros mensais, quantidade de gêneros mensais, gêneros escolhidos, tipo de encadernação, valor mensal e valor anual. Lembre-se que para cadastrar uma forma de assinatura o usuário já deve ter cadastrado pelo menos um tipo de gênero, não permita cadastro repetido.*/
            }
                break;
            case 3:
            {
                /*Cadastrar Assinaturas: cadastrar dados de assinaturas organizados em uma árvore binária pelo CPF do assinante, um usuário pode cadastrar uma assinatura a qualquer momento, não permita cadastro repetido. Lembre-se que para cadastrar uma assinatura o usuário já deve ter cadastrado o assinante e uma lista dinâmica forma de assinaturas, não permita cadastro repetido.
*/
            }
            case 4:
            {

            }
            case 5:
            {

            }
            case 6:
            {

            }
            case 7:{

            }
            case 8:
            {

            }
            case 9:
            {

            }
            case 10:
            {

            }
            case 11:
            {

            }
            case 12:
            {

            }
            case 13:
            {

            }
            case 14:{

            }
            case 15:
            {

            }
            case 0:
            {
                printf("\nFechando o progrando em 3, 2, 1...\n");
                liberar_arvore_usuario(raiz_assinante);
                liberar_arvore_assinaturas(raiz_assinatura);

                for (int i = 0; i < MAX_GENEROS; i++) {
                    liberar_arvore_livros(lista_generos[i].colecao_livros);
                }
                liberar_lista_formas(lista_forma);

                printf("\nMemoria liberada\nFechando o programa...");
            }
            default:
                printf("\nOpcao invalida\n");
                break;
            }
        }
    }while(opc != 0 || repetir == 0);
}