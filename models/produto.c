#include <stdio.h>
#include <stdlib.h>
#include "../include/produto.h"

Produto *criar_produto(int id, const char *nome, float valor) {
    Produto *p = malloc(sizeof(Produto));
    p->id = id;
    snprintf(p->nome, sizeof(p->nome), "%s", nome);
    p->valor = valor;
    return p;
}

void exibir_produto(Produto *p) {
    printf("ID: %d | Nome: %s | Valor: %.2f\n", p->id, p->nome, p->valor);
}
