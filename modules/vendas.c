#include "../app/config.h"
#include "../include/fila.h"
#include "../include/visual.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Item {
    int id;
    char nome[40];
    float preco;
    float quantidade;
    float total_item;
} Item;

typedef struct Venda {
    int id;
    char datastr[SIZES];
    int data;
    int id_cliente;
    int id_produto;
    char nome[SIZES];

    float quantidade;
    float preco;
    float valor;
    float total_item;

    int qt_itens;
    float total;

    Fila *itens;
} Venda;

#define ACAO_VENDA_CLIENTE 1
#define ACAO_VENDA_PRODUTO 2
#define ACAO_VENDA_QUANTIDADE 3
#define ACAO_VENDA_PRECO 4
#define ACAO_VENDA_TOTAL 5
#define ACAO_VENDA_IMPRIMIR 6
#define ACAO_ENCERRAR 0
#define ACAO_CANCELAR -1


static int proxima_venda = 0;

int cursor_proxima_venda(void) {
    return proxima_venda;
}

void * criarItem() {
    FilaX *f = malloc(sizeof(FilaX));
    if (!f) return NULL;
    f->proximo = NULL;
    return f;
}

Venda *alocar_venda() {
    Venda *v = malloc(sizeof(Venda));
    if (!v) return NULL;

    v->id = 0;
    v->nome[0] = '\0';
    v->datastr[0] = '\0';
    v->data  = 0;
    v->valor = 0.0f;

    v->itens = criarItem();  // lista de entregas

    return v;
}

// ---------------------------------------------------------
// ADICIONAR ENTREGA A VENDA
// ---------------------------------------------------------
void venda_adicionar_entrega(Venda *v, void *e, float valor) {
    if (!v || !e) return;

    enfileirar(v->itens, e);

    // Atualiza total da venda
    v->valor += valor;
}

void imprimir_venda(void *dado) {
    Venda *v = dado;

    printf("V%3d %-30s %-10s R$ %6.2f\n",
        v->id,
        v->nome,
        v->datastr,
        v->valor
    );
}

void moveXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void imprimir_venda_layout(Venda *v) {
    printf("\033[2J"); // limpa tela

    // BANNER ---------------------------------------------------------
    moveXY(1,1);  printf("  ┌────────────────────────────────────────────────────────────┐");
    moveXY(1,2);  printf("  │                      BOX  SISTEMAS                         │");
    moveXY(1,3);  printf("  ├────────────────────────────────────────────────────────────┤");

    // CABEÇALHO ------------------------------------------------------
    moveXY(1,4);  printf("  │ DATA: %-10s      ID CLIENTE: %04d                      │", v->data, v->id_cliente);
    moveXY(1,5);  printf("  │ CLIENTE: %-46s │", v->nome);
    moveXY(1,6);  printf("  ├──────────────────────────────┬───────────────────────────────────────┤");

    // CAMPOS ESQUERDA -----------------------------------------------
    moveXY(1,7);  printf("  │     CAMPOS DA VENDA          │             LISTA DE ITENS            │");

    moveXY(1,8);  printf("  │ ┌──────────────────────────┐ │ ┌────────────────────────────────────┐│");
    moveXY(1,9);  printf("  │ │ QUANTIDADE: %-12.2f │ │ │                                         ││", v->quantidade);
    moveXY(1,10); printf("  │ └──────────────────────────┘ │ └────────────────────────────────────┘│");

    moveXY(1,11); printf("  │ ┌──────────────────────────┐ │                                       │");
    moveXY(1,12); printf("  │ │ PREÇO:      %-12.2f │ │                                       │", v->preco);
    moveXY(1,13); printf("  │ └──────────────────────────┘ │                                       │");

    moveXY(1,14); printf("  │ ┌──────────────────────────┐ │                                       │");
    moveXY(1,15); printf("  │ │ TOTAL ITEM: %-12.2f │ │                                       │", v->total_item);
    moveXY(1,16); printf("  │ └──────────────────────────┘ │                                       │");

    // ÁREA VAZIA PARA ESTÉTICA --------------------------------------
    for (int y = 17; y <= 30; y++) {
        moveXY(1, y);
        printf("  │                              │                                       │");
    }

    moveXY(1,31);
    printf("  ├──────────────────────────────┴───────────────────────────────────────┤");

    // RODAPÉ ---------------------------------------------------------
    moveXY(1,32);
    printf("│ QT ITENS: %-5d                                         TOTAL: R$ %8.2f │",
           v->qt_itens, v->total);

    moveXY(1,33);
    printf("  └──────────────────────────────────────────────────────────────────────┘");

    // LISTA DE ITENS -------------------------------------------------
    FilaX *cur = v->itens->inicio;
    int linha = 9;  // começa onde está a caixa da lista

    while (cur && linha < 30) {
        Item *it = cur->dado;

        moveXY(37, linha);
        printf("%02d %-6s %6.2f x %-6.2f = %6.2f",
               it->id, it->nome, it->quantidade, it->preco, it->total_item);

        linha++;
        cur = cur->proximo;
    }

    fflush(stdout);
}

