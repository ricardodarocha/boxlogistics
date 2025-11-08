#include <stdlib.h>
#include <stdio.h>
#include "../app/config.h"
#include "../include/fila.h"

typedef struct Carga{
    int id;
    int data;
    char nome[SIZES];
    float valor;
} Carga;

static int proxima_carga = 0;

int cursor_proxima_carga(void) {
    return proxima_carga;
}

void imprimir_cabecalha_carga() {
    printf("  %3s %-49s %9s\n%s", "id", "nome", "valor",
                    "───────────────────────────────────────────────────────────────────\n");
}

void iprimir_carga(void *dado) {
    Carga * p= dado;
    printf("  %03d %-49s %9.2f\n", p->id, p->nome, p->valor );
}

int localizar_carga(void *a, void *b) {
    Carga *pa = a, *pb = b;
    return pa->id == pb->id ? FOUND : NOTFOUND;
}

int validar_carga(void *dado) {
    Carga * p= dado;

    //pode ser criada uma validacao personalizada
    return VALID;
}

Carga *alocar_carga(void) {
    Carga *carga = malloc(sizeof(Carga));
    if (!carga) {
        perror("malloc");
        return NULL;
    }

    // Valores padrao
    carga->id = proxima_carga += 1;
    carga->nome[0] = '\0';
    carga->valor = 0.0f;

    return carga;
}


