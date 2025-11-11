#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "../include/arvore.h"


Arvore *criarArvore(int id, void *dado) {
    Arvore *n = malloc(sizeof(Arvore));
    if (!n) return NULL;
    n->id = id;
    n->dado = dado;
    n->esq = n->dir = NULL;
    return n;
}

Arvore *inserirArvore(Arvore *raiz, int id, void *dado) {
    if (!raiz) return criarArvore(id, dado);

    if (id < raiz->id)
        raiz->esq = inserirArvore(raiz->esq, id, dado);
    else
        raiz->dir = inserirArvore(raiz->dir, id, dado);

    return raiz;
}

void *buscarArvoreId(Arvore *raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->id) return raiz->dado;
    if (id < raiz->id) return buscarArvoreId(raiz->esq, id);

    return buscarArvoreId(raiz->dir, id);
}

void *buscarArvore(Arvore *raiz, void *alfa, int (*cmp)(void*, void*)) {
    if (!raiz) return NULL;
    int parcial = cmp(raiz->dado, raiz->dado);
    if (parcial == FOUND) return raiz->dado;

    return parcial < FOUND
        ? buscarArvore(raiz->esq, alfa, cmp)
        : buscarArvore(raiz->dir, alfa, cmp)
    ;
}

// Ultimo nó mais a esquerda
Arvore *leftArvore(Arvore *raiz) {
    if (!raiz) return NULL;
    while (raiz->esq != NULL ) raiz = raiz->esq;
    return raiz;
}

// Ultimo nó mais a direita
Arvore *rightArvore(Arvore *raiz) {
    if (!raiz) return NULL;
    while (raiz->dir) raiz = raiz->dir;
    return raiz;
}

// Funcao auxiliar para remover no minimo da subarvore
Arvore *removerMin(Arvore *raiz, Arvore **min) {
    if (!raiz->esq) {
        *min = raiz;
        return raiz->dir;
    }
    raiz->esq = removerMin(raiz->esq, min);
    return raiz;
}

// Remover no por id mantendo Arvore
Arvore *removerArvore(Arvore *raiz, int id) {
    if (!raiz) return NULL;

    if (id < raiz->id)
        raiz->esq = removerArvore(raiz->esq, id);
    else if (id > raiz->id)
        raiz->dir = removerArvore(raiz->dir, id);
    else {
        // Nao encontrado
        if (!raiz->esq) {
            Arvore *temp = raiz->dir;
            free(raiz);
            return temp;
        };

        if (!raiz->dir) {
            Arvore *temp = raiz->esq;
            free(raiz);
            return temp;
        };

        // Dois filhos: substituir pelo menor da direita
        Arvore *min = NULL;
        raiz->dir = removerMin(raiz->dir, &min);
        min->esq = raiz->esq;
        min->dir = raiz->dir;
        free(raiz);
        return min;

    }
    return raiz;
}

// Impressao em ordem
void imprimirArvore(Arvore *raiz, void (*imprimir)(void *)) {
    if (!raiz) return;
    imprimirArvore(raiz->esq, imprimir);
    // printf("ID:%d -> ", raiz->id);
    imprimir(raiz->dado);
    imprimirArvore(raiz->dir, imprimir);
}

// Serializacao
void pre_ordem(Arvore *raiz, void (*imprimir)(void *)) {
    if (!raiz) return;
    printf("ID:%d -> ", raiz->id);
    imprimir(raiz->dado);
    pre_ordem(raiz->esq, imprimir);
    pre_ordem(raiz->dir, imprimir);
}

void pos_ordem(Arvore *raiz, void (*imprimir)(void *)) {
    if (!raiz) return;
    pos_ordem(raiz->esq, imprimir);
    pos_ordem(raiz->dir, imprimir);
    printf("ID:%d -> ", raiz->id);
    imprimir(raiz->dado);
}

void *busca_avancada(Arvore *raiz, void *alfa, int (*cmp)(void*, void*)) {
    if (!raiz) return NULL;

    if (cmp(raiz->dado, alfa) == 0) return raiz->dado;

    void *res = busca_avancada(raiz->esq, alfa, cmp);
    if (res) return res;
    return busca_avancada(raiz->dir, alfa, cmp);
}


// typedef struct {
//     int matricula;
//     char nome[64];
// } Aluno;
//
// void imprimirAluno(void *ptr) {
//     Aluno *a = ptr;
//     printf("%s\n", a->nome);
// }
//
// // Comparacao para busca avancada
// int cmpAluno(void *a, void *b) {
//     Aluno *aa = a;
//     Aluno *bb = b;
//     return strcmp(aa->nome, bb->nome);
// }

