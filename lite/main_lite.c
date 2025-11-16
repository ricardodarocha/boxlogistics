
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct No_Produto* Produtos = NULL;
struct No_Cliente* Clientes = NULL;
struct No_Caminhao* Caminhoes = NULL;

struct FilaW FilaWdeEntregas;

struct No_Arvore_Carga* G_Raiz_Cargas = NULL;

#include "outros.c"
#include "listaduplaprodutos.c"
#include "listaduplaclientes.c"
#include "listaduplacaminhoes.c"
#include "filaentregas.c"
#include "arvore_cargas.c"

int vOpcao;

void liberarFilaEntregas_main(FilaW* fila) {
    No_Entregas* atual = fila->frente;
    No_Entregas* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    fila->frente = NULL;
    fila->tras = NULL;
    fila->tamanho = 0;
}

void liberarArvoreCargas_main(No_Arvore_Carga* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArvoreCargas_main(raiz->esquerda);
    liberarArvoreCargas_main(raiz->direita);

    liberarFilaEntregas_main(&raiz->dados_carga.entregas_da_carga);

    free(raiz);
}

void liberarListaProdutos_main(No_Produto** cabeca_ref) {
    No_Produto* atual = *cabeca_ref;
    No_Produto* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca_ref = NULL;
}

void liberarListaClientes_main(No_Cliente** cabeca_ref) {
    No_Cliente* atual = *cabeca_ref;
    No_Cliente* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca_ref = NULL;
}

void liberarListaCaminhoes_main(No_Caminhao** cabeca_ref) {
    No_Caminhao* atual = *cabeca_ref;
    No_Caminhao* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca_ref = NULL;
}

void liberarTodaMemoria() {
    printf("Limpando toda a memória alocada...\n");

    liberarArvoreCargas_main(G_Raiz_Cargas);

    liberarFilaEntregas_main(&FilaWdeEntregas);

    liberarListaProdutos_main(&Produtos);
    liberarListaClientes_main(&Clientes);
    liberarListaCaminhoes_main(&Caminhoes);

    printf("Memória liberada com sucesso.\n\n");
}

void MenuLogin() {
    char usuario[20];
    char senha[20];
    int logado = 0;

    while (logado == 0) {
        imprimirCabecalho("Login");
        printf("Usuário..(admin): ");
        scanf(" %19[^\n]", usuario);
        printf("Senha....(admin): ");
        scanf(" %19[^\n]", senha);

        if (strcmp(usuario, "admin") == 0 && strcmp(senha, "admin") == 0) {
            logado = 1;
            printf("\n[SUCESSO] Login realizado com sucesso!\n\n");
            limparTela();
        } else {
            printf("\n[ERRO] Usuário ou senha inválidos!\n\n");
            limparTela();
            boas_vindas_simplificado("VERSÃO LITE                                            ");
        }
    }
}

