#include "../include/bd.h"
#include "../include/cadastros.h"

#include "../include/visual.h"
#include "../modules/produtos.c"
#include "../modules/entregas.c"
#include "../modules/cargas.c"
#include "../modules/vendas.c"

// ================= indicadores  ====================
int qtd_produtos(void) {
  return cursor_proximo_produto();
}

int qtd_entregas(void) {
  return 0;
}

int qtd_cargas(void) {
  return 0;
}

int qtd_vendas(void) {
  return 0;
}
//==========================================

void inserir_produtos(){
    Produto * novo_produto = alocar_produto();

  //==================== ler os campos do produto ====================
    printf(      "              ID: %03d\n", novo_produto->id);
    input_string("Nome do produto", novo_produto->nome, sizeof(novo_produto->nome));
    input_float(   "          Valor", &novo_produto->valor);
  //==================================================================

  //==================== validar =====================================
    validar_produto(novo_produto);
  //==================================================================

  //==================== inserir no banco de dados ===================
    inserirListaDupla(&bd()->produtos, novo_produto);
  //==================================================================
}

void buscar_produtos(const int id) {
    Produto chave = {0};
    chave.id = id;
    Produto *encontrado = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
    if (encontrado)
        printf("\nEncontrado: %s\n", encontrado->nome);
}

void listar_produtos() {
  imprimir_cabecalho_produto();
  imprimirDuplo(bd()->produtos, iprimir_produto);
  system("pause");
}

void inserir_entregas() {

}

void buscar_entregas() {

}

void listar_entregas() {

}

void inserir_cargas() {

}

void buscar_cargas() {

}
void listar_cargas() {

}

void inserir_vendas() {

}
void buscar_vendas() {

}
void listar_vendas() {

}

void relatorios(){
}
