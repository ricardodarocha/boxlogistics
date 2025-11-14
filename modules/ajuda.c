#include <stdio.h>
#include <stdlib.h>
#include "visual.h"

void ajuda_geral() {

    system("cls");

    printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                     AJUDA DO SISTEMA – BOX LOGISTICS             ║\n");
    printf("  ║                         Versão 0.1  (2025)                       ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════════╝\n\n");

    printf("  ┌──────────────────────────────────────────────────────────────────┐\n");
    printf("  │                           INTRODUÇÃO                             │\n");
    printf("  └──────────────────────────────────────────────────────────────────┘\n");
    printf("   O sistema BOX LOGISTICS foi desenvolvido para gerenciar produtos,\n");
    printf("   entregas, cargas e vendas de forma simples, rápida e intuitiva.\n");
    printf("   Este módulo de ajuda fornece uma visão geral das funções e como\n");
    printf("   navegar pelas principais operações do sistema.\n\n");

    printf("  ┌──────────────────────────────────────────────────────────────────┐\n");
    printf("  │                              ÍNDICE                              │\n");
    printf("  └──────────────────────────────────────────────────────────────────┘\n");
    printf("   1. Cadastro de Produtos\n");
    printf("   2. Sistema de Entregas\n");
    printf("   3. Montagem de Cargas\n");
    printf("   4. Relatórios e Consultas\n");
    printf("   5. Suporte e Informações\n\n");
    printf("   6. Guia de estilos\n\n");

    int opera;
    input_inteiro(   "   Escolha uma opcao ", &opera);

    if (opera==1) {
        printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
        printf("  ║                     1) CADASTRO DE PRODUTOS                      ║\n");
        printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
        printf("   • Inclui novos produtos no sistema.\n");
        printf("   • Permite buscar produtos pelo código.\n");
        printf("   • Aceita listagem completa para conferência.\n");
        printf("   • Ideal para cadastros iniciais ou atualizações.\n\n");
    }

    if (opera==2) {
    printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                       2) SISTEMA DE ENTREGAS                     ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("   • Localize um produto e atribua a um cliente.\n");
    printf("   • Cadastro automático de cliente caso não exista.\n");
    printf("   • Permite adicionar múltiplos itens para a mesma entrega.\n");
        printf("   • Armazena endereço, CPF e informações do destinatário.\n\n");
    }

    if (opera==3) {

    printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                        3) MONTAGEM DE CARGAS                     ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("   • Reune diversas entregas em uma única carga.\n");
    printf("   • Cada carga possui um TICKET (código de rastreio).\n");
    printf("   • Entregas podem ser listadas e selecionadas para inclusão.\n");
        printf("   • Usado para gerar o romaneio para expedição.\n\n");
    }

    if (opera==4) {

    printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                   4) RELATÓRIOS E CONSULTAS                      ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("   • Relatório de produtos\n");
    printf("   • Relatório de entregas\n");
    printf("   • Relatório de cargas (Romaneio)\n");
    printf("   • Pesquisas por código ou data\n");
        printf("   • Ideal para conferências e auditorias\n\n");
    }

    if (opera==5) {

    printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
    printf("  ║                   5) SUPORTE E INFORMAÇÕES                       ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
    printf("   • Para dúvidas, consulte o administrador do sistema.\n");
    printf("   • Em caso de falhas, reinicie o aplicativo.\n");
    printf("   • Consulte atualizações na versão futura.\n");
        printf("   • Este sistema segue o padrão de ajuda do Windows 2000.\n\n");
    }

    if (opera==6) {

        printf("  ╔══════════════════════════════════════════════════════════════════╗\n");
        printf("  ║                  6) GUIA DE ESTILOS DO SISTEMA                  ║\n");
        printf("  ╚══════════════════════════════════════════════════════════════════╝\n");
        printf("   O sistema BOX LOGISTICS utiliza padrões visuais definidos para\n");
        printf("   manter uma identidade consistente nas telas, caixas, menus e\n");
        printf("   relatórios do terminal. Abaixo estão os estilos principais:\n\n");

        printf("      ╔════════════════════════════╗     Estética Premium / Bold\n");
        printf("      ║          Premium           ║     Layout forte, títulos marcados.\n");
        printf("      ╚════════════════════════════╝\n\n");

        printf("      ┌────────────────────────────┐     Estética Clean / Slim\n");
        printf("      │    Fine / Minimalista      │     Uso leve de bordas.\n");
        printf("      └────────────────────────────┘\n\n");

        printf("      ┌──══──────────────—────────═╗     Estética Gothic / Dark\n");
        printf("      │  Gothic / Daftpunk Style   │     Aparência futurista/dark.\n");
        printf("      └─────────────────────────┘──┘\n\n");

        printf("      ╔════════════════╦═══════════╗     Estética Soft / Hybrid\n");
        printf("      ║   Híbrido –────├--- Bold   ║     Mistura clean com elementos premium.\n");
        printf("      ╚════════════════╩═══════════╝\n\n");
    }

    printf("  ┌──────────────────────────────────────────────────────────────────┐\n");
    printf("  │                         COPYRIGHT © 2025                         │\n");
    printf("  │                       BOX LOGISTICS SYSTEM                       │\n");
    printf("  └──────────────────────────────────────────────────────────────────┘\n\n");
    printf("  ┌──────────────────────────────────────────────────────────────────┐\n");
    printf("  │               Pressione qualquer tecla para voltar               │\n");
    printf("  └──────────────────────────────────────────────────────────────────┘\n");
    system("pause");
}

