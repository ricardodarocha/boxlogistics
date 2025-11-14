//
// Created by Ricardo on 13/11/2025.
//

typedef struct Entrega {
    int id;
    int id_produto;
    float valor;
    float quant;
    float total;
    char destinatario[SIZES]; //nome do destinatario
    // char cpf[SIZES];
    int cpf;
} Entrega;

int cursor_proxima_entrega( );

int validar_entrega(void* dado, char* message);

Entrega *alocar_entrega(void);

int localizar_entrega(void *a, void *b);

void imprimir_cabecalho_entrega();

void imprimir_entrega(void *dado);

#ifndef TFINAL_ENTREGA_H
#define TFINAL_ENTREGA_H

#endif //TFINAL_ENTREGA_H