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

void *remover(Fila *f, void *alfa, int (*cmp)(void*, void*)){
    if (!f || !f->inicio) return NULL;
    FilaX *anterior = NULL;
    FilaX *remover = f->inicio;
    while (remover && cmp(remover->dado, alfa)) {
        anterior = remover;
        remover = remover->proximo;
    }
    if (remover==NULL)  return NULL;
    void *dado = remover->dado;
    if (anterior==NULL) {
        f->inicio = remover->proximo;
    } else {
        anterior->proximo = remover->proximo;
    }
    free(remover);
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

