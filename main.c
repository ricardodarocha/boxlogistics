#include "app.c"
#include <stdlib.h>

void membros_do_time() {
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
    printf("   ║     ║  Nathan              ║    ║  Guilherme           ║     ║\n");
    printf("   ║     ║  Product Owner       ║    ║  Scrum Master        ║     ║\n");
    printf("   ║     ║  Chefe Comercial     ║    ║  Agile Expert        ║     ║\n");
    printf("   ║     ╚══════════════════════╝    ╚══════════════════════╝     ║\n");
    printf("   ║     ╔══════════════════════╗    ╔══════════════════════╗     ║\n");
    printf("   ║     ║  Joao Paulo          ║    ║  Ricardo             ║     ║\n");
    printf("   ║     ║  Suporte Técnico     ║    ║  Tech Lead           ║     ║\n");
    printf("   ║     ║  Implantação         ║    ║  Dev Senior          ║     ║\n");
    printf("   ║     ╚══════════════════════╝    ╚══════════════════════╝     ║\n");
    printf("   ║     ╔══════════════════════════════════════════════════╗     ║\n");
    printf("   ║     ║  Professor...  Jacimar Tavares                   ║     ║\n");
    printf("   ║     ║  Disciplina..  Algoritmos e Estruturas de Dados  ║     ║\n");
    printf("   ║     ╚══════════════════════════════════════════════════╝     ║\n");
    printf("   ║                                                              ║\n");
    printf("   ╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void volte_sempre() {
    boas_vindas();
}

/* Main
    main(int argc, char * argv[])
    Funcao principal do programa

    1. habilita caracteres especiais ANSI - UTF8
    2. limpa a tela e roda o aplicativo, exibindo a tela de boas vindas
    3. while (input_logico)
        Fica preso no menu principal, até digitar N - deseja entrar com outro usuario S/N
    4. agradecimentos
    5. encerra o sistema
*/

int le_parametros(int argc, char * argv[]) {
    if (argc == 1) {
        printf("Nenhum parâmetro informado.\n");
        return 0;
    }

    printf("Parametros recebidos:\n");
    for (int i = 1; i < argc; i++) {
        printf("  %s\n", argv[i]);
        return argc;
    }
}

int main(int argc, char * argv[]) {
    le_parametros(argc, argv);
    enable_ansi();

    do {
        system("cls");
        boas_vindas();
        rodar_app(/* APP.CONFIG */);

    } while (input_logico("Deseja entrar com outro usuario?"));

    volte_sempre();
    membros_do_time();
    printf("Nosso time agradece a confiança!\n");
    system("pause");

    return 0;
}