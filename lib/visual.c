#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/visual.h"
#include "../include/data.h"
#include "../include/calendario.h"

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

#define margem 4
#define vert 2

/* Guia de estilos
        ╔════════════════════════════╗
        ║          Premium           ║   Estetica Premium/Bold
        ╚════════════════════════════╝

        ┌────────────────────────────┐
        │   Fina / Estilo Minimal    │   Estética Clean/Slin
        └────────────────────────────┘

        ┌─── ────────────────────────┐
        │   Go╦hic / Daftpunk        │   Estética Gothic/Dark
        └──────────────────────────┘─┘

        ╔════════════════════════════╗
        ║  Híbrida ────├───────────  ║   Estetica Soft/Hybrid
        ╚════════════════════════════╝
 */

void cursorxy(int x, int y) {
    printf("\x1b[%d;%dH", y, x);
}

void cursor_up(int n) {
    printf("\x1b[%dA", n);
}

void cursor_down(int n) {
    printf("\x1b[%dB", n);
}

void cursor_left(int n) {
    printf("\x1b[%dD", n);
}

void cursor_right(int n) {
    printf("\x1b[%dC", n);
}

// -----------------------------
// Linha atual
// -----------------------------
void cursor_home_line(void) {
    // Voltar para o início da linha atual
    printf("\r");
    // Alternativa ANSI:
    // printf("\x1b[0G");
}

void cursor_next_line(int n) {
    printf("\x1b[%dE", n);
}

void cursor_prev_line(int n) {
    printf("\x1b[%dF", n);
}

// -----------------------------
// Limpezas
// -----------------------------
void clear_screen(void) {
    printf("\x1b[2J\x1b[1;1H");
}

void clear_line(void) {
    printf("\x1b[2K");
}

void clear_line_to_end(void) {
    printf("\x1b[K");
}

void clear_line_to_start(void) {
    printf("\x1b[1K");
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

void input_flush() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void input_string(const char *prompt, char *out, size_t size) {
    printf(" %s: ", prompt);

    if (fgets(out, size, stdin)) {
        size_t len = strlen(out);
        if (len > 0 && out[len-1] == '\n') {
            out[len-1] = '\0';
        } else {
            input_flush();
        }
    }
}

void render_mascara_data(const char *title, char *digits, int pos) {
    printf("\r%s: ", title);

    if (pos == 0) printf("../../....");
    else if (pos == 1) printf("%c_/../....", digits[0]);
    else if (pos == 2) printf("%c%c/../....", digits[0], digits[1]);
    else if (pos == 3) printf("%c%c/%c_/....", digits[0], digits[1], digits[2]);
    else if (pos == 4) printf("%c%c/%c%c/....", digits[0], digits[1], digits[2], digits[3]);
    else if (pos == 5) printf("%c%c/%c%c/%c.._",
                              digits[0], digits[1], digits[2], digits[3], digits[4]);
    else if (pos == 6) printf("%c%c/%c%c/%c%c..",
                              digits[0], digits[1], digits[2], digits[3],
                              digits[4], digits[5]);
    else if (pos == 7) printf("%c%c/%c%c/%c%c%c_",
                              digits[0], digits[1], digits[2], digits[3],
                              digits[4], digits[5], digits[6]);
    else if (pos == 8) printf("%c%c/%c%c/%c%c%c%c",
                              digits[0], digits[1], digits[2], digits[3],
                              digits[4], digits[5], digits[6], digits[7]);

    // reposicionar o cursor no ponto correto
    int visual_pos = pos;
    if (pos >= 2) visual_pos++;
    if (pos >= 4) visual_pos++;

    int base_x = (int)strlen(title) + 3;
    cursor_home_line();
}

void input_data_mascarada_validada(const char *title, char *out) {
    char digits[9] = {0};
    int pos = 0;

    printf("%s: ../../....", title);
    int base_x = (int)strlen(title) + 3;
    cursor_home_line();

    while (1) {
        int c = getch();

        // ENTER → só aceita se for válida
        if ((c == 13 || c == 10) && pos == 8) {
            if (data_valida_str(digits)) break;
            printf("\nData invalida, tente novamente.\n");
            pos = 0;
            digits[0] = 0;
            printf("%s: ../../....", title);
    cursor_home_line();
            continue;
        }

        // BACKSPACE inteligente
        if (c == 8 && pos > 0) {
            pos--;
            digits[pos] = '\0';
            render_mascara_data(title, digits, pos);
            continue;
        }

        // apenas numeros
        if (!isdigit(c)) continue;
        if (pos >= 8) continue;

        digits[pos++] = c;
        render_mascara_data(title, digits, pos);
    }

    // retorna dd/mm/aaaa
    sprintf(out, "%c%c/%c%c/%c%c%c%c",
        digits[0], digits[1], digits[2], digits[3],
        digits[4], digits[5], digits[6], digits[7]);

    printf("\n");
    input_flush();
}
void input_data_valid(const char *title, char *out) {
    Data _hoje = hoje();
    system("cls");
    imprimir_calendario(_hoje.dia, _hoje.mes, _hoje.ano);

    char digits[9] = {0};
    int pos = 0;

    printf("%s: ../../....", title);
    int base_x = (int)strlen(title) + 3;
    cursor_home_line();

    while (1) {
        int c = getch();

        // ENTER → só aceita se for válida
        if ((c == 13 || c == 10) && pos == 8) {
            if (data_valida_str(digits)) break;
            printf("\nData invalida, tente novamente.\n");
            pos = 0;
            digits[0] = 0;
            printf("%s: ../../....", title);
    cursor_home_line();
            continue;
        }

        // BACKSPACE inteligente
        if (c == 8 && pos > 0) {
            pos--;
            digits[pos] = '\0';
            render_mascara_data(title, digits, pos);
            continue;
        }

        // apenas numeros
        if (!isdigit(c)) continue;
        if (pos >= 8) continue;

        digits[pos++] = c;
        render_mascara_data(title, digits, pos);
    }

    // retorna dd/mm/aaaa
    sprintf(out, "%c%c/%c%c/%c%c%c%c",
        digits[0], digits[1], digits[2], digits[3],
        digits[4], digits[5], digits[6], digits[7]);

    printf("\n");
    input_flush();
}
void input_string_required(const char *title, char *out, size_t size) {
    for (;;) {
        printf(" %s: ", title);

        if (!fgets(out, size, stdin)) {
            input_flush();
            continue;
        }

        size_t len = strcspn(out, "\n");
        out[len] = '\0';

        if (len == 0) {
            printf(" campo requerido!\n");
            continue;
        }

        // se a linha era maior que o buffer, flush
        if (len == size - 1 && out[len] != '\0')
            input_flush();

        break;
    }
    input_flush();
}

void input_moeda(const char *title, float *out) {
    char buffer[64];

    for (;;) {
        printf(" %s (R$): ", title);

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            input_flush();
            continue;
        }

        // remove \n
        buffer[strcspn(buffer, "\n")] = '\0';

        // converte
        char *end;
        float val = strtof(buffer, &end);

        if (end == buffer || *end != '\0') {
            printf(" valor invalido, tente novamente.\n");
            continue;
        }

        *out = val;
        break;
    }
    input_flush();
}

