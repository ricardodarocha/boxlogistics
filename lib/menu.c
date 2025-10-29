
int exibir_menu(const char *operacoes) {
    imprimir_nome_sistema();
    printf("%s", operacoes);

    int menu_escolhido;
    printf("Escolha uma opção: ");
    scanf("%d", &menu_escolhido);
    getchar(); 
    return menu_escolhido;
}
