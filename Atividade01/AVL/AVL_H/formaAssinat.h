#ifndef FORMA_ASSINATURA_H
#define FORMA_ASSINATURA_H

#include "../AVL_H/structs.h"

forma_ass *aloca_forma_assinatura();
int *alocar_vetor_generos(int qtd);
forma_ass *inserir_na_lista(forma_ass* lista, forma_ass* novo);
forma_ass *cad_forma_assinatura(forma_ass *lista, int qtd_generos_sistema);
void mostrar_assinaturas_por_forma(Assinatura *raiz, int codigo_busca); 
void mostrar_formas_assinatura(forma_ass *lista);

#endif