#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct No_Produto {
    int vId_Produto;
    char vNomeProd[25];
    float vValorProd;
    float vPeso;
    float vAltura;
    float vComprimento;
    float vProfundidade;
    struct No_Produto* proximo;
    struct No_Produto* anterior;
} No_Produto;

float calcularVolumeProduto(No_Produto* produto){
    if (produto == NULL) {
        return 0.0;
    }

    float produtoVol = produto->vAltura * produto->vComprimento * produto->vProfundidade;
    return produtoVol / 1000000.0;
}

No_Produto* criarWProduto(int vId_Produto, const char *vNomeProd, float vValorProd, float vPeso, float vAltura, float vComprimento, float vProfundidade) {
    No_Produto* novoNo = (No_Produto*)malloc(sizeof(No_Produto));
    if (novoNo == NULL) {
        printf("    Erro na alocação de mem�ria!\n");
        return NULL;
    }

    novoNo->vId_Produto = vId_Produto;
    strcpy(novoNo->vNomeProd, vNomeProd);
    novoNo->vValorProd = vValorProd;
    novoNo->vPeso = vPeso;
    novoNo->vAltura = vAltura;
    novoNo->vComprimento = vComprimento;
    novoNo->vProfundidade = vProfundidade;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    return novoNo;
}

void inserirProdutoNoFimLista(No_Produto** cabeca_ref) {
    static int vId_Produto = 1;
    char vNomeProd[25];
    float vValorProd;
    float vPeso;
    float vAltura;
    float vComprimento;
    float vProfundidade;

    printf("        Código: %d\n", vId_Produto);
    printf("        Nome: ");
    scanf(" %24[^\n]", vNomeProd);
    printf("        Preço: R$");
    scanf("%f", &vValorProd);
    printf("        Peso (KG): ");
    scanf("%f", &vPeso);
    printf("        Altura (cm): ");
    scanf("%f", &vAltura);
    printf("        Comprimento (cm): ");
    scanf("%f", &vComprimento);
    printf("        Profundidade (cm): ");
    scanf("%f", &vProfundidade);

    No_Produto* novoNo = criarWProduto(vId_Produto, vNomeProd, vValorProd, vPeso, vAltura, vComprimento, vProfundidade);
    vId_Produto ++;

    if (novoNo == NULL) {
        return;
    }

    if (*cabeca_ref == NULL) {
        *cabeca_ref = novoNo;
        return;
    }

    No_Produto* temp = *cabeca_ref;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNo;
    novoNo->anterior = temp;
}

No_Produto* buscarProdutoPorId(No_Produto* cabeca_ref, int id) {
    No_Produto* temp = cabeca_ref;
    while (temp != NULL) {
        if (temp->vId_Produto == id) {
            return temp;
        }
        temp = temp->proximo;
    }
}

void imprimirProdutos(No_Produto* cabeca_ref) {

    printf("    %-5s %-20s %-10s %-10s %-10s\n", "ID", "Nome", "Preço", "Peso(Kg)", "Volume(m³)");

    while (cabeca_ref != NULL) {
        printf("    %-5d %-20s R$%-8.2f %-10.2f %-10.4f\n", cabeca_ref->vId_Produto, cabeca_ref->vNomeProd, cabeca_ref->vValorProd, cabeca_ref->vPeso, calcularVolumeProduto(cabeca_ref));
        cabeca_ref = cabeca_ref->proximo;
    }
}

/*void imprimirProdutosSelecionado(No_Produto* ProdutoSelecionado) {
    printf("    %-5s %-20s %-10s %-10s %-10s\n", "ID", "Nome", "Pre�o", "Peso(Kg)", "Volume(m�)");
    printf("    %-5d %-20s R$%-8.2f %-10.2f %-10.4f\n", ProdutoSelecionado->vId_Produto, ProdutoSelecionado->vNomeProd, ProdutoSelecionado->vValorProd, ProdutoSelecionado->vPeso, calcularVolumeProduto(ProdutoSelecionado));
}*/
