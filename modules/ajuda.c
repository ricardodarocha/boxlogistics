#include <stdio.h>
#include <stdlib.h>

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
