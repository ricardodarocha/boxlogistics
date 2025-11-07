#ifndef TFINAL_ARVORE_H
#define TFINAL_ARVORE_H

typedef struct Arvore {
    int id;
    void *dado;
    struct Arvore *esq;
    struct Arvore *dir;
} Arvore;

Arvore *criarArvore(int id, void *dado);
Arvore *inserirBST(Arvore *raiz, int id, void *dado);
void *buscarBST(Arvore *raiz, int id);
Arvore *leftBST(Arvore *raiz);
Arvore *rightBST(Arvore *raiz);


#endif