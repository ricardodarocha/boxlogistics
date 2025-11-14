//
// Created by Ricardo on 9/11/2025.
/*
    Define pilha de backup para entregas recentes permitindo reconstruir cargas
*/

#include "../include/carga.h"

typedef struct Historico {
    Entrega * entrega;
    Carga * carga;
} Historico;

void imprimir_cabecalho_historico();

#ifndef TFINAL_HISTORICO_H
#define TFINAL_HISTORICO_H

#endif //TFINAL_HISTORICO_H