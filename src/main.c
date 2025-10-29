#include "../lib/menu.c"
#include "../models/bd.c"

const char *menu_principal =
    "(1) Cadastrar\n"
    "(2) Evento\n"
    "(3) Relatório\n"
    "(0) Sair\n";

const char *menu_cadastrar =
    "(1) Cadastro de Produto\n"
    "(2) Cadastro de Cliente\n"
    "(0) Voltar\n";

const char *menu_evento =
    "(1) Pesar Mercadoria\n"
    "(2) Enviar Mensagem\n"
    "(0) Voltar\n";

const char *menu_relatorio =
    "(1) Vendas do Dia\n"
    "(2) Estoque Atual\n"
    "(0) Voltar\n";

int executar_menu_cadastrar(){
  int operacao =  exibir_menu(menu_cadastrar);
}

int executar_menu_evento(){
  int operacao =  exibir_menu(menu_evento);
}

int executar_menu_relatorio(){
  int operacao =  exibir_menu(menu_relatorio);
}
int main() {
    conectar_bd();

    while (1) {
        int operacao = exibir_menu();
        switch (operacao) {
            case 1: {
                executar_menu_cadastrar()
                break;
            }
            case 2:
                executar_menu_evento();
                break;
            case 3:
                executar_menu_relatorio();
                break;
            case 0:
                // encerrar o programa
                desconectar_bd();
                return 0;
            default:
                printf("operacao invalida \n");
        }
    }
}
