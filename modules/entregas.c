#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../app/config.h"

typedef struct {
    int id;
    int id_produto;
    float valor;
    float quant;
    float total;
    char destinatario[SIZES]; //nome do destinatario
    // char cpf[SIZES];
    int cpf;
} Entrega;

static int proxima_entrega = 0; //id do proximo codigo que sera gerado pelo sistema = proximo_entrega + 1

int cursor_proxima_entrega( ) {
    return proxima_entrega;
}

void imprimir_entrega(void *dado) {
    Entrega *e = dado;
    printf("  │ %02d │ %-40s│ %10.2f    │\n",
           e->id, e->destinatario, e->valor);
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
    entrega->total = 1.0f;

    return entrega;
}

Entrega *nova_entrega(char *destinatario, int id_produto, float valor, float quant, int cpf) {
    Entrega * result = alocar_entrega();
    strcpy(result->destinatario, destinatario);
    result->id_produto = id_produto;
    result->valor = valor;
    result->quant = quant;
    result->total = quant  * valor;
    result->cpf = cpf; //todo! inserir CPF como string
    return result;
}

int validar_entrega(void* dado, char* message) {
    Entrega *e = dado;
    if (e->valor <= 0) {
        strcpy(message, "Informe um valor");
        return INVALID;
    }
    if (e->quant <= 0) {
        strcpy(message, "Informe uma quantidade");
        return INVALID;
    }
    if (e->cpf == 0) {
        strcpy(message, "Informe um cpf");
        return INVALID;
    }
    return VALID;
}
