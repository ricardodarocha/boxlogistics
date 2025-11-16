#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "fila.h"
#include "../include/cadastros.h"
#include "../include/visual.h"
#include "../include/calendario.h"
#include "../include/data.h"
#include "../modules/ajuda.c"

void boas_vindas_simplificado(const char *title) {

    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║ %-55s      ║\n", title);
    printf("  ║ %-35s %25s ║\n", "BOX LOGISTICS", "Versão 0.1 (2025)");
    printf("  ╚══════════════════════════════════════════════════════════════╝\n");

    // printf("╔═════════════════════════════════════════════════════════════════════╗\n");
    // printf("║                        OPERACAO DE VENDAS                           ║
    // printf("║ BOX LOGISTICS                                (Versão 0.1 2025)      ║
    // printf("╚═════════════════════════════════════════════════════════════════════╝\n");

}

void executar_cadastro_produtos() {
    for (;;) {
        int codigo_produto = inserir_produto();
        if (!input_logico("Inserir mais um produto?")) break;
        printf("───────────────────────────────────────\n");
    }
}

void executar_busca_produtos() {
    int id;
    printf("Informe o id do produto para buscar\n");
    input_inteiro("ID", &id);
    id = buscar_produto_id(id);
    if (id==0) {
        alerta("ERRO", "PRODUTO NÃO ENCONTRADO");
    } else {
        imprimir_produto_id(id);
    }
    system("PAUSE");
}

void executar_listar_produtos() {
    system("cls");
    boas_vindas_simplificado("RELATORIO DE PRODUTOS");
    listar_produtos();
}

void executar_listar_clientes() {
    system("cls");
    boas_vindas_simplificado("RELATORIO DE CLIENTES");
    listar_clientes();
}

/*   Cadastro de entregas
     --------
     - Primeiro é necessario localizar um produto
     - Em seguida usuario digita o cpf do cliente
     - Se o cpf nao existe, entao o sistema coleta os dados do cliente
     - O sistema guarda esses dados no banco de dados
     - o sistema pergunta se quer inserir mais um produto
     - N -> o sistema encerra a entrega
     - S -> o sistema continua adicionando itens para o mesmo cliente
 */

void executar_cadastro_entregas() {
    // int id_produto, id_cliente, continuar; esta linha da erro lixo de memoria
    int id_produto, id_cliente = 0 , continuar;

    do {

        printf("\n  ┌────────────────────────────────────────┐\n");
        printf(  "  │   ESCOLHA UM PRODUTO                   │\n");
        printf(  "  └────────────────────────────────────────┘\n");
        //═════════════════════════════════
        //         LOOP DE BUSCA
        //digite 0 para listar, digite o codigo do produto, repete ate encontrar ou -1 para cancelar
        do {
            input_inteiro("  Digite o codigo do produto.    (0) ajuda\n   CODIGO DO PRODUTO", &id_produto);
            if (id_produto<0)
                return;
            if (id_produto==0) {
                listar_produtos();
            } else {
                id_produto = buscar_produto_id(id_produto); //0 se nao encontrado
                if (id_produto == 0) {
                    alerta("AVISO", "PRODUTO NÃO ENCONTRADO");
                    system("PAUSE");
                }
            }
        }   while (id_produto == 0);
        //      FIM DO LOOP DE BUSCA
        //═════════════════════════════════
        printf(" \n"); //bug
                    // system("PAUSE"); //evita bug

        int id_entrega = inserir_entregas(id_produto, &id_cliente);
        printf("Entrega inserida [%d]\n", id_entrega);
        continuar = input_logico("Inserir mais um?");
    } while (continuar);
}

void executar_busca_entregas() {
    int id;

    printf("\n  ┌────────────────────────────────────────┐\n");
    printf(  "  │   SELECIONE UMA ENTREGA                │\n");
    printf(  "  └────────────────────────────────────────┘\n");
    printf("Informe o id da entrega para buscar\n");
    input_inteiro("CODIGO DA ENTREGA", &id);
    buscar_entrega(id);
    system("PAUSE");
}

void executar_listar_entregas() {
    system("cls");
    boas_vindas_simplificado("RELATORIO DE ENTREGAS");
    listar_entregas();
}

