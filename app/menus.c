#include <stdio.h>
#include <stdlib.h>

#include "../app/operacoes.c"
#include "../include/data.h"
#include "../include/visual.h"
#include "../lite/main_lite.c"


const char *menu_principal =
    "   (1) Cadastrar produtos    (5) Relatorios                   \n"
    "   (2) Cadastrar entregas    (6) Calendario                   \n"
    "   (3) Cadastrar cargas      (7) Ajuda                        \n"
    "   (4) Formulario de vendas  (8) Versão Lite                  \n"
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
    "   (1) Cadastro de produtos\n"
    "   (2) Cadastro de clientes\n"
    "   (3) Cadastro de entregas\n"
    "   (4) Cadastro de cargas\n"
    "   (5) Ultimos carregamentos\n"
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

void relatorios() {
    int operacao =  exibir_menu(menu_relatorio);
    switch (operacao) {
        case 1:
            executar_listar_produtos();
            break;
        case 2:
            executar_listar_clientes();
            break;
        case 3:
            executar_listar_entregas();
            break;
        case 4:
            executar_listar_cargas();
            break;
        case 5:
            executar_listar_historico(); //ultimas entregas carregadas (pilha)
            break;
        case 0:
            return;
        default:
            printf("operacao invalida\n");
    }
}

void calendario() {
    Data data = hoje();
    imprimir_calendario(data.dia, data.mes, data.ano);
    system("pause");
}

void exibir_versao_lite() {
    MenuLogin();
    MenuPrincipal();
    system("pause");
}

void exibir_ajuda_geral() {
    ajuda_geral();
}

void exibir_configuracoes() {
    printf("  Voce nao precisa se preocupar com nada. O sistema ja vem previamente configurado. \n");
    printf("  Sentiu falta de alguma coisa? Entre em contato com nosso suporte.");
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
            relatorios();
            break;
        case 6:
            boas_vindas_simplificado("CALENDARIO");
            calendario();
            break;
        case 7:
            boas_vindas_simplificado("AJUDA");
            exibir_ajuda_geral();
            break;
        case 8:
            boas_vindas_simplificado("VERSÃO LITE                                            ");
            exibir_versao_lite();
            break;
        case 9:
            boas_vindas_simplificado("CONFIGURACOES");
            exibir_configuracoes();
            break;
        case 0:
            *continuar = 0;
            return;
        default:
            printf("operacao invalida\n");
    }
}
