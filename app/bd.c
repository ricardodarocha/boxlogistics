
#include <stdio.h>
#include "../include/arvore.h"
#include "../include/bd.h"
#include "../include/fila.h"
#include "../include/lista_dupla.h"
#include "../include/pilha.h"

//Aponta sempre pra cabeça da lista
BancoDados* bd() {
    static BancoDados memoria;
    static int initialized = 0;

    if (!initialized) {
        memoria.produtos = NULL;
        memoria.clientes = NULL;
        memoria.entregas = criarFila();
        memoria.cargas   = NULL;
        memoria.pedidos  = NULL;
        memoria.vendas   = NULL;
        initialized = 1;
    }

    return &memoria;
}

//Aponta sempre pra o item selecionado, podendo mudar durante a navegacao
BancoDados* cursor() {
    static BancoDados memoria;
    static int initialized = 0;

    if (!initialized) {
        memoria.produtos = NULL;
        memoria.entregas = NULL;
        memoria.cargas   = NULL;
        memoria.pedidos  = NULL;
        memoria.vendas   = NULL;
        initialized = 1;
    }

    return &memoria;
}

extern BancoDados DB;

void conectar(){

}
void desconectar(){
    printf("\nBanco de dados finalizado\n");
}