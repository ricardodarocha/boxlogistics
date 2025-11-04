#include <stdio.h>
#include <stdlib.h>

#include "../include/calendario.h"
#include "../include/data.h"
#include "../include/visual.h"
#include "../include/cadastros.h"

void boas_vindas_simplificado(const char *title) {

    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║ %-60s      ║\n",  title);
    printf("║ %-40s %25s ║\n", "BOX LOGISTICS", "Versão 0.1 (2025)");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");

    // printf("╔═════════════════════════════════════════════════════════════════════╗\n");
    // printf("║                           MENU DE VENDAS                            ║
    // printf("║ BOX LOGISTICS                                (Versão 0.1 2025)      ║
    // printf("╚═════════════════════════════════════════════════════════════════════╝\n");

}

const char *menu_principal =
    "   (1) Cadastrar produtos     (4) Formulario de vendas         \n"
    "   (2) Cadastrar entregas     (5) Relatorios                   \n"
    "   (3) Cadastrar cargas       (6) Calendario                   \n"
    " ═══════════════════════════════════════════════════════════════════\n"
    "   (9) Configuracoes          (0) Sair\n"
    "";

const char *menu_cadastrar_produtos =
    "   (1) Inserir produto\n"
    "   (2) Buscar produto\n"
    "   (3) Listar produtos\n"
    " ═══════════════════════════════════════\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_cadastrar_entregas =
    "   (1) Inserir entrega\n"
    "   (2) Buscar entrega\n"
    "   (3) Listar entregas\n"
    " ═══════════════════════════════════════\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_cadastrar_cargas =
    "   (1) Inserir carga\n"
    "   (2) Buscar carga\n"
    "   (3) Listar cargas\n"
    " ═══════════════════════════════════════\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_vendas =
    "   (1) Inserir venda\n"
    "   (2) Buscar venda\n"
    "   (3) Listar vendas\n"
    " ═══════════════════════════════════════\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_relatorio =
    "   (1) Vendas do Dia\n"
    "   (2) Estoque Atual\n"
    " ═══════════════════════════════════════\n"
    "   (0) Voltar\n";

void cadastrar_produtos() {
    int operacao =  exibir_menu(menu_cadastrar_produtos);
    switch (operacao) {
        case 1:
            inserir_produtos();
            break;
        case 2:
            int id;
            printf("Informe o id do produto para buscar\n");
            input_inteiro("ID", &id);
            buscar_produtos(id);
            break;
        case 3:
            system("cls");
            boas_vindas_simplificado("RELATORIO DE PRODUTOS");
            listar_produtos();
            break;
        case 0:
            return;
        default:
            printf("operacao invalida\n");
    }
}

void calendario() {
    Data data = hoje();
    imprimir_calendario(data.mes,data.ano);
    system("pause");
}

void executar_menu_principal(int * continuar) {
    boas_vindas_simplificado("MENU PRINCIPAL");
    int operacao =  exibir_menu(menu_principal);
    system("cls");
    switch (operacao) {
        case 1:
            boas_vindas_simplificado("CADASTRO DE PRODUTOS");
            if (qtd_produtos() == 0) {
                inserir_produtos();
            }
            cadastrar_produtos();
            break;
        case 2:
            boas_vindas_simplificado("CADASTRO DE ENTREGAS");
            // cadastrar_entregas();
            break;
        case 3:
            boas_vindas_simplificado("CADASTRO DE CARGAS");
            // cadastrar_cargas();
            break;
        case 4:
            boas_vindas_simplificado("VENDAS");
            // formulario_vendas();
            break;
        case 5:
            boas_vindas_simplificado("RELATORIOS");
            // relatorios();
            break;
        case 6:
            boas_vindas_simplificado("CALENDARIO");
            calendario();
            break;
        case 0:
            *continuar = 0;
            return;
        default:
            printf("operacao invalida\n");
    }
}
