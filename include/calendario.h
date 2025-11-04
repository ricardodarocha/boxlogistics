#ifndef MODULE_CALENDARIO
#define MODULE_CALENDARIO

const char* d_semana(int ddd);

const char* dd_semana(int ddd);

const char* dia_semana(int ddd);

const char* mes(int mm);

void imprimir_data_excel(int serial);

int serial_de_data(int dia, int mes, int ano);

void imprimir_calendario(int mes, int ano);

#endif
