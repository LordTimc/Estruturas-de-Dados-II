#ifndef AUXILIARES_H
#define AUXILIARES_h

char *leitura_de_string();
void limpa_dados_buffer();

void pegar_data_de_hoje (Data *data_hoje);
int dias_de_um_mes(int mes, int ano);
int verificar_data(Data *data);

int ler_string_info(char *buffer, int tam);
int converte_data(const char *entrada, Data *data);
int validar_data_com_mensagem(Data *data);
int pega_data_nasci(Data *data_usuario);
int pega_data(Data *data_usuario);

int cpf_eh_valido(const char *cpf);
int pega_cpf(char *cpf);

int endereco_eh_valido(const char *endereco);
char *pega_endereco();

int num_eh_valido(const char *num);
int pega_isbn(char *codigo);

int num_inteiro();
float num_decimal();

#endif