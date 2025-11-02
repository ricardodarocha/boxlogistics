🧱 Exemplo: include/listagenerica.h
```C
#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

typedef struct Nodo {
    void *dados;
    struct Nodo *prox;
    struct Nodo *ant;
} Nodo;

typedef struct {
    Nodo *inicio;
    Nodo *fim;
    int tamanho;
} ListaGenerica;

ListaGenerica *criar_lista();
void inserir(ListaGenerica *lista, void *dados);
void *buscar(ListaGenerica *lista, int (*comparar)(void*, void*), void *chave);
void liberar_lista(ListaGenerica *lista, void (*destruir)(void*));

#endif
```

⚙️ Exemplo: lib/listagenerica.c
```C
#include <stdio.h>
#include <stdlib.h>
#include "../include/listagenerica.h"

ListaGenerica *criar_lista() {
    ListaGenerica *lista = malloc(sizeof(ListaGenerica));
    lista->inicio = lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

void inserir(ListaGenerica *lista, void *dados) {
    Nodo *n = malloc(sizeof(Nodo));
    n->dados = dados;
    n->prox = NULL;
    n->ant = lista->fim;
    if (lista->fim)
        lista->fim->prox = n;
    else
        lista->inicio = n;
    lista->fim = n;
    lista->tamanho++;
}
```
