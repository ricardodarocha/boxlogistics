#include "../app/config.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;
    char nome[INPUTSIZE];
    float valor;
} Produto;

static int proximo_produto = 0;

int cursor_proximo_produto(void) {
    return proximo_produto;
}

void imprimir_cabecalho_produto() {
    printf("%3s %-49s %8s\n%s", "id", "nome", "valor",
    "============================================================\n" );
}

void iprimir_produto(void *dado) {
    Produto * p= dado;
    printf("%03d %-49s %6.2f\n", p->id, p->nome, p->valor );
}

int localizar_produto(void *a, void *b) {
    Produto *pa = a, *pb = b;
    return pa->id == pb->id ? FOUND : NOTFOUND;
}

int validar_produto(void *dado) {
    Produto * p= dado;

    //pode ser criada uma validacao personalizada
    return VALID;
}

Produto *alocar_produto(void) {
    Produto *produto = malloc(sizeof(Produto));
    if (!produto) {
        perror("malloc");
        return NULL;
    }

    // Valores padrao
    produto->id = proximo_produto += 1;
    produto->nome[0] = '\0';
    produto->valor = 0.0f;

    return produto;
}