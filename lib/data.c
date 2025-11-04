#include "../include/data.h"
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

Data* nova_data(int dia, int mes, int ano) {
    if (!data_valida(dia, mes, ano))
        return NULL;

    Data* d = malloc(sizeof(Data));
    if (!d) return NULL;

    d->dia = dia;
    d->mes = mes;
    d->ano = ano;

    return d;
}

Data hoje() {
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    Data d;
    d.dia = now->tm_mday;
    d.mes = now->tm_mon + 1;   // meses são 0..11
    d.ano = now->tm_year + 1900;

    return d;
}

int hoje_serial() {
    time_t now = time(NULL);

    int dias_desde_1970 = now / 86400;
    // Excel começa em 01/01/1900, que em timestamp é 25569 dias antes de 1970
    int base_excel = 25569;

     // Excel incorpora o bug de 29/02/1900 → soma +1
    return dias_desde_1970 + base_excel + 1;
}

int data_to_excel(int dia, int mes, int ano) {
    struct tm dt = {0};
    dt.tm_mday = dia;
    dt.tm_mon  = mes - 1;
    dt.tm_year = ano - 1900;

    time_t t = mktime(&dt);

    return (t / 86400) + 25569 + 1;
}

int data_valida(int dia, int mes, int ano) {
    if (ano <= 0) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1) return false;

    int dias_mes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (eh_bissexto(ano))
        dias_mes[1] = 29;

    return dia <= dias_mes[mes - 1];
}

int data_valida_str(const char *d) {
    int dia  = (d[0]-'0')*10 + (d[1]-'0');
    int mes  = (d[2]-'0')*10 + (d[3]-'0');
    int ano  = (d[4]-'0')*1000 + (d[5]-'0')*100 +
               (d[6]-'0')*10   + (d[7]-'0');

    if (mes < 1 || mes > 12) return 0;
    if (dia < 1) return 0;

    int max_dias = 31;

    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        max_dias = bissexto ? 29 : 28;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        max_dias = 30;
    }

    if (dia > max_dias) return 0;

    if (ano < 1000 || ano > 2099) return 0;

    return 1;
}

int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int dias_no_mes(int mes, int ano) {
    int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (mes == 2 && eh_bissexto(ano)) return 29;
    return dias[mes-1];
}