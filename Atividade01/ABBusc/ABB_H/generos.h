#include "structs.h"

// Função para criar um novo gênero na lista estática não ordenada
Genero criar_genero(int codigo_livro, char *nome_genero);

// Função para inserir o genero na lista estática
int inserir_genero(Genero lista[], int *qtd_gen, Genero novo_genero);

// Função para verificar se o genero já existe
int existe_livro_cad(Genero lista[], int qtd_gen, int codigo_livro);

// Função para mostrar todos os gêneros cadastrados na lista estática
void mostrar_generos(Genero lista[], int qtd);



// Função auxiliar para varrer a árvore de assinaturas e marcar os gêneros encontrados
void marcar_generos_assinados(Assinatura *raiz, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos, int marcados[]);

// Função principal para exibir os gêneros assinados
void mostrar_generos_assinados(Assinatura *raiz_assinaturas, forma_ass *lista_formas, Genero lista_generos[], int qtd_generos);

// ----- Ver se encaixa no main: EXISTE_LIVRO_CAD ---- 
// // No seu código principal:
// if (!existe_codigo(lista_generos, total_generos, novo_codigo)) {
//     cadastrar_genero_estatico(lista_generos, &total_generos, novo_codigo, "Nome");
// } else {
//     printf("Erro: Código duplicado!");
// }

// ----- Ver se encaixa no main: INSERIR_GENERO_ESTATICO ----
// ... dentro do main ou de uma função de controle
// Genero g1 = criar_genero(1, "Ficcao Cientifica");

// if (inserir_genero_estatico(meu_vetor, &quantidade, g1)) {
//     printf("Genero inserido com sucesso!\n");
// }

// ----- Ver se encaixa no main: MOSTRAR_GENEROS ----
/*int main() {
    Genero meus_generos[MAX_GENEROS];
    int total = 0;

    // ... após realizar alguns cadastros ...
    
    listar_generos(meus_generos, total);

    return 0;
}*/ 