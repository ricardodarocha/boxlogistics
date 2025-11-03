#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/visual.h"

#ifdef _WIN32
#include <windows.h>
#endif

void enable_ansi(void) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT;
    SetConsoleMode(hOut, dwMode);

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

int exibir_menu(const char *operacoes) {
    //imprimir_nome_sistema();
    printf("\n\n%s\n", operacoes);

    int menu_escolhido;
    printf(" Escolha uma opcao: ");
    scanf("%d", &menu_escolhido);
    getchar();
    return menu_escolhido;
}

void input_string(const char *prompt, char *out, size_t size) {
    printf(" %s: ", prompt);
    if (fgets(out, size, stdin)) {
        size_t len = strlen(out);
        if (len > 0 && out[len-1] == '\n') out[len-1] = '\0'; // remove \n
    }
}

void input_string_required(const char *title, char *out, size_t size) {
    size_t len;
    do {
        printf(" %s: ", title);
        if (!fgets(out, size, stdin))
            continue;
        len = strcspn(out, "\n");
        out[len] = '\0';
        if (len == 0)
            printf(" campo requerido\n");
    } while (len == 0);
}


void input_moeda(char *title, float *out) {
    printf(" %s: R$ ",  title);
    scanf("%f", out);
}

void input_inteiro(char *title, int *out) {
    printf(" %s: ",  title);
    scanf("%d", out);
}

void input_float(char *title, float *out) {
    printf(" %s: ",  title);
    scanf("%f", out);
}

int input_logico(char *title) {
    char selected;
    printf(" %s: (S/N) ",  title);
    scanf("%c", &selected);
    return (selected == 'S' || selected == 's' ? 1 : 0);
}

void input_senha(const char *title, char *out, size_t max_len) {
    printf(" %s: ", title);

    int i = 0;
    while (1) {
        char ch = _getch();

        if (ch == '\r' || ch == '\n') {
            out[i] = '\0';
            printf("\n");
            break;
        }

        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
            continue;
        }

        if (i >= (int)(max_len - 1))
            continue;

        out[i++] = ch;
        putch('*');
    }

}