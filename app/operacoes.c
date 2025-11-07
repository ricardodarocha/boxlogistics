#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../include/cadastros.h"
#include "../include/visual.h"
#include "../modules/ajuda.c"

void boas_vindas_simplificado(const char *title) {

    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║ %-55s      ║\n",  title);
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
    buscar_produto(id);
    system("PAUSE");
}

void executar_listar_produtos() {
    system("cls");
    boas_vindas_simplificado("RELATORIO DE PRODUTOS");
    listar_produtos();
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
        printf("Selecione o produto\n");
        input_inteiro("ID", &id_produto);
        id_produto = buscar_produto_id(id_produto); //0 se nao encontrado
        if (id_produto == 0) {
            printf("Produto nao encontrado");
            return;
        }
        int id_entrega = inserir_entregas(id_produto, &id_cliente);

        continuar = input_logico("Inserir mais um?");
    } while (continuar);
}

void executar_busca_entregas() {
    int id;
    printf("Informe o id da entrega para buscar\n");
    input_inteiro("ID", &id);
    buscar_entregas(id);
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