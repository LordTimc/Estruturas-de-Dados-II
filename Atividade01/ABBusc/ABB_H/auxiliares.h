#ifndef AUXILIARES_H
#define AUXILIARES_h

char *leitura_de_string();

void pegar_data_de_hoje (data_nasci *data_hoje);
int dias_de_um_mes(int mes, int ano);
int data_valida(data_nasci *data);
int ler_string_info(char *buffer, int tam);
int converte_data(const *entrada, data_nasci *data);
int pega_data_nasci(data_nasci *data_usuario);

#endif