void vender_agora() {
    int acao = ACAO_VENDA_CLIENTE;
    Venda *venda = alocar_venda();
    while (acao>ACAO_ENCERRAR) {
        imprimir_venda_layout(venda);
        if (acao == ACAO_VENDA_PRODUTO) {
            moveXY(7, 7);
            input_inteiro("ID PRODUTO", &venda->id_cliente);
            acao = ACAO_VENDA_QUANTIDADE;
        } else if (acao == ACAO_VENDA_CLIENTE)
        {
            moveXY(4, 4);
            input_inteiro("ID CLIENTE", &venda->id_produto);
            acao = ACAO_VENDA_PRODUTO;
        } else if (acao == ACAO_VENDA_QUANTIDADE)
        {
            moveXY(6, 9);
            input_float("QUANTIDADE", &venda->quantidade);
            acao = ACAO_VENDA_PRECO;
        } else if (acao == ACAO_VENDA_PRECO)
        {
            moveXY(6, 13);
            input_float("PREÇO", &venda->preco);
            acao = ACAO_VENDA_TOTAL;
        } else if (acao == ACAO_VENDA_TOTAL)
        {
            moveXY(6, 19);
            input_float("TOTAL ITEM", &venda->valor);
            acao = ACAO_ENCERRAR;
        }
    }

}

void imprimir_relatorio_venda(Venda *v) {
    if (!v) return;

    printf("  ╔══════════════════════════════════════════════════════════╗\n");
    printf("  ║                       VENDA n° %04d                      ║\n", v->id);
    printf("  ╠══════════════════════════════════════════════════════════╣\n");
    printf("  ║ Cliente: %-45s ║\n", v->nome);
    printf("  ║ Data:    %-45s ║\n", v->data);
    printf("  ╠══════════════════════════════════════════════════════════╣\n");
    printf("  ║ ITENS DA VENDA                                           ║\n");
    printf("  ╠══════════════════════════════════════════════════════════╣\n");
    printf("  ║ ID   Descricao                       Quant.    Valor     ║\n");
    printf("  ║ -------------------------------------------------------- ║\n");

    float total = 0.0f;

    //todo! mover pra quem chamou
    // for (FilaX *cur = v->entregas->inicio; cur; cur = cur->proximo) {
    //     Entrega *e = cur->dado;
    //     float subtotal = e->valor * e->quant;
    //
    //     printf("║ %-4d %-28s %7.2f %10.2f ║\n",
    //         e->id,
    //         e->destinatario,
    //         e->quant,
    //         subtotal
    //     );

    //total += subtotal;
    }
void imprimir_rodape_venda(float total) {


    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║ TOTAL%45s R$ %8.2f ║\n", "", total);
    printf("╚══════════════════════════════════════════════════════════╝\n");
}
