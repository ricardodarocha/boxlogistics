#ifndef TFINAL_PILHA_H
#define TFINAL_PILHA_H

typedef struct NoPilha {
    void *dado;
struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
} Pilha;

Pilha *criarPilha();

#endif