void ajuda_sistema_entregas() {

    printf("                           ┌───────────────────────┐\n");
    printf("                           │   Início do Processo  │\n");
    printf("                           └───────────┬───────────┘\n");
    printf("                                       │\n");
    printf("                                       ▼\n");
    printf("                       ┌────────────────────────────────┐\n");
    printf("                       │ Localizar produto no sistema   │\n");
    printf("                       └───────────────┬────────────────┘\n");
    printf("                                       │\n");
    printf("                                       ▼\n");
    printf("                     ┌───────────────────────────────────┐\n");
    printf("                     │   Usuário digita CPF do cliente   │\n");
    printf("                     └─────────────────┬─────────────────┘\n");
    printf("                                       │\n");
    system(("pause"));
    printf("                                       ▼\n");
    printf("                ┌────────────────────────────────────────────┐\n");
    printf("                │       CPF existe no banco de dados?        │\n");
    printf("                └───────────┬────────────────────────┬───────┘\n");
    printf("                            │Sim                     │Não\n");
    printf("                            ▼                        ▼\n");
    printf("          ┌─────────────────────────┐       ┌──────────────────────────────┐\n");
    printf("          │ Carregar dados cliente  │       │   Coletar dados do cliente   │\n");
    printf("          └───────────┬─────────────┘       └──────────────────────────────┘\n");
    printf("                      │                                   │\n");
    printf("                      └──────────────────┬────────────────┘\n");
    printf("                                         │\n");
    printf("                                         ▼\n");
    printf("                       ┌─────────────────────────────────┐\n");
    printf("                       │   Inserir produto na entrega    │\n");
    printf("                       └─────────────────┬───────────────┘\n");
    printf("                                         │\n");
    system(("pause"));
    printf("                                         ▼\n");
    printf("                 ┌─────────────────────────────────────────────────┐\n");
    printf("                 │     Deseja inserir mais um produto? (S/N)       │\n");
    printf("                 └───────┬─────────────────────────────┬───────────┘\n");
    printf("                         │S                            │N       \n");
    printf("                         ▼                             ▼       \n");
    printf("        ┌─────────────────────────────┐  ┌───────────────────────────┐\n");
    printf("        │ Volta para localizar produto│  │ Finalizar e salvar entrega│\n");
    printf("        └─────────────────────────────┘  └─────────────┬─────────────┘\n");
    printf("                                                       │\n");
    printf("                                                       ▼\n");
    printf("                                           ┌──────────────────────────┐\n");
    printf("                                           │        Fim do fluxo      │\n");
    printf("                                           └──────────────────────────┘\n");

}