void MenuPrincipal(){
    do {
        imprimirCabecalho(" Lite 1.0");
        imprimirSubtitulo("MENU PRINCIPAL");
        printf("    [1] - Trocar Usuário\n\n");
        printf("    [2] - Cadastrar Produtos\n");
        printf("    [3] - Cadastrar Clientes\n");
        printf("    [4] - Cadastrar Caminhões\n");
        printf("    [5] - Cadastrar Cargas\n\n");
        printf("    [6] - Vender Produto (Gerar Entrega)\n");
        printf("    [7] - Alocar Entregas em Cargas\n\n");
        printf("    [8] - Relatórios\n\n");
        printf("    [0] - Sair\n\n");

        printf("Digite uma opção: ");
        scanf("%d", &vOpcao);
        printf("\n");


        switch (vOpcao) {
            case 0: {
                limparTelaSemPause();
                imprimirSubtitulo("ATENÇÃO");
                printf("Tem certeza que deseja sair? \n(0 - Sim / 1 - Cancelar): ");
                scanf("%d", &vOpcao);

                do {
                    if (vOpcao == 0) {
                        break;
                    } else if (vOpcao == 1) {
                        printf("\nOperação cancelada.\n\n");
                        printf("Retornando ao menu e limpando tela...\n");
                        limparTela();
                        break;
                    } else {
                        printf("\nDigite uma opção válida!\n\n");
                        printf("Tem certeza que deseja sair? \n(0 - Sim / 1 - Cancelar): ");
                        scanf("%d", &vOpcao);
                    }
                } while (vOpcao != 0);
                break;
            }

            case 1: {
                limparTelaSemPause();
                MenuLogin();
                break;
            }

            case 2: {
                limparTelaSemPause();
                imprimirSubtitulo("CADASTRAR PRODUTO");

                inserirProdutoNoFimLista(&Produtos);

                printf("\nProduto cadastrado com sucesso!\nVoltando ao menu inicial...\n\n");
                limparTela();
                break;
            }

            case 3:{
                limparTelaSemPause();
                imprimirSubtitulo("CADASTRAR CLIENTE");

                inserirClienteNoFimLista(&Clientes);

                printf("\nCliente cadastrado com sucesso!\nVoltando ao menu inicial...\n\n");
                limparTela();
                break;

            }

            case 4:{
                limparTelaSemPause();
                imprimirSubtitulo("CADASTRAR CAMINHÃO");

                inserirCaminhoesNoFimLista(&Caminhoes);

                printf("\nCaminhão cadastrado com sucesso!\nVoltando ao menu inicial...\n\n");
                limparTela();
                break;

            }

            case 5: {
                limparTelaSemPause();
                imprimirSubtitulo("CADASTRAR CARGA");

                static int G_ID_CARGA = 1;

                if (Caminhoes == NULL) {
                    printf("É preciso ter ao menos um caminhão cadastrado.\n");
                    limparTela();
                    break;
                }

                printf("--- Caminhões Disponíveis ---\n");
                imprimirCaminhoes(Caminhoes);

                int idCam;
                printf("\nDigite o ID do Caminhão para esta Carga: ");
                scanf("%d", &idCam);

                No_Caminhao* cam = Caminhoes;
                while (cam != NULL && cam->vId_Caminhao != idCam) {
                    cam = cam->proximo;
                }

                if (cam == NULL) {
                    printf("\nERRO: ID do Caminhão não encontrado!\n");
                    limparTela();
                    break;
                }

                char diaSaida[11];
                printf("Digite a data de saída (DD/MM/AAAA): ");
                scanf(" %10[^\n]", diaSaida);

                Carga novaCarga;
                novaCarga.idCarga = G_ID_CARGA;
                strcpy(novaCarga.diaSaida, diaSaida);
                novaCarga.caminhao_associado = cam;
                novaCarga.peso_atual_kg = 0.0;
                novaCarga.volume_atual_m3 = 0.0;

                iniciarFilaWEntregas(&novaCarga.entregas_da_carga);

                G_Raiz_Cargas = inserirCargaNaArvore(G_Raiz_Cargas, novaCarga);

                printf("\nCarga %d (Placa: %s) planejada com sucesso!\n\n", G_ID_CARGA, cam->vPlaca_Caminhao);
                printf("Use 'Alocar Entregas' para carregar o caminhão.\nVoltando ao Menu Inicial...\n\n");

                G_ID_CARGA++;
                limparTela();
                break;
            }

            case 6: {
                limparTelaSemPause();
                imprimirSubtitulo("VENDER PRODUTO");

                if (Clientes == NULL || Produtos == NULL) {
                    printf("Para vender é preciso possuir ao menos 1 cliente e 1 produto cadastrado!\n\n");
                    limparTela();
                    break;
                }

                static int vId_Entrega = 1;

                printf("Produtos disponíveis para venda:\n\n");

                imprimirProdutos(Produtos);

                int vSelecaoVenda;
                printf("\nDigite o código do produto a ser vendido: ");
                scanf("%d", &vSelecaoVenda);



                No_Produto* ProdutoSelecionado = Produtos;
                while (ProdutoSelecionado->vId_Produto != vSelecaoVenda) {
                    ProdutoSelecionado = ProdutoSelecionado->proximo;
                }

                printf("\n\nClientes disponiveis para a compra: \n\n");

                imprimirClientes(Clientes);

                int vSelecaoClienteVenda;
                printf("\nDigite o código do cliente que fará a compra: ");
                scanf("%d", &vSelecaoClienteVenda);

                No_Cliente* ClienteSelecionado = Clientes;
                while (ClienteSelecionado->vId_Cliente != vSelecaoClienteVenda) {
                    ClienteSelecionado = ClienteSelecionado->proximo;
                }

                enfileirarEntrega(&FilaWdeEntregas, vId_Entrega, ProdutoSelecionado, ClienteSelecionado);
                vId_Entrega ++;

                printf("\nEntrega cadastrada com sucesso!\nVoltando ao menu inicial...\n\n");
                limparTela();
                break;
            }

            case 7: {
                limparTelaSemPause();
                imprimirSubtitulo("ALOCAR ENTREGAS");

                if (G_Raiz_Cargas == NULL) {
                    printf("[ERRO]: Nenhuma carga foi cadastrada ainda.\n\n");
                    limparTela();
                    break;
                }

                if (verificarFilaWEntregasVazia(&FilaWdeEntregas) == 1) {
                    printf("[ERRO]: Nenhuma entrega aguardando na fila geral.\n\n");
                    limparTela();
                    break;
                }

                printf("--- Cargas Planejadas (Vazias ou Parciais) ---\n");
                imprimirCargasEmOrdem(G_Raiz_Cargas);

                int idCarga;
                printf("\nDigite o ID da Carga que deseja carregar: ");
                scanf("%d", &idCarga);

                Carga* cargaAlvo = buscarCargaPorId(idCarga);

                if (cargaAlvo == NULL) {
                    printf("\nERRO: ID da Carga não encontrado!\n");
                    limparTela();
                    break;
                }

                printf("\nIniciando alocação para Carga %d (Caminhão: %s)...\n",
                       cargaAlvo->idCarga, cargaAlvo->caminhao_associado->vPlaca_Caminhao);

                int movidas = 0;
                int tamanhoOriginalFila = FilaWdeEntregas.tamanho;

                for (int i = 0; i < tamanhoOriginalFila; i++) {
                    No_Entregas* entregaAtual = desenfileirarEntregas(&FilaWdeEntregas);

                    if (entregaAtual == NULL) {
                         break;
                    }

                    int sucesso = tentarAlocarEntrega(cargaAlvo, entregaAtual);

                    if (sucesso == 1) {
                        printf("[OK] Entrega %d alocada.\n", entregaAtual->vId_Entrega);
                        movidas++;
                    } else {
                        enfileirarNoMovido(&FilaWdeEntregas, entregaAtual);
                    }
                }

                printf("\nAlocação concluída: %d entregas movidas para a Carga %d.\nVoltando ao Menu Inicial...\n\n", movidas, idCarga);
                limparTela();
                break;
            }

            case 8: {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                int vOpcao_2;
                do {
                    imprimirCabecalho("RELATÓRIOS");
                    imprimirSubtitulo("MENU RELATÓRIOS");
                    printf("    [1] - Produtos Cadastrados\n");
                    printf("    [2] - Clientes Cadastrados\n");
                    printf("    [3] - Caminhões Cadastrados\n\n");
                    printf("    [4] - Entregas (Aguardando Alocação)\n");
                    printf("    [5] - Cargas Planejadas (Árvore)\n\n");
                    printf("    [0] - Voltar ao Menu Inicial\n\n");

                    printf("Digite uma opção: ");
                    scanf("%d", &vOpcao_2);

                    switch (vOpcao_2) {
                        case 0: {
                            limparTelaSemPause();
                            imprimirSubtitulo("ATENÇÃO");
                            printf("Tem certeza que deseja voltar ao Menu Inicial?\n(0 - Sim / 1 - Cancelar): ");
                            scanf("%d", &vOpcao_2);

                            do {
                                if (vOpcao_2 == 0) {
                                    printf("\n");
                                    break;
                                } else if (vOpcao_2 == 1) {
                                    printf("\nOperação cancelada.\n");
                                    printf("Permanecendo no menu Relatórios e limpando tela...\n\n");
                                    system("pause");
                                    system("cls");
                                    break;
                                } else {
                                    printf("\nDigite uma opção válida!\n\n");
                                    printf("Tem certeza que deseja voltar ao Menu Inicial?\n(0 - Sim / 1 - Cancelar): ");
                                    scanf("%d", &vOpcao_2);
                                }
                            } while (vOpcao_2 != 0);
                            break;
                        }

                        case 1: {
                            if (Produtos == NULL) {
                                limparTelaSemPause();
                                imprimirSubtitulo("ATENÇÃO");
                                printf("Nenhum produto cadastrado!\nEscolha outra opção ou volte ao menu inicial para cadastrar um produto.\n\n");
                                limparTela();
                                break;
                            }
                            limparTelaSemPause();
                            imprimirSubtitulo("PRODUTOS CADASTRADOS");
                            imprimirProdutos(Produtos);
                            printf("\n");
                            limparTela();
                            break;
                        }

                        case 2: {
                            if (Clientes == NULL) {
                                limparTelaSemPause();
                                imprimirSubtitulo("ATENÇÃO");
                                printf("Nenhum cliente cadastrado!\nEscolha outra opção ou volte ao menu inicial para cadastrar um cliente.\n\n");
                                limparTela();
                                break;
                            }
                            limparTelaSemPause();
                            imprimirSubtitulo("CLIENTES CADASTRADOS");
                            imprimirClientes(Clientes);
                            printf("\n");
                            limparTela();
                            break;
                        }

                        case 3: {
                            if (Caminhoes == NULL) {
                                limparTelaSemPause();
                                imprimirSubtitulo("ATENÇÃO");
                                printf("Nenhum caminhão cadastrado!\nEscolha outra opção ou volte ao menu inicial para cadastrar um caminhão.\n\n");
                                limparTela();
                                break;
                            }
                            limparTelaSemPause();
                            imprimirSubtitulo("CAMINHÕES CADASTRADOS");
                            imprimirCaminhoes(Caminhoes);
                            printf("\n");
                            limparTela();
                            break;
                        }

                        case 4: {
                            if (verificarFilaWEntregasVazia(&FilaWdeEntregas) == 1) {
                                limparTelaSemPause();
                                imprimirSubtitulo("ATENÇÃO");
                                printf("Nenhuma entrega aguardando alocação!\n\n");
                                limparTela();
                                break;
                            }
                            limparTelaSemPause();
                            imprimirSubtitulo("ENTREGAS AGUARDANDO");
                            imprimirFilaWEntregas(&FilaWdeEntregas);
                            limparTela();
                            break;
                        }

                        case 5: {
                            if (G_Raiz_Cargas == NULL) {
                                limparTelaSemPause();
                                imprimirSubtitulo("ATENÇÃO");
                                printf("Nenhuma carga foi planejada ainda!\n\n");
                                limparTela();
                                break;
                            }
                            limparTelaSemPause();
                            imprimirSubtitulo("CARGAS PLANEJADAS");
                            imprimirCargasEmOrdem(G_Raiz_Cargas);
                            printf("\n\n");
                            limparTela();
                            break;
                        }

                        default: {
                            limparTelaSemPause();
                            imprimirSubtitulo("OPÇÃO INVÁLIDA");
                            printf("Digite uma opção válida.\n\n");
                            limparTela();
                            break;
                        }
                    }
                } while (vOpcao_2 != 0);

                limparTelaSemPause();
                break;
            }

            default: {
                printf("\n\n=====   OPÇÃO INVÁLIDA  =====\nDigite uma opção válida.\nVoltando ao Menu Inicial...\n\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while (vOpcao != 0);

    limparTelaSemPause();
    imprimirCabecalho(" Lite 1.0");
    liberarTodaMemoria();
    printf("Saindo...\nObrigado por usar o sistema Lite BoxLogistics!\n\n");
}

int main_lite() {
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    MenuLogin();
    MenuPrincipal();

    return 0;
}