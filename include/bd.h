#ifndef TFINAL_BD_H
#define TFINAL_BD_H

#include "../include/lista_dupla.h"

typedef struct {
    ListaDupla *produtos;
    ListaDupla *entregas;
    ListaDupla *cargas;
    ListaDupla *vendas;
} BancoDados;

BancoDados* bd();

void conectar();
void desconectar();

#endif