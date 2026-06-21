#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMERO_PINOS 3
#define NUMERO_DISCOS 5  // Numero de discos
#define MAX 243 // NUM_PINOS ^ NUM_DISCOS

typedef struct grafo{
    int configuracao[NUMERO_DISCOS]; // Configuracao dos discos nos pinos
} GRAFO; 

int matriz_adjacen[MAX][MAX]; // Matriz de adjacencia

//-----------------------------------------------
// Gera todas as configuracoes possiveis dos discos
void gerar_configuracoes(GRAFO *grafo) {
    // Percorre todos os vertices/estados possiveis do grafo (de 0 ate MAX-1)
    for (int i = 0; i < MAX; ++i) {
        int numero_base = i; // Copia o indice atual para ser decomposto
        // Determina a posicao de cada disco para a configuracao atual
        for (int j = 0; j < NUMERO_DISCOS; ++j) {
            // Mapeia o pino do disco j usando o resto da divisao (conversao de base)
            grafo[i].configuracao[j] = numero_base % NUMERO_PINOS + 1;
            // Desloca para o proximo digito/disco dividindo pelo numero de pinos
            numero_base /= NUMERO_PINOS;
        }
    }
}

//-----------------------------------------------
// Verifica se ha uma aresta valida entre duas configuracoes
int eh_aresta(GRAFO config1, GRAFO config2) {
    int diferenca_discos = 0;
    int disco_alterado = -1;
    int valida = 1; // Assume que a aresta e valida por padrao

    // Compara as duas configuracoes disco por disco
    for (int i = 0; i < NUMERO_DISCOS; ++i) {
        if (config1.configuracao[i] != config2.configuracao[i]) {
            diferenca_discos++; // Conta quantos discos mudaram de lugar
            disco_alterado = i; // Guarda o indice do ultimo disco alterado
        }
    }

    // Regra 1: O movimento so eh valido se exatamente 1 disco mudou de posicao
    if(diferenca_discos == 1){
        valida = 1;
    } else {
        valida = 0;
    }

    // Regra 2: Se passou na primeira regra, checa as restricoes de tamanho
    if (valida) {
        for (int i = 0; i < NUMERO_DISCOS; ++i) {
            // Procura por discos menores (i < disco_alterado) que o disco movido
            if (i != disco_alterado && i < disco_alterado) { 
                // Se um disco menor ja estava no pino de origem ou de destino, o movimento e invalido
                if (config1.configuracao[i] == config1.configuracao[disco_alterado] || config2.configuracao[i] == config2.configuracao[disco_alterado])
                    valida = 0; 
            }
        }
    }
    
    return valida; // Retorna 1 se o movimento for valido ou 0 se for invalido
}

//-----------------------------------------------
// Preenche a matriz de adjacencia do grafo
void gerar_adjacencias(GRAFO *grafo) {
    // Percorre todas as linhas da matriz (configuracao de origem i)
    for (int i = 0; i < MAX; ++i) {
        // Percorre todas as colunas da matriz (configuracao de destino j)
        for (int j = 0; j < MAX; ++j)
            // Testa se a transicao entre i e j e valida e guarda o resultado (0 ou 1)
            matriz_adjacen[i][j] = eh_aresta(grafo[i], grafo[j]);
    }
}
//-----------------------------------------------

// Imprime o caminho minimo encontrado
void imprimir_caminho(int *pesos, int origem, int destino) {
    printf("\nCaminho minimo entre configuracoes %d e %d:\n", origem, destino);

    // Vetor auxiliar para armazenar a sequencia de vertices do caminho
    int caminho[destino + 1], temp = pesos[destino], pos = 0;

    // Reconstrói o caminho de tras para frente usando o vetor de predecessores (pesos)
    while(temp != -1)
        // Guarda o vertice atual no vetor e avanca para o pai/antecessor dele
        temp = pesos[caminho[pos++] = temp];

    // Imprime os vertices na ordem correta (do inicio ate o penultimo)
    for (int i = pos - 1; i >= 0; i--)
        printf("%d ", caminho[i]);

    // Imprime o vertice de destino para fechar o caminho
    printf("%d\n", destino);

    // Exibe o total de passos dados para alcancar o objetivo
    printf("Quantidade de movimentos: %d\n", pos);
}