// int main() { //exemplo com alunos
//     Arvore *raiz = NULL;
//
//     Aluno *a1 = malloc(sizeof(Aluno)); a1->matricula=1; strcpy(a1->nome,"Alice");
//     Aluno *a2 = malloc(sizeof(Aluno)); a2->matricula=2; strcpy(a2->nome,"Bruno");
//     Aluno *a3 = malloc(sizeof(Aluno)); a3->matricula=3; strcpy(a3->nome,"Clarice");
//
//     raiz = inserirArvore(raiz, a1->matricula, a1);
//     raiz = inserirArvore(raiz, a2->matricula, a2);
//     raiz = inserirArvore(raiz, a3->matricula, a3);
//
//     printf("Imprimindo Arvore in-order:\n");
//     imprimirArvore(raiz, imprimirAluno);
//
//     printf("\nBuscando por ID 2:\n");
//     Aluno *buscado = buscarArvore(raiz, 2);
//     if (buscado) printf("Encontrado: %s\n", buscado->nome);
//
//     printf("\nBusca avancada por nome 'Clarice':\n");
//     Aluno alvo; strcpy(alvo.nome,"Clarice");
//     Aluno *buscado2 = busca_avancada(raiz, &alvo, cmpAluno);
//     if (buscado2) printf("Encontrado: %s\n", buscado2->nome);
//
//     printf("\nRemovendo ID 2...\n");
//     raiz = removerArvore(raiz, 2);
//
//     printf("\nArvore apos remocao:\n");
//     imprimirArvore(raiz, imprimirAluno);
//
//     return 0;
// }
//

/* typedef struct {
    int id;
    char nome[64];
    float valor;
    int quantidade;
} Produto;

// Criar um produto
Produto *criarProduto(int id, const char *nome, float valor, int qtd) {
    Produto *p = malloc(sizeof(Produto));
    if (!p) return NULL;
    p->id = id;
    strncpy(p->nome, nome, sizeof(p->nome));
    p->valor = valor;
    p->quantidade = qtd;
    return p;
}

// Imprimir produto
void imprimirProduto(void *ptr) {
    Produto *p = ptr;
    printf("ID:%d %-15s Valor: %.2f Qtd:%d\n",
           p->id, p->nome, p->valor, p->quantidade);
}

// Comparacao para busca avancada (exemplo: pelo nome)
int cmpProdutoNome(void *a, void *b) {
    Produto *pa = a;
    Produto *pb = b;
    return strcmp(pa->nome, pb->nome);
}

// Comparacao para busca avancada (exemplo: pelo valor)
int cmpProdutoValor(void *a, void *b) {
    Produto *pa = a;
    Produto *pb = b;
    if (pa->valor < pb->valor) return -1;
    if (pa->valor > pb->valor) return 1;
    return 0;
}

int main() {
    Arvore *raiz = NULL;

    // Criar produtos
    Produto *p1 = criarProduto(1, "Cama Casal", 1200.50, 2);
    Produto *p2 = criarProduto(2, "Cadeira", 150.75, 10);
    Produto *p3 = criarProduto(3, "Cabeceira", 350.00, 2);
    Produto *p4 = criarProduto(4, "Bau", 800.00, 1);

    // Inserir na Arvore pelo ID
    raiz = inserirArvore(raiz, p1->id, p1);
    raiz = inserirArvore(raiz, p2->id, p2);
    raiz = inserirArvore(raiz, p3->id, p3);
    raiz = inserirArvore(raiz, p4->id, p4);

    // Imprimir Arvore
    printf("Arvore de Produtos (in-order):\n");
    imprimirArvore(raiz, imprimirProduto);

    // Busca por ID
    int buscarID = 3;
    Produto *buscado = buscarArvore(raiz, buscarID);
    if (buscado)
        printf("\nProduto encontrado por ID %d: %s\n", buscarID, buscado->nome);

    // Busca avancada por nome
    Produto alvo; strcpy(alvo.nome, "Cadeira");
    Produto *buscado2 = busca_avancada(raiz, &alvo, cmpProdutoNome);
    if (buscado2)
        printf("Produto encontrado por nome: %s\n", buscado2->nome);

    // Remover produto por ID
    printf("\nRemovendo produto ID 2...\n");
    raiz = removerArvore(raiz, 2);

    printf("\nArvore apos remocao:\n");
    imprimirArvore(raiz, imprimirProduto);

    return 0;
}
 */