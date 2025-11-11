#ifndef TFINAL_ARVORE_H
#define TFINAL_ARVORE_H

typedef struct Arvore {
    int id;
    void *dado;
    struct Arvore *esq;
    struct Arvore *dir;
} Arvore;

Arvore *criarArvore(int id, void *dado);
Arvore *inserirArvore(Arvore *raiz, int id, void *dado);
void *buscarArvoreId(Arvore *raiz, int id);
void *buscarArvore(Arvore *raiz, void *alfa, int (*cmp)(void*, void*));
Arvore *leftArvore(Arvore *raiz);
Arvore *rightArvore(Arvore *raiz);

Arvore *removerMin(Arvore *raiz, Arvore **min) ;
Arvore *removerArvore(Arvore *raiz, int id);
void imprimirArvore(Arvore *raiz, void (*imprimir)(void *));

void pre_ordem(Arvore *raiz, void (*imprimir)(void *));
void pos_ordem(Arvore *raiz, void (*imprimir)(void *));
void *busca_avancada(Arvore *raiz, void *alfa, int (*cmp)(void*, void*));

#endif