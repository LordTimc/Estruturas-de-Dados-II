#include "structs.h"

// Função para alocar a forma de assinatura
forma_ass *aloca_forma_assinatura();

// Função para criar o vetor de códigos dentro da struct
int *alocar_vetor_generos(int qtd);

// Função para inserir um nó já pronto na lista
forma_ass* inserir_na_lista(forma_ass* lista, forma_ass* novo);

// Função para cadastrar uma nova forma de assinatura na lista dinâmica
forma_ass* cad_forma_assinatura(forma_ass *lista, int qtd_generos_sistema);

// Função para mostrar assinaturas filtradas por um código de forma específico
void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_forma); /////////////

// Função para mostrar todas as formas de assinatura cadastradas
void mostrar_formas_assinatura(forma_ass *lista);