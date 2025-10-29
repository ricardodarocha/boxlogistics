#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[100];
    float valor;
} Produto;

Produto *criar_produto(int id, const char *nome, float valor);
void exibir_produto(Produto *p);

#endif
