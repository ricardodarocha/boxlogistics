#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../app/config.h"

typedef struct {
    int id;
    int id_produto;
    float valor;
    float quant;
    char destinatario[SIZES]; //nome do destinatario
    // char cpf[SIZES];
    int cpf;
} Entrega;

static int proxima_entrega = 0; //id do proximo codigo que sera gerado pelo sistema = proximo_entrega + 1

int cursor_proxima_entrega( ) {
    return proxima_entrega;
}

void imprimir_cabecalho_entrega() {

    // ╔═════════════════════════════════════════════════════════════════════╗
    // ║                        entrega 1                                    ║
    //  ─────────────────────────────────────────────────────────────────────
    // ║ BOX LOGISTICS                                (Versão 0.1 2025)      ║
    //  ─────────────────────────────────────────────────────────────────────
    //   001    produto asda                                       3000
    //   002    produto jasdjka                                    3000
    // ╚═════════════════════════════════════════════════════════════════════╝
    //   3 volumes                                   titak          303033
    // ╚═════════════════════════════════════════════════════════════════════╝

    // printf("  %3s %-49s %9s\n", "  id", "nome", "quant" );
}

int localizar_entrega(void *a, void *b) {
    Entrega *pa = a, *pb = b;
    return pa->id == pb->id ? FOUND : NOTFOUND;
}

int validar_entrega(void *dado) {
    Entrega * e= dado;

    //pode ser criada uma validacao personalizada
    return VALID;
}

Entrega *alocar_entrega(void) {
    Entrega *entrega = malloc(sizeof(Entrega));
    if (!entrega) {
        perror("Erro ao alocar Entrega");
        return NULL;
    }

    entrega->id = ++proxima_entrega;

    entrega->id_produto = 0;
    entrega->destinatario[0] = '\0';
    entrega->cpf = 0;
    entrega->quant = 1.0f;
    entrega->valor = 1.0f;

    return entrega;
}