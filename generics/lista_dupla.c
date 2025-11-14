#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_dupla.h"
#include "../app/config.h"
/**
Lista duplamente encadeada generica
 - aceita qualquer struct como conteudo
 - implmeentaementa os metodos inserir, pesquisar, irmpirmir
 */

ListaDupla *criarListaDupla(void *dado) {
    ListaDupla *no = malloc(sizeof(ListaDupla));
    if (!no) return NULL;
    no->dado = dado;
    no->proximo = NULL;
    no->anterior = NULL;
    return no;
}

void inserirListaDupla(ListaDupla **lista, void *dado) {
    ListaDupla *novo = criarListaDupla(dado);
    if (!novo) return;

    if (*lista == NULL) {
        *lista = novo;
        return;
    }

    ListaDupla *cursor = *lista;
    while (cursor->proximo)
        cursor = cursor->proximo;

    cursor->proximo = novo;
    novo->anterior = cursor;
}

// Pesquisar com funcao cmp(a, b) == 0 → igual
void *pesquisarDuplo(ListaDupla *lista, void *alfa, int (*cmp)(void *, void *)) {
    for (ListaDupla *cursor = lista; cursor; cursor = cursor->proximo)
        if (cmp(cursor->dado, alfa) == FOUND)
            return cursor->dado;
    return NULL;
}

// Imprimir todos os elementos
void imprimirDuplo(ListaDupla *lista, void (*imprimir)(void *)) {
    for (ListaDupla *cursor = lista; cursor; cursor = cursor->proximo)
        imprimir(cursor->dado);
}

// Imprimir do fim ao inicio
void imprimirDuploReverso(ListaDupla *lista, void (*imprimir)(void *)) {
    if (!lista) return;
    ListaDupla *cursor = lista;
    while (cursor->proximo) cursor = cursor->proximo;
    for (; cursor; cursor = cursor->anterior)
        imprimir(cursor->dado);
}

// Limpar lista (nao libera o dado!)
void limparDuplo(ListaDupla *lista) {
    while (lista) {
        ListaDupla *lixo = lista;
        lista = lista->proximo;
        free(lixo);
    }
}

