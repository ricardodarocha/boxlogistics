#include <stdio.h>
#include <stdlib.h>

#include "../app/operacoes.c"
#include "../include/data.h"
#include "../include/visual.h"

const char *menu_principal =
    "   (1) Cadastrar produtos     (4) Formulario de vendas         \n"
    "   (2) Cadastrar entregas     (5) Relatorios                   \n"
    "   (3) Cadastrar cargas       (6) Calendario                   \n"
    "  └──────────────────────────────────────────────────────────────┘\n"
    "   (9) Configuracoes          (0) Sair\n"
    "";

const char *menu_cadastrar_produtos =
    "   (1) Inserir produto\n"
    "   (2) Buscar produto\n"
    "   (3) Listar produtos\n"
    "  └──────────────────────────────────────┘\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_cadastrar_entregas =
    "   (1) Inserir entrega\n"
    "   (2) Buscar entrega\n"
    "   (3) Listar entregas\n"
    "   (4) Ajuda\n"
    "  └──────────────────────────────────────┘\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_cadastrar_cargas =
    "   (1) Inserir carga\n"
    "   (2) Buscar carga\n"
    "   (3) Listar cargas\n"
    "  └──────────────────────────────────────┘\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_vendas =
    "   (1) Inserir venda\n"
    "   (2) Buscar venda\n"
    "   (3) Listar vendas\n"
    "  └──────────────────────────────────────┘\n"
    "   (9) Configuracoes\n"
    "   (0) Voltar\n";

const char *menu_relatorio =
    "   (1) Vendas do Dia\n"
    "   (2) Estoque Atual\n"
    "  └──────────────────────────────────────┘\n"
    "   (0) Voltar\n";

void cadastrar_produtos() {
    int operacao =  exibir_menu(menu_cadastrar_produtos);
    switch (operacao) {
        case 1:
            executar_cadastro_produtos();
            break;
        case 2:
            executar_busca_produtos();
            break;
        case 3:
            executar_listar_produtos();
            break;
        case 0:
            return;
        default:
            printf("operacao invalida\n");
    }
}

void cadastrar_entregas() {
    int operacao =  exibir_menu(menu_cadastrar_entregas);
    switch (operacao) {
        case 1:
            executar_cadastro_entregas();
            break;
        case 2:
            executar_busca_entregas();
            break;
        case 3:
            executar_listar_entregas();
            break;
        case 4:
            executar_ajuda_sistema_entregas();
            system("PAUSE");
            break;
        case 0:
            return;
        default:
            printf("operacao invalida\n");
    }
}

void montar_cargas() {
    int operacao =  exibir_menu(menu_cadastrar_cargas);
    switch (operacao) {
        case 1:
            executar_cadastro_cargas();
            break;
        case 2:
            executar_busca_cargas();
            break;
        case 3:
            executar_listar_cargas();
            break;
        case 4:
            executar_ajuda_sistema_entregas(); //todo criar ajuda montar cargas
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
                inserir_produto();
            }
            cadastrar_produtos();
            break;
        case 2:
            boas_vindas_simplificado("CADASTRO DE ENTREGAS");
            cadastrar_entregas();
            break;
        case 3:
            boas_vindas_simplificado("MONTAR CARGAS");
            montar_cargas();
            break;
        case 4:
            boas_vindas_simplificado("VENDAS");
            formulario_vendas();
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
