#include "../app/config.h"
#include "../include/fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;
    // char cliente[SIZES];
    char datastr[SIZES];
    int data;
    char nome[SIZES];
    float valor;
    // float total;
    void * fila;
} Venda;

static int proxima_venda = 0;

int cursor_proxima_venda(void) {
    return proxima_venda;
}

Venda *alocar_venda() {
    Venda *v = malloc(sizeof(Venda));
    if (!v) return NULL;

    v->id = 0;
    v->nome[0] = '\0';
    v->datastr[0] = '\0';
    v->data  = 0;
    v->valor = 0.0f;

    v->entregas = criarFila();  // lista de entregas

    return v;
}

// ---------------------------------------------------------
// ADICIONAR ENTREGA A VENDA
// ---------------------------------------------------------
void venda_adicionar_entrega(Venda *v, Entrega *e) {
    if (!v || !e) return;

    enfileirar(v->entregas, e);

    // Atualiza total da venda automaticamente
    v->valor += (e->valor * e->quant);
}

// ---------------------------------------------------------
// IMPRESSÃO SIMPLES (para depuração / árvore)
// ---------------------------------------------------------
void imprimir_venda(void *dado) {
    Venda *v = dado;

    printf("Venda %d | Cliente: %s | Data: %s | Total R$ %.2f\n",
        v->id,
        v->nome,
        v->data,
        v->valor
    );
}

// ---------------------------------------------------------
// RELATÓRIO BONITO DA VENDA COMPLETA
// ---------------------------------------------------------
void imprimir_relatorio_venda(Venda *v) {
    if (!v) return;

    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║                       VENDA n° %04d                      ║\n", v->id);
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ Cliente: %-45s ║\n", v->nome);
    printf("║ Data:    %-45s ║\n", v->data);
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ ITENS DA VENDA                                           ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ ID   Destinatário                    Quant.    Valor     ║\n");
    printf("║ -------------------------------------------------------- ║\n");

    float total = 0.0f;

    for (FilaX *cur = v->entregas->inicio; cur; cur = cur->proximo) {
        Entrega *e = cur->dado;
        float subtotal = e->valor * e->quant;

        printf("║ %-4d %-28s %7.2f %10.2f ║\n",
            e->id,
            e->destinatario,
            e->quant,
            subtotal
        );

        total += subtotal;
    }

    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ TOTAL%45s R$ %8.2f ║\n", "", total);
    printf("╚══════════════════════════════════════════════════════════╝\n");
}