//-----------------------------------------------
// Implementacao do algoritmo de Dijkstra
int* dijkstra(int origem) {
    static int menor_caminho[MAX], pesos[MAX]; // Vetores de distancias e de predecessores (pais)
    int visitado[MAX] = {0}; // Marca os vertices cujo menor caminho ja foi fechado

    memset(pesos, -1, sizeof(pesos)); // Inicializa todos os predecessores como -1 (nenhum)
    for (int i = 0; i < MAX; i++) menor_caminho[i] = 99999999; // Define que a distancia inicial para todas as configuracoes eh "infinita"

    menor_caminho[origem] = 0; // A distancia do vertice de origem para ele mesmo e zero

    // Laco principal para visitar todos os vertices do grafo
    for (int i = 0; i < MAX; ++i) {
        int u = -1, min_dist = 99999999;
        // u é o vertice atual, ou seja, o ponto onde o algoritmo está posicionado naquela iteracao.
        
        // Encontra o vertice nao visitado que possui a menor distancia atual
        for (int j = 0; j < MAX; ++j) {
            if (!visitado[j] && menor_caminho[j] < min_dist) {
                min_dist = menor_caminho[j];
                u = j;
            }
        }

        visitado[u] = 1; // Marca o vertice escolhido como visitado/processado

        // Atualiza a distancia dos vizinhos 'v' do vertice atual 'u'. 
        for (int v = 0; v < MAX; ++v) {
            // Se existe aresta entre u e v, e o caminho passando por u for menor que o atual de v
            if (matriz_adjacen[u][v] == 1 && menor_caminho[u] + matriz_adjacen[u][v] < menor_caminho[v]) {
                menor_caminho[v] = menor_caminho[u] + matriz_adjacen[u][v]; // Atualiza o menor custo para chegar em v
                pesos[v] = u;                             // Define 'u' como o antecessor/pai de 'v'
            }
        }
    }
    return pesos; // Retorna o vetor de predecessores para remontar o caminho depois
}

//-----------------------------------------------
// Imprime todas as configuracoes dos vertices do grafo
void imprimir_grafo(GRAFO *grafo) {
    printf("\n");
    
    // Percorre todos os vertices (configuracoes) do grafo
    for (int i = 0; i < MAX; ++i) {
        printf("Configuracao %d: ", i);
        
        // Percorre e imprime os discos de cada configuracao especifica
        for (int j = 0; j < NUMERO_DISCOS; ++j) {
            printf("%d ", grafo[i].configuracao[j]);
        }
        printf("\n"); // Pula linha apos exibir a configuracao atual
    }
}
//-----------------------------------------------
// Imprime a matriz de adjacencia
void imprimir_matriz_adjacencia() {
    printf("\nMatriz de Adjacencia:\n");
    printf("   ");
    
    // Imprime o cabecalho com o indice das colunas
    for (int i = 0; i < MAX; i++)
        printf("%2d ", i);

    printf("\n");
    // Percorre as linhas da matriz
    for (int i = 0; i < MAX; i++) {
        printf("%2d ", i); // Imprime o indice da linha atual
        
        // Percorre e imprime as conexoes (arestas) de cada coluna
        for (int j = 0; j < MAX; j++)
            printf("%2d ", matriz_adjacen[i][j]);
            
        printf("\n"); // Pula de linha ao terminar a linha atual da matriz
    }
}
//-----------------------------------------------

void testes_tempo(int origem) {
    printf("\n==== TESTES DE TEMPO ====\n");
    int num_testes = 1000;
    double tempo_dijkstra = 0.0;
    printf("Realizando %d testes...\n", num_testes);

    int i;
    // Executa o algoritmo repetidas vezes para obter uma media estavel
    for (i = 0; i < num_testes; i++) {
        clock_t inicio = clock(); // Registra o instante inicial do teste
        dijkstra(origem);         // Executa a funcao que sera avaliada
        clock_t fim = clock();    // Registra o instante final do teste
        
        // Calcula a duracao em milissegundos e acumula no tempo total
        tempo_dijkstra += ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    }

    // Exibe os resultados consolidados do benchmark
    printf("\nTempo total Dijkstra: %.6f ms\n", tempo_dijkstra);
    printf("Tempo medio Dijkstra: %.6f ms\n", tempo_dijkstra / num_testes);
    printf("\n==== FIM DOS TESTES ====\n");
}

int main() {
    GRAFO grafo[MAX];

    gerar_configuracoes(grafo);
    gerar_adjacencias(grafo);

    int opcao;
    int origem = 0; // Configuração de origem
    int destino = MAX - 1;

    do {
        printf("\n\n==== MENU ====\n");
        printf("1. Imprimir configuracoes do grafo\n");
        printf("2. Imprimir matriz de adjacencia\n");
        printf("3. Encontrar caminho minimo com Dijkstra\n");
        printf("4. Testes de tempo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                imprimir_grafo(grafo);
                break;
            case 2:
                system("cls");
                imprimir_matriz_adjacencia();
                break;
            case 3:{
                system("cls");
                int *pesos;

                printf("Encontrando caminho minimo com Dijkstra...\n");

                clock_t inicio = clock();  // Marca o tempo de início
                pesos = dijkstra(origem);

                clock_t fim = clock();     // Marca o tempo de fim

                imprimir_caminho(pesos, origem, destino);
                double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000; // Tempo em milissegundos
                printf("Tempo de execucao (Dijkstra): %.6f ms\n", tempo_execucao);
                break;
            }
            
            case 4:{
                testes_tempo(origem);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}