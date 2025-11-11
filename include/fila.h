#ifndef TFINAL_FILA_H
#define TFINAL_FILA_H
#include "../app/config.h"

typedef struct FilaX {
    void *dado;
    struct FilaX *proximo;
} FilaX;

typedef struct {
    FilaX *inicio;
    FilaX *fim;
} Fila;

Fila *criarFila();
void enfileirar(Fila *f, void *dado);
void *desenfileirar(Fila *f);
void *remover(Fila *f, void *alfa, int (*cmp)(void*, void*));
void *peek_fila(Fila *f);
int filaVazia(Fila *f);
void imprimirFila(Fila *f, void (*imprimir)(void *));
void imprimirFilaAg(Fila *f, void (*imprimir_agregado)(void *, char *[SIZES], float * agregado), char * ag[SIZES], float * agregado);
void *buscarFila(Fila *fila, void *alfa, int (*cmp)(void*, void*));
void limparFila(Fila *f);

#endif
