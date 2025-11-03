//
// Created by Ricardo on 02/11/2025.
//

#ifndef MODULE_CADASTROS3
#define MODULE_CADASTROS3

#include <stdint.h>

//indicadores
int qtd_produtos(void);
int qtd_entregas(void);
int qtd_cargas(void);
int qtd_vendas(void);

void inserir_produtos();
void buscar_produtos(int id);
void listar_produtos();

void inserir_entregas();
void buscar_entregas();
void listar_entregas();

void inserir_cargas();
void buscar_cargas();
void listar_cargas();

void inserir_vendas();
void buscar_vendas();
void listar_vendas();

void relatorios();

#endif