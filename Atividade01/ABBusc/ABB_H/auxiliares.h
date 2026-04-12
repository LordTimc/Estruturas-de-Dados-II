#ifndef AUXILIARES_H
#define AUXILIARES_h

char *leitura_de_string();
void limpa_dados_buffer();

void pegar_data_de_hoje (data_nasci *data_hoje);
int dias_de_um_mes(int mes, int ano);
int verificar_data(data_nasci *data);

int ler_string_info(char *buffer, int tam);
int converte_data(const char *entrada, data_nasci *data);
int validar_data_com_mensagem(data_nasci *data);
int pega_data_nasci(data_nasci *data_usuario);

int cpf_eh_valido(const char *cpf);
int pega_cpf(char *cpf);

int endereco_eh_valido(const char *endereco);
char *pega_endereco();

int num_eh_valido(const char *num);
int pega_isbn(char *codigo);

int pega_edicao(char *codigo);

#endif