#include <stdio.h>
#include "../include/data.h"
#include "../include/calendario.h"

int serial_1_jan_1900 = 1;

const char* d_semana(int ddd) {
    static const char* nomes[] = {
        "D", "S", "T", "Q", "Q", "S", "S"
    };
    return nomes[ddd % 7];
}

const char* dd_semana(int ddd) {
    static const char* nomes[] = {
        "dom", "seg", "ter", "qua", "qui", "sex", "sab"
    };
    return nomes[ddd % 7];
}

const char* dia_semana(int ddd) {
    static const char* nomes[] = {
        "domingo", "segunda", "terca", "quarta", "quinta", "sexta", "sabado"
    };
    return nomes[ddd % 7];
}

const char* mes(int mm) {
    static const char* nomes[] = {
        "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
        "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
    };
    if (mm < 1 || mm > 12)
        return "Invalido";
    return nomes[mm - 1];
}

// Converte número serial (1 = 01/01/1900) em data gregoriana
void imprimir_data_excel(int serial) {
    int dias_no_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int ano = 1900;
    int dia_restante = serial;

    // Ajuste: Excel considera 1900 como bissexto (erro histórico),
    // mas vamos usar o calendário real.
    while (1) {
        int dias_ano = eh_bissexto(ano) ? 366 : 365;
        if (dia_restante > dias_ano) {
            dia_restante -= dias_ano;
            ano++;
        } else break;
    }

    // Ajustar fevereiro se bissexto
    if (eh_bissexto(ano))
        dias_no_mes[1] = 29;

    int mes = 0;
    while (dia_restante > dias_no_mes[mes]) {
        dia_restante -= dias_no_mes[mes];
        mes++;
    }

    int dia = dia_restante;
    int ddd = serial % 7;
    printf("%04d %02d %02d %03d\n", ano, mes + 1, dia, ddd);
}

int serial_de_data(int dia, int mes, int ano) {
    int s = serial_1_jan_1900;
    for (int y = 1900; y < ano; y++)
        s += eh_bissexto(y) ? 366 : 365;
    for (int m = 1; m < mes; m++)
        s += dias_no_mes(m, ano);
    s += dia - 1;
    return s;
}

// int main() {
//     printf("Data serial 1:   ");  imprimir_data_excel(1);
//     printf("Data serial 60:  ");  imprimir_data_excel(60);
//     printf("Data serial 45123: "); imprimir_data_excel(45123); // exemplo de antes
//     printf("Data serial 45125: "); imprimir_data_excel(45125);
//
//     int mes = 8;  // Agosto
//     int ano = 2023;
//
//     imprimir_calendario(mes, ano);
//
//     return 0;
// }