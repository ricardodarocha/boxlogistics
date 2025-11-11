#ifndef MODULE_CALENDARIO
#define MODULE_CALENDARIO

const char* d_semana(int ddd);

const char* dd_semana(int ddd);

const char* dia_semana(int ddd);

const char* mes(int mm);

void imprimir_data_excel(int serial);

int serial_de_data(int dia, int mes, int ano);

#define SIZEDATE 11

char* formatar_data(int serial);

int serial_de_data_str(const char *data_str[SIZEDATE]);

#endif
