#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pilha.h"

Pilha *criarPilha() {
    Pilha *p = malloc(sizeof(Pilha));
    if (!p) return NULL;
    p->topo = NULL;
    return p;
}

void push(Pilha *p, void *dado) {
    NoPilha *novo = malloc(sizeof(NoPilha));
    if (!novo) return;
    novo->dado = dado;
    novo->proximo = p->topo;
    p->topo = novo;
}

void empilhar(Pilha *p, void *dado) {
    push(p, dado);
}

void *pop(Pilha *p) {
    if (!p->topo) return NULL;
    NoPilha *removido = p->topo;
    void *dado = removido->dado;
    p->topo = removido->proximo;
    free(removido);
    return dado;
}

void *desempilhar(Pilha *p) {
    return pop(p);
}
void *peek(Pilha *p) {
    return p->topo ? p->topo->dado : NULL;
}

int contar(Pilha *p) {
    int c = 0;
    for (NoPilha *cur = p->topo; cur; cur = cur->proximo) c++;
    return c;
}

int pilhaVazia(Pilha *p) {
    return p->topo == NULL;
}

void imprimirPilha(Pilha *p, void (*imprimir)(void *)) {
    for (NoPilha *cur = p->topo; cur; cur = cur->proximo)
        imprimir(cur->dado);
    printf("=== Topo da Pilha ===\n");
}

void limparPilha(Pilha *p) {
    while (!pilhaVazia(p))
        pop(p);
    free(p);
}

typedef struct {
    int id;
    char nome[64];
    float valor;
    int quantidade;
} Produto;

Produto *criarProduto(int id, const char *nome, float valor, int qtd) {
    Produto *prod = malloc(sizeof(Produto));
    if (!prod) return NULL;
    prod->id = id;
    strncpy(prod->nome, nome, sizeof(prod->nome));
    prod->valor = valor;
    prod->quantidade = qtd;
    return prod;
}

void imprimirProduto(void *ptr) {
    Produto *p = ptr;
    printf("ID:%d %-15s Valor: %.2f Qtd:%d\n",
           p->id, p->nome, p->valor, p->quantidade);
}

// int main() {
//     Pilha *entrega = criarPilha();
//
//     // Produtos de móveis
//     Produto *p1 = criarProduto(1, "Cama Casal", 1200.50, 2);
//     Produto *p2 = criarProduto(2, "Cadeira", 150.75, 10);
//     Produto *p3 = criarProduto(3, "Cabeceira", 350.00, 2);
//     Produto *p4 = criarProduto(4, "Bau", 800.00, 1);
//
//     // Empilhar produtos
//     push(entrega, p1);
//     push(entrega, p2);
//     push(entrega, p3);
//     push(entrega, p4);
//
//     printf("Entrega atual:\n");
//     imprimirPilha(entrega, imprimirProduto);
//     printf("Total de itens empilhados: %d\n\n", contar(entrega));
//
//     // Desempilhar um item
//     Produto *removido = pop(entrega);
//     if (removido) {
//         printf("Produto removido do topo: %s\n\n", removido->nome);
//         free(removido);
//     }
//
//     printf("Entrega restante:\n");
//     imprimirPilha(entrega, imprimirProduto);
//     printf("Total de itens empilhados: %d\n", contar(entrega));
//
//     // Limpar pilha
//     limparPilha(entrega);
//     return 0;
// }
