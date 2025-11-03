#include <stdio.h>
#include "cadastros.h"

void print_kpi_card(const char *icon, const char *nome, const char *valor, const char arrow) {
    printf("╔══════════════════════╗\n");
    printf("║  %s %-16s  \n"            , icon, nome);
    printf("║  Valor: %-10s %c  \n"     , valor, arrow);
    printf("╚══════════════════════╝\n\n");
}

void print_kpis_value(const char *icon, const char *nome, float valor, const char arrow) {
    char str_buffer[20];
    sprintf(str_buffer, "%5f", valor);
    print_kpi_card(icon, nome,   str_buffer, arrow);
}

void print_kpi_produtos() {
    print_kpis_value("☻", "produtos",  qtd_produtos(), 30 );
}
void print_kpi_entregas() {
    print_kpis_value("◙", "entregas",  qtd_entregas(), 31 );
}
void print_kpi_cargas() {
    print_kpis_value("♫", "cargas",  qtd_cargas(), 31 );
}
void print_kpi_vendas() {
    print_kpis_value("§", "vendas",  qtd_vendas(), 31 );
}

void print_kpis() {
    print_kpi_produtos();
    print_kpi_entregas();
    print_kpi_cargas();
    print_kpi_vendas();
}