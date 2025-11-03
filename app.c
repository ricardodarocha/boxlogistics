#include "app/config.h"
#include "app/menus.c"
#include "app/estatisticas.c"
#include "include/bd.h"
#include "include/login.h"
#include <stdlib.h>

void boas_vindas() {

    printf("\x1b[2J\x1b[H");
    printf("\n");
    printf("   ╔══════════════════════════════════════════════════════════════╗\n");
    printf("   ║                                                              ║\n");
    printf("   ║                   ██████╗  ██████╗ ██╗   ██╗                 ║\n");
    printf("   ║                   ██╔══██╗██╔═══██╗ ██║ ██╔╝                 ║\n");
    printf("   ║                   ██████╔╝██║   ██║  ████╔╝                  ║\n");
    printf("   ║                   ██╔══██╗██║   ██║ ██╔═██╗                  ║\n");
    printf("   ║                   ██████║╚═██████╔╝██║   ██╗                 ║\n");
    printf("   ║                    ╚════╝  ╚═════╝ ╚═╝   ╚═╝                 ║\n");
    printf("   ║                                                              ║\n");
    printf("   ║               BOX LOGISTICS SYSTEM  ▪  v0.1 (2025)           ║\n");
    printf("   ║               -------------------------------------          ║\n");
    printf("   ║               © 2025  Box Logistics - The System             ║\n");
    printf("   ║                                                              ║\n");
    printf("   ╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

int main() {
    enable_ansi();
    conectar(/*ARQUIVO*/);
    char login[INPUTSIZE];

    do {

        system("cls");
        boas_vindas();

        int acesso = efetuar_login(login);

        if (!acesso) {
            printf("usuario ou senha invalidos\n");
            exit(0);
        }

        while (acesso) {
            verificar_permissoes(login);
            boas_vindas();
            executar_menu_principal(&acesso);
        }

    print_kpis();

    } while (input_logico("Deseja entrar com outro usuario?"));

    desconectar(/*ARQUIVO*/);
    system("pause");

    return 0;
}