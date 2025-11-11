#ifndef TFINAL_DATA_H
#define TFINAL_DATA_H

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

Data* nova_data(int dia, int mes, int ano);
Data hoje();
int hoje_serial();
int data_valida(int dia, int mes, int ano);
int data_valida_str(const char *d);
void input_data_valid(const char *title, char *out[10]);
int data_to_excel(int dia, int mes, int ano);
int eh_bissexto(int ano);
int dias_no_mes(int mes, int ano);

#endif