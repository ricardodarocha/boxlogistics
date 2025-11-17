#include <stdlib.h>
#include <visual.h>

void limparTela() {
    system("pause");
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparTelaSemPause() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//MANTEM O PADRAO
void imprimirCabecalho(const char* titulo) {
    printf("\x1b[2J\x1b[H");
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                        9v23  ║\n");
    printf("  ║              BOX LOGISTICS SYSTEM  -  v0.1 (2025)            ║\n");
    printf("  ║             ──────────────────────────────────────           ║\n");
    printf("  ║              © 2025  Box Logistics - Lite Version            ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════╝\n");
    printf("   \x1b[7mVOCE ESTA NA VERSAO LITE\x1b[0m                  \n");
}

void imprimirSubtitulo(const char* subtitulo) {

    boas_vindas_simplificado(subtitulo);
}

void banner_lite() {
    printf("\n    \x1b[7mVOCE ESTA NA VERSAO LITE\x1b[0m\n");
}


// void imprimirCabecalho(const char* titulo) {
//     printf("\n===================================================\n");
//     printf("||  BoxLogistics - %-28s  ||\n", titulo);
//     printf("===================================================\n\n");
// }
//
// void imprimirSubtitulo(const char* subtitulo) {
//     printf("\n=============================\n");
//     printf("||   %-20s  ||\n", subtitulo);
//     printf("=============================\n\n");
// }