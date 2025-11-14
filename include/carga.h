//
// Created by Ricardo on 13/11/2025.
//

#ifndef TFINAL_CARGA_H
#define TFINAL_CARGA_H


#define CARGA_NAO_ENCONTRADA 0

typedef struct Carga {
    int id;
    int data; //o numero serial que representa a data, igual excel
    void *entregas; //um ponteiro para a cabeça de uma lista de entregas
    char nome[SIZES];
    float valor;
} Carga;

int cursor_proxima_carga( );

void imprimir_carga(void *dado, void (*imprimir_entrega)(void *));

void imprimir_cabecalha_carga();

int localizar_carga(void *a, void *b);

Carga *alocar_carga(void);

#endif //TFINAL_CARGA_H