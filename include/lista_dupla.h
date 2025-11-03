#ifndef TFINAL_LISTA_DUPLA_H
#define TFINAL_LISTA_DUPLA_H

typedef struct ListaDupla ListaDupla;

ListaDupla *criarListaDupla(void *dado);
void inserirListaDupla(ListaDupla **lista, void *dado);
void *pesquisarDuplo(ListaDupla *lista, void *alfa, int (*cmp)(void*, void*));
void imprimirDuplo(ListaDupla *lista, void (*imprimir)(void *));
void limparDuplo(ListaDupla *lista);

#endif