void executar_ajuda_sistema_entregas() {
    system("cls");
    boas_vindas_simplificado("AJUDA DO SISTEMA DE ENTREGAS");
    ajuda_sistema_entregas();
}

/*   Montar cargas
     --------
     - Inspeciona a fila de entregas
     - o usuario digita o id da entrega
     - se a entrega existir, ele remove da fila e adiciona na carga
 */

void executar_cadastro_cargas() {
        int continuar;
        int id_carga = 0;
        if (qtd_cargas() > 0)
            if (input_logico("Deseja atualizar uma carga existente?"))
                listar_resumo_cargas();

    printf("\n  ┌────────────────────────────────────────┐\n");
    printf(  "  │   ESCOLHA UMA CARGA                    │\n");
    printf(  "  └────────────────────────────────────────┘\n");
    //═════════════════════════════════
    //         LOOP DE BUSCA
    input_inteiro("  Digite o codigo da carga.    (0) incluir\n   CODIGO DE RASTREIO", &id_carga);
    printf("\n  ┌────────────────────────────────────────┐\n");
    if (id_carga==0) {
        printf(  "  │   INCLUINDO UMA NOVA CARGA             │\n");
        printf(  "  ┌────────────────────────────────────────┐\n");
    }
    do {
        int id_entrega;
        printf("\n  ┌────────────────────────────────────────┐\n");
        printf(  "  │   ESCOLHA UMA ENTREGA                  │\n");
        printf(  "  └────────────────────────────────────────┘\n");
        //═════════════════════════════════
        //         LOOP DE BUSCA
        //digite 0 para listar, digite o codigo da entrega, repete ate encontrar ou -1 para cancelar
        do {
            input_inteiro("  Digite o codigo da entrega.    (0) ajuda\n   CODIGO DA ENTREGA", &id_entrega);
            if (id_entrega<0)
                return;
            if (id_entrega==0) {
                listar_entregas();
            } else {
                id_entrega = buscar_entrega_id(id_entrega); //0 se nao encontrado
                if (id_entrega == 0) {
                    alerta("AVISO", "ENTREGA NÃO ENCONTRADA");
                    system("PAUSE");
                }
            }
        }   while (id_entrega == 0);
        //      FIM DO LOOP DE BUSCA
        //═════════════════════════════════
        //selecionou
        incluir_entrega_na_carga(id_entrega, &id_carga);
        printf("\n  ┌───────────┬──────────────────────┐\n");
        printf(  "  │   TICKET  │ %4d                │\n", id_carga);
        printf(  "  └───────────└──────────────────────┘\n");
        printf(  "  Guarde o seu código de rastreio\n\n\n");

        // remove a entrega da fila e registra na lista de historicos
        arquivar_entrega(remover_entrega(id_entrega), id_carga);

        continuar = input_logico("Inserir mais um?");
    } while (continuar);
}

void executar_busca_cargas() {
    int id;

    printf("\n  ┌────────────────────────────────────────┐\n");
    printf("  │   LOCALIZE UMA CARGA                   │\n");
    printf("  └────────────────────────────────────────┘\n");
    printf("Informe o ticket da carga para buscar\n");
    input_inteiro("Codigo de Rastreio", &id);
    buscar_carga(id);
    system("PAUSE");
}
void executar_busca_cargas_por_data() {
    int serial_data;
    char data_carga[SIZEDATE];
    do {
        input_data_valid(("   Insira a data da carga"), data_carga);
        serial_data = serial_de_data_str(data_carga);

        if (serial_data <= 0) {
            alerta2("ERRO ", "Data inválida", data_carga);
        }
    } while (serial_data <= 0);
    buscar_carga(serial_data);
    system("PAUSE");
}

void executar_listar_cargas() {
    system("cls");
    boas_vindas_simplificado("ROMANEIO");
    listar_cargas();
}

void executar_listar_historico() {
    system("cls");
    boas_vindas_simplificado("ULTIMAS ENTREGAS CARREGADAS");
    listar_historico();
}

void formulario_vendas() {
    vender();
}

void simular_dados() {
    migrations();
}
