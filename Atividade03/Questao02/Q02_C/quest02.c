#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMERO_DISCOS 5  // Numero de discos
#define NUMERO_PINOS 3
#define MAX 243 // NUMERO_PINOS ^ NUMERO_DISCOS

typedef struct nodo_lista {
    int vertice;
    struct nodo_lista *proximo;
} nodo_lista;

typedef struct {
    nodo_lista *cabeca;
    int grau;
} lista_adj_t;

lista_adj_t lista_adj[MAX]; // Lista de adjacencia global

//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#define NUMERO_DISCOS 5  // Numero de discos
#define NUMERO_PINOS 3
#define MAX 243 // NUMERO_PINOS ^ NUMERO_DISCOS

typedef struct {
    int configuracao[NUMERO_DISCOS]; // Configuracao dos discos nos pinos
} GRAFO;

//-----------------------------------------------
// Estruturas da Lista de Adjacencia

typedef struct nodo_lista {
    int vertice;
    struct nodo_lista *proximo;
} nodo_lista;

typedef struct {
    nodo_lista *cabeca;
    int grau;
} lista_adj_t;

lista_adj_t lista_adj[MAX]; // Lista de adjacencia global

//-----------------------------------------------
// Gera todas as configuracoes possiveis dos discos
void gerar_configuracoes(GRAFO *grafo) {
    for (int i = 0; i < MAX; ++i) {
        int numero_base = i;
        for (int j = 0; j < NUMERO_DISCOS; ++j) {
            grafo[i].configuracao[j] = numero_base % NUMERO_PINOS + 1;
            numero_base /= NUMERO_PINOS;
        }
    }
}

//-----------------------------------------------
// Verifica se há uma aresta válida entre duas configurações
int eh_aresta(GRAFO config1, GRAFO config2) {
    int diferenca_discos = 0;
    int disco_alterado = -1;
    int valida = 1; // Assume que a aresta é válida por padrão

    for (int i = 0; i < NUMERO_DISCOS; ++i) {
        if (config1.configuracao[i] != config2.configuracao[i]) {
            diferenca_discos++;
            disco_alterado = i;
        }
    }

    valida = (diferenca_discos == 1);

    if (valida) {
        for (int i = 0; i < NUMERO_DISCOS; ++i) {
            if (i != disco_alterado && i < disco_alterado) {
                if (config1.configuracao[i] == config1.configuracao[disco_alterado] || config2.configuracao[i] == config2.configuracao[disco_alterado])
                    valida = 0;
            }
        }
    }

    return valida;
}

//-----------------------------------------------
// Inicializa a lista de adjacencia (todos os nodos como NULL)
void inicializar_lista_adj() {
    for (int i = 0; i < MAX; i++) {
        lista_adj[i].cabeca = NULL;
        lista_adj[i].grau   = 0;
    }
}

//-----------------------------------------------
// Libera a memoria alocada pela lista de adjacencia
void liberar_lista_adj() {
    for (int i = 0; i < MAX; i++) {
        nodo_lista *atual = lista_adj[i].cabeca;
        while (atual != NULL) {
            nodo_lista *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        lista_adj[i].cabeca = NULL;
        lista_adj[i].grau   = 0;
    }
}

//-----------------------------------------------
// Preenche a lista de adjacencia a partir das configuracoes
// Regra da saida unica: um unico ponto de retorno ao final da funcao
void gerar_lista_adj(GRAFO *grafo) {
    int erro = 0; // flag de controle para saida unica

    inicializar_lista_adj();

    for (int i = 0; i < MAX && !erro; i++) {
        for (int j = 0; j < MAX && !erro; j++) {
            if (eh_aresta(grafo[i], grafo[j])) {
                nodo_lista *novo = (nodo_lista *)malloc(sizeof(nodo_lista));
                if (novo == NULL) {
                    fprintf(stderr, "Erro: falha na alocacao de memoria.\n");
                    liberar_lista_adj();
                    erro = 1; // marca erro e encerra os loops
                } else {
                    novo->vertice  = j;
                    novo->proximo  = lista_adj[i].cabeca;
                    lista_adj[i].cabeca = novo;
                    lista_adj[i].grau++;
                }
            }
        }
    }
    // unico ponto de saida da funcao
}

//-----------------------------------------------
// Imprime a lista de adjacencia gerada
void imprimir_lista_adj() {
    for (int i = 0; i < MAX; i++) {
        printf("Vertice %d (grau %d): ", i, lista_adj[i].grau);
        for (nodo_lista *no = lista_adj[i].cabeca; no != NULL; no = no->proximo)
            printf("%d ", no->vertice);
        printf("\n");
    }
}

//-----------------------------------------------

int main() {
    GRAFO grafo[MAX];

    gerar_configuracoes(grafo);
    gerar_lista_adj(grafo);

    imprimir_lista_adj();

    liberar_lista_adj();

    return 0;
}