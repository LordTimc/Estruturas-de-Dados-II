#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100 // Defina o limite de vértices do seu grafo

// Função para encontrar o vértice com a maior probabilidade que ainda não foi processado
int maxProbabilityVertex(double prob[], bool visitados[], int V) {
    double max_prob = -1.0;
    int max_index = -1;

    for (int v = 0; v < V; v++) {
        if (visitados[v] == false && prob[v] > max_prob) {
            max_prob = prob[v];
            max_index = v;
        }
    }
    return max_index;
}

// Função para imprimir o caminho percorrido recursivamente
void imprimirCaminho(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }
    imprimirCaminho(parent, parent[j]);
    printf("-> %d ", j);
}

// Algoritmo de Dijkstra modificado para Caminho Mais Confiável
void caminhoMaisConfiavel(double grafo[MAX_VERTICES][MAX_VERTICES], int origem, int destino, int V) {
    double prob[MAX_VERTICES];  // prob[i] guarda a maior confiabilidade da origem até i
    bool visitados[MAX_VERTICES]; // visitados[i] é true se o vértice i já foi processado
    int parent[MAX_VERTICES];   // Array para reconstruir o caminho

    // Inicialização
    for (int i = 0; i < V; i++) {
        prob[i] = 0.0;
        visitados[i] = false;
        parent[i] = -1;
    }

    // A confiabilidade da origem para ela mesma é 1.0 (100%)
    prob[origem] = 1.0;

    // Encontra o caminho mais confiável para todos os vértices
    for (int count = 0; count < V - 1; count++) {
        // Escolhe o vértice com a maior probabilidade atual
        int u = maxProbabilityVertex(prob, visitados, V);

        // Se o grafo for desconectado ou o destino for inalcançável
        if (u == -1) break; 

        visitados[u] = true;

        // Se já processamos o destino, podemos parar cedo (otimização)
        if (u == destino) break;

        // Atualiza o valor de probabilidade dos vértices adjacentes
        for (int v = 0; v < V; v++) {
            // Atualiza se: não foi visitado, existe aresta, e o novo caminho multiplicando as
            // probabilidades for maior que a probabilidade conhecida até o momento
            if (!visitados[v] && grafo[u][v] > 0.0) {
                if (prob[u] * grafo[u][v] > prob[v]) {
                    prob[v] = prob[u] * grafo[u][v];
                    parent[v] = u; // Guarda o pai para traçar a rota depois
                }
            }
        }
    }

    // Saída de dados
    if (prob[destino] == 0.0) {
        printf("Nao existe um caminho entre os vertices %d e %d.\n", origem, destino);
    } else {
        printf("A confiabilidade maxima do caminho do vertice %d ate o vertice %d e: %f\n", origem, destino, prob[destino]);
        printf("Caminho mais confiavel: ");
        imprimirCaminho(parent, destino);
        printf("\n");
    }
}

int main() {
    int V = 5; // Número de vértices

    // Criando um grafo de exemplo em formato de Matriz de Adjacência
    // 0.0 significa que não há conexão direta (aresta)
    double grafo[MAX_VERTICES][MAX_VERTICES] = {0.0};

    // Populando as arestas com suas probabilidades de confiabilidade r(u,v)
    grafo[0][1] = 0.9;
    grafo[0][2] = 0.5;
    grafo[1][2] = 0.8;
    grafo[1][3] = 0.2;
    grafo[2][3] = 0.9;
    grafo[2][4] = 0.4;
    grafo[3][4] = 0.8;

    int origem, destino; // Agora apenas declaramos as variáveis

    // Interagindo com o usuário
    printf("Digite o vertice de origem (0 a %d): ", V - 1);
    scanf("%d", &origem);

    printf("Digite o vertice de destino (0 a %d): ", V - 1);
    scanf("%d", &destino);

    // Verificação básica para evitar que o usuário digite vértices que não existem
    if (origem < 0 || origem >= V || destino < 0 || destino >= V) {
        printf("Erro: Vertice invalido. Por favor, digite valores entre 0 e %d.\n", V - 1);
        return 1; // Encerra o programa com erro
    }

    caminhoMaisConfiavel(grafo, origem, destino, V);

    return 0;
}