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
    printf("   ║              BOX LOGISTICS SYSTEM  -  v0.1 (2025)            ║\n");
    printf("   ║             ──────────────────────────────────────           ║\n");
    printf("   ║              © 2025  Box Logistics - The System              ║\n");
    printf("   ║                                                              ║\n");
    printf("   ╚══════════════════════════════════════════════════════════════╝\n");
}

void team() {
    printf("   ╔══════════════════════════════════════════════════════════════╗\n");
    printf("   ║     ╔══════════════════════╗    ╔══════════════════════╗     ║\n");
    printf("   ║     ║  Wemerson            ║    ║  Maria Eduarda       ║     ║\n");
    printf("   ║     ║  Analista            ║    ║  Customer Success    ║     ║\n");
    printf("   ║     ║  Dev Pleno           ║    ║  Testadora           ║     ║\n");
    printf("   ║     ╚══════════════════════╝    ╚══════════════════════╝     ║\n");
    printf("   ║     ╔══════════════════════╗    ╔══════════════════════╗     ║\n");
    printf("   ║     ║  Agatta              ║    ║  Otavio              ║     ║\n");
    printf("   ║     ║  Frontend            ║    ║  Database Admin      ║     ║\n");
    printf("   ║     ║  Designer            ║    ║  ORACLE MVP          ║     ║\n");
    printf("   ║     ╚══════════════════════╝    ╚══════════════════════╝     ║\n");
    printf("   ║     ╔══════════════════════╗    ╔══════════════════════╗     ║\n");
    printf("   ║     ║  Nathan              ║    ║  Ricardo             ║     ║\n");
    printf("   ║     ║  Product Owner       ║    ║  Tech Lead           ║     ║\n");
    printf("   ║     ║  Chefe Comercial     ║    ║  Dev Senior          ║     ║\n");
    printf("   ║     ╚══════════════════════╝    ╚══════════════════════╝     ║\n");
    printf("   ║     ╔══════════════════════════════════════════════════╗     ║\n");
    printf("   ║     ║  Professor...  Jacimar Tavares                   ║     ║\n");
    printf("   ║     ║  Disciplina..  Algoritmos e Estruturas de Dados  ║     ║\n");
    printf("   ║     ╚══════════════════════════════════════════════════╝     ║\n");
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

    boas_vindas();
    team();
    printf("Nosso time agradece a confiança!\n");

    desconectar(/*ARQUIVO*/);
    system("pause");

    return 0;
}