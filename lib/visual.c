#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

void imprimir_nome_sistema() {
    printf("%s", "SATURN LOGISTICS");
}

int exibir_menu(const char *operacoes) {
    imprimir_nome_sistema();
    printf("%s\n", operacoes);

    int menu_escolhido;
    printf("Escolha uma opcao: ");
    scanf("%d", &menu_escolhido);
    getchar();
    return menu_escolhido;
}
