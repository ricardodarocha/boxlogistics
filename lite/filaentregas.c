#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct No_Entregas {
    int vId_Entrega;
    struct No_Produto* vProduto_da_Entrega;
    struct No_Cliente* vCliente_Da_Entrega;
    struct No_Entregas* proximo;
} No_Entregas;

typedef struct FilaW {
    struct No_Entregas* frente;
    struct No_Entregas* tras;
    int tamanho;
} FilaW;

void iniciarFilaWEntregas(struct FilaW* FilaW) {
    FilaW->frente = NULL;
    FilaW->tras = NULL;
    FilaW->tamanho = 0;
}

int verificarFilaWEntregasVazia(struct FilaW* FilaW) {
    if (FilaW->frente == NULL && FilaW->tras == NULL) {
        return 1;
    } else {
        return 0;
    }
}

struct No_Entregas* criarNo_Entrega(int vId_Entrega, struct No_Produto* vProduto_da_Entrega, struct No_Cliente* vCliente_Da_Entrega){
    No_Entregas* novoNo = (struct No_Entregas*) malloc (sizeof(struct No_Entregas));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria");
        return NULL;
    }
    novoNo->vId_Entrega = vId_Entrega;
    novoNo->vProduto_da_Entrega = vProduto_da_Entrega;
    novoNo->vCliente_Da_Entrega = vCliente_Da_Entrega;
    novoNo->proximo = NULL;
    return novoNo;
}

void enfileirarEntrega(struct FilaW* FilaW, int vId_Entrega, No_Produto* vProduto_da_Entrega, No_Cliente* vCliente_Da_Entrega) {

    struct No_Entregas* novoNo = criarNo_Entrega(vId_Entrega, vProduto_da_Entrega, vCliente_Da_Entrega);

    if (novoNo == NULL) {
        return;
    }

    if (verificarFilaWEntregasVazia(FilaW) == 1) {
        FilaW->frente = novoNo;
        FilaW->tras = novoNo;
    } else {
        FilaW->tras->proximo = novoNo;
        FilaW->tras = novoNo;
    }
    FilaW->tamanho++;
}

No_Entregas* desenfileirarEntregas(struct FilaW* FilaW) {
    if (verificarFilaWEntregasVazia(FilaW) == 1) {
        printf("\nNenhuma entrega para desenfileirar\n\n");
        return NULL;
    }

    struct No_Entregas* temp = FilaW->frente;
    FilaW->frente = FilaW->frente->proximo;

    if (FilaW->frente == NULL) {
        FilaW->tras = NULL;
    }

    FilaW->tamanho --;
    temp->proximo = NULL;
    return temp;
}

void imprimirFilaWEntregas(struct FilaW* FilaW) {
    if (verificarFilaWEntregasVazia(FilaW) == 1) {
        printf("\nNenhuma entrega para desenfileirar\n\n");
        return;
    }

    struct No_Entregas* atual = FilaW->frente;

    printf("%-5s %-20s %-20s\n", "ID", "Produto", "Cliente");

    while (atual != NULL) {
        printf("%-5d %-20s %-20s\n", atual->vId_Entrega, atual->vProduto_da_Entrega ? atual->vProduto_da_Entrega->vNomeProd : "N/A", atual->vCliente_Da_Entrega ? atual->vCliente_Da_Entrega->vNome_Cliente : "N/A");
        //printf("Id. Entrega: %-3d    Nome Destinatario: %-10s   C�digo Produto: %-3d    Nome Produto: %-10s\n", atual->vId_Entrega, atual->vCliente_Da_Entrega->vNome_Cliente, atual->vProduto_da_Entrega->vId_Produto, atual->vProduto_da_Entrega->vNomeProd);
        atual = atual->proximo;
    }
    printf("\nTotal de %d entrega(s) na FilaW.\n\n", FilaW->tamanho);
}

void enfileirarNoMovido(struct FilaW* FilaW, struct No_Entregas* noMovido) {
    if (noMovido == NULL) {
        return;
    }

    noMovido->proximo = NULL;

    if (verificarFilaWEntregasVazia(FilaW) == 1) {
        FilaW->frente = noMovido;
        FilaW->tras = noMovido;
    } else {
        FilaW->tras->proximo = noMovido;
        FilaW->tras = noMovido;
    }
    FilaW->tamanho++;
}