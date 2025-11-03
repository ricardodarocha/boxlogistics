
#include <stdio.h>
#include "../include/lista_dupla.h"

typedef struct {
    ListaDupla *produtos;
    ListaDupla *entregas;
    ListaDupla *cargas;
    ListaDupla *vendas;
} BancoDados;

BancoDados* bd() {
    static BancoDados memoria;
    static int initialized = 0;

    if (!initialized) {
        memoria.produtos = NULL;
        memoria.entregas = NULL;
        memoria.cargas   = NULL;
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