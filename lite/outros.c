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

void imprimirCabecalho(const char* titulo) {
    printf("\n===================================================\n");
    printf("||  BoxLogistics - %-28s  ||\n", titulo);
    printf("===================================================\n\n");
}

void imprimirSubtitulo(const char* subtitulo) {
    printf("\n=============================\n");
    printf("||   %-20s  ||\n", subtitulo);
    printf("=============================\n\n");
}