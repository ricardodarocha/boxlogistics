#include "app/config.h"
#include "app/menus.c"
#include "app/estatisticas.c"
#include "include/bd.h"
#include "include/login.h"
#include <stdlib.h>
void boas_vindas() {

    printf("\x1b[2J\x1b[H");
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                        5v83  ║\n");
    printf("  ║                   ██████╗  ██████╗ ██╗   ██╗                 ║\n");
    printf("  ║                   ██╔══██╗██╔═══██╗ ██║ ██╔╝                 ║\n");
    printf("  ║                   ██████╔╝██║   ██║  ████╔╝                  ║\n");
    printf("  ║                   ██╔══██╗██║   ██║ ██╔═██╗                  ║\n");
    printf("  ║                   ██████║╚═██████╔╝██║   ██╗                 ║\n");
    printf("  ║                    ╚════╝  ╚═════╝ ╚═╝   ╚═╝                 ║\n");
    printf("  ║                                                              ║\n");
    printf("  ║              BOX LOGISTICS SYSTEM  -  v0.1 (2025)            ║\n");
    printf("  ║             ──────────────────────────────────────           ║\n");
    printf("  ║              © 2025  Box Logistics - The System              ║\n");
    printf("  ║                                                              ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════╝\n");
}

/* Roda o aplicativo
    1. conecta no banco de dados
    2. faz login
    3. while (acesso)
        Fica preso no menu principal, até digitar 0 - sair
    4. imprime os indicadores
    5. volta no main
*/

void rodar_app() {
    conectar(/*ARQUIVO*/);
    simular_dados();
    int acesso = efetuar_login(_login);

    if (!acesso) {
        printf("usuario ou senha invalidos\n");
        exit(0);
    }

    while (acesso) {
        if (!verificar_permissoes(_login)) break;
        boas_vindas();
        executar_menu_principal(&acesso);
    }

    print_kpis();
    desconectar(/*ARQUIVO*/);
}