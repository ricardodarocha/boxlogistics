#ifndef TFINAL_BD_H
#define TFINAL_BD_H

#include "../include/arvore.h"
#include "../include/lista_dupla.h"
#include "../include/fila.h"
#include "../include/pilha.h"

typedef struct {
    ListaDupla *produtos;
    ListaDupla *clientes;
    Fila *entregas;
    Arvore *cargas;
    Pilha *pedidos; //últimos pedidos inseridos
    ListaDupla *vendas;
} BancoDados;
BancoDados* bd();
BancoDados* cursor();

void conectar();
void desconectar();

#endif