void input_inteiro(char *title, int *out) {
    printf(" %s: ",  title);
    scanf("%d", out);
    input_flush();
}

void input_float(char *title, float *out) {
    printf(" %s: ",  title);
    scanf("%f", out);
    input_flush();
}

int input_logico(char *title) {
    char selected;
    printf(" %s: (S/N) ",  title);
    scanf(" %c", &selected);
    input_flush();
    return (selected == 'S' || selected == 's'|| selected == 'Y'|| selected == 'y'|| selected == '1' ? 1 : 0);
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

void imprimir_calendario(int dia, int mes, int ano) {
    int dias_mes = dias_no_mes(mes, ano);
    int serial_inicio = serial_de_data(1, mes, ano);
    int inicio_semana = serial_inicio%7; // 0=domingo

    // Serial do primeiro dia a mostrar (completando a semana anterior)
    int serial_primeiro = serial_inicio - inicio_semana;

    // Serial do último dia a mostrar (completando a semana final)
    int serial_ultimo = serial_inicio + dias_mes - 1;
    int fim_semana = serial_ultimo%7;
    int serial_final = serial_ultimo + (6 - fim_semana);

    #define TL "╔"
    #define TR "╗"
    #define BL "╚"
    #define BR "╝"

    #define HZ "═"
    #define VT "║"

    #define TS "╦"
    #define BS "╩"
    #define LS "╠"
    #define RS "╣"

    // Título do calendário
    printf("\n%*s%s", margem, "", TL);
    for (int i = 0; i < 29; i++) printf("%s", HZ);
    printf("%s\n", TR);

    printf("%*s%s     Calendario %3s/%04d     %s\n", margem, "", VT, mmm(mes), ano, VT);

    printf("%*s%s", margem, "", LS);
    for (int i = 0; i < 29; i++) printf("%s", HZ);
    printf("%s\n", RS);

    // Cabeçalho da semana
    printf("%*s%s", margem, " ", VT);
    for (int d = 0; d < 7; d++)
        printf(" %2s ", d_semana(d));
    printf(" %s\n", VT);

    // // Linha separadora entre cabeçalho e dias
    // printf("%*s%c", margem, " ", ls);
    // for (int i = 0; i < 29; i++) printf("%c", hz);
    // printf("%c\n", rs);

    // Dias
    for (int s = serial_primeiro; s <= serial_final; s++) {
        if ((s - serial_primeiro) % 7 == 0) printf("%*s%s", margem, "  ", VT);

        int _dia = (s < serial_inicio) ? dias_no_mes(mes == 1 ? 12 : mes-1, (mes==1? ano-1: ano)) - (serial_inicio - s -1) :
                  (s > serial_inicio + dias_mes -1) ? s - serial_inicio - dias_mes +1 :
                  s - serial_inicio + 1;

        if (_dia==dia) {
            //imprime com cores invertidas, se for o dia escolhido
            printf("\033[7m %2d \033[0m", _dia);
        } else
            printf(" %2d ",  _dia);

        if ((s - serial_primeiro) % 7 == 6) printf(" %s\n", VT);
    }

    // Linha final
    printf("%*s%s", margem, "", BL);
    for (int i = 0; i < 29; i++) printf("%s", HZ);
    printf("%s\n", BR);
}

void alerta(const char *title, const char *message){
    printf("▄▄  %-10s▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n", title);
    printf("█                                               █\n");
    printf("█  %-43s   █\n", message);
    printf("█                                               █\n");
    printf("█────────────────┐──────────────────────────────█\n");
    printf("█       OK       │                              █\n");
    printf("▀────────────────┘──────────────────────────────▀\n");
}
void alerta2(const char *title, const char *message, const char *message2){
    printf("▄▄  %-10s▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄\n", title);
    printf("█                                               █\n");
    printf("█  %-43s   █\n", message);
    printf("█  %-43s   █\n", message2);
    printf("█                                               █\n");
    printf("█────────────────┐──────────────────────────────█\n");
    printf("█       OK       │                              █\n");
    printf("▀────────────────┘──────────────────────────────▀\n");
}
