#include <stdio.h>
#include <stdlib.h>
#include "../include/fila.h"
#include "../app/config.h"

Fila *criarFila() {
    Fila *f = malloc(sizeof(Fila));
    if (!f) return NULL;
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void enfileirar(Fila *f, void *dado) {
    FilaX *novo = malloc(sizeof(FilaX));
    if (!novo) return;
    novo->dado = dado;
    novo->proximo = NULL;

    if (f->fim) {
        f->fim->proximo = novo;
    } else {
        f->inicio = novo;
    }
    f->fim = novo;
}

void *desenfileirar(Fila *f) {
    if (!f->inicio) return NULL;

    FilaX *removido = f->inicio;
    void *dado = removido->dado;

    f->inicio = removido->proximo;
    if (!f->inicio) f->fim = NULL; // fila ficou vazia

    free(removido);
    return dado;
}

void *remover(Fila *f, void *alfa, int (*cmp)(void*, void*)) {
    if (!f || !f->inicio) return NULL;

    FilaX *anterior = NULL;
    FilaX *rem = f->inicio;

    // percorre até achar o item (cmp == 0 indica igualdade)
    while (rem && cmp(rem->dado, alfa) != 0) {
        anterior = rem;
        rem = rem->proximo;
    }

    if (!rem) return NULL;  // não encontrou

    void *dado = rem->dado;

    // caso 1: removendo o primeiro nó
    if (!anterior) {
        f->inicio = rem->proximo;
        // se removemos o único nó, ajustar também o fim
        if (f->inicio == NULL)
            f->fim = NULL;
    }
    // caso 2: removendo do meio ou fim
    else {
        anterior->proximo = rem->proximo;
        // se removemos o último
        if (rem == f->fim)
            f->fim = anterior;
    }

    free(rem);
    return dado;
}

void *peek_fila(Fila *f) {
    return (f && f->inicio) ? f->inicio->dado : NULL;
}

int filaVazia(Fila *f) {
    return (f == NULL || f->inicio == NULL);
}

void imprimirFila(Fila *f, void (*imprimir)(void *)) {
    if (f == NULL || f->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    for (FilaX *cur = f->inicio; cur; cur = cur->proximo)
        imprimir(cur->dado);
    printf("=== Fim da Fila ===\n");
}

//Esta funcao permite usar um agregador por exemplo order by name
void imprimirFilaAg(Fila *f, void (*imprimir_agregado)(void *, char *[SIZES], float * agregado), char * ag[SIZES], float * agregado) {
    if (f == NULL || f->inicio == NULL) {
        printf("Fila vazia.\n");
        return;
    }
    for (FilaX *cur = f->inicio; cur; cur = cur->proximo)
        imprimir_agregado(cur->dado, ag, agregado);
}

void *buscarFila(Fila *fila, void *alfa, int (*cmp)(void*, void*)) {
    if (fila == NULL) return NULL;
    if (fila->inicio == NULL) return NULL;
    for (FilaX *cursor = fila->inicio; cursor; cursor = cursor->proximo)
        if (cmp(cursor->dado, alfa) == 0)
            return cursor->dado;
    return NULL;
}

void limparFila(Fila *f) {
    while (!filaVazia(f))
        desenfileirar(f);
    free(f);
}

