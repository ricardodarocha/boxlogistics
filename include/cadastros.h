#ifndef MODULE_CADASTROS3
#define MODULE_CADASTROS3

#include <stdint.h>

#include "../app/config.h"

//indicadores
int qtd_produtos(void);
int qtd_entregas(void);
int qtd_cargas(void);
int qtd_vendas(void);

/*
    arquitetura
        cadastro.h  -> acessa bd() funcoes para inserir registro no bd (push), localizar (search), listar (iterator)
        cadastro.c  -> acessa os modulos produtos.c entregas.c, conhece os tipos Produto, Entrega etc
        produto.c,
        entrega.c      define a struct Produto, Entrega e os metodos imprimir1 encontrou1 individuais
*/

/*
    prototipos
        qtd..           -> indicador que retorna o numero de registros no banco de dados
        inserir..       -> funcao que permite chamar o metodo de inserir
        void * buscar..    funcao que retorna um (void * dado) contendo o Tipo Generico <T>ListaGenerica ex. cast (Produto *) *void
        int    buscar..    funcao que retorna apenas o id ex. <T>ListaGenerica->id * boa para evitar dependencias de (Produto *)
        listar             funcao que permite navegar na lista e imprimir todos os registros
 */

/*
    recomendações
        Nao implementar arquivos .h para produtos.c, entregas.c etc
        Nao visualizar bc dentro de produto.c
        Nao importar structs dentro de outra estruct por exemplo produto->entrega xx proibido
        em vez disso use injecao de dependencias via cadastro.c
        aceitavel:
            produto * Produto = (Produto *) Buscar(bd()->produtos, buscar1produto)
            ..onde void buscar1produto(a, b) é declarada em produto.c
 */

int inserir_produto();
void * buscar_produto(int id);
int buscar_produto_id(int id);
void listar_produtos();

int inserir_entregas(int id_produto, int * id_cliente);
void * buscar_entregas(const int id);

//funcao especial para agrupar entrega por destinatario;
void iprimir_entrega_ag(void *dado,  char * destinatario[SIZES], float * agregado);

void listar_entregas();

int inserir_cargas();
void * buscar_cargas(const int id);
void listar_cargas();

int inserir_vendas(const int id);
void * buscar_vendas();
void listar_vendas();

void relatorios();

#endif