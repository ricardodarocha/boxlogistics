#include <stdlib.h>
#include <stdio.h>
#include "../app/config.h"

typedef struct {
    int id;
    char nome[SIZES];
    int cpf; //todo! change cpf to *char
} Cliente;

static int proximo_cliente = 0; //id do proximo codigo que sera gerado pelo sistema = proximo_cliente + 1

int cursor_proximo_cliente(void) {
    return proximo_cliente;
}

void imprimir_cabecalho_cliente() {
    printf("  %3s %-49s %9s", "id", "nome", "cpf");
    printf("\n ═══════════════════════════════════════════════════════════════════\n" );
}

void iprimir_cliente(void *dado) {
    Cliente * p = dado;
    printf("  %03d %-40s ***9-%002d***\n", p->id, p->nome, p->cpf );
}

int localizar_cliente(void *a, void *b) {
    Cliente *pa = a, *pb = b;
    return pa->id == pb->id ? FOUND : NOTFOUND;
}

int localizar_cpf(void *a, void *b) {
    Cliente *pa = a, *pb = b;
    return pa->cpf == pb->cpf ? FOUND : NOTFOUND;
}

int validar_cliente(void *dado) {
    Cliente * p= dado;

    //return validar_cpf(p->cpf);
    return VALID;
}

Cliente *alocar_cliente(void) {
    Cliente *cliente = malloc(sizeof(Cliente));
    if (!cliente) {
        perror("malloc");
        return NULL;
    }

    // Valores padrao
    cliente->id = proximo_cliente += 1;
    cliente->nome[0] = '\0';
    cliente->cpf = cliente->id+18; //um valor aleatorio

    return cliente;
}