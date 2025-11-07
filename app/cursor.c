#include "../include/bd.h"

/*
 Este arquivo implementa navegação
    |< primeiro    ultimo >|
     < anterior   proximo >

 - Listas duplamente encadeadas implementam navegação bidirecinal
 - Listas simplesmente encadeadas implementam navegação unidirecinal
 - Pilhas apenas removem o ultimo inserido com insercao no inicio
 - Filas apenas removem o primeiro inserido com insercao no final

exemplo:

 proximo_produto(bd)
  move para o proximo produto
  retorna (1) se encontrou um próximo registro
  retorna (0) se chegou ao fim
*/

int proximo_produto(BancoDados * cursor) {
    if (!cursor->produtos->proximo) return 0;
    cursor->produtos = cursor->produtos->proximo;
    return 1;
}

int anterior_produto(BancoDados * cursor) {
    if (!cursor->produtos->anterior) return 0;
    cursor->produtos = cursor->produtos->anterior;
    return 1;
}