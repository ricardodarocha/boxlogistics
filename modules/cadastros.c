#include "../include/bd.h"
#include "../include/cadastros.h"

#include "calendario.h"
#include "data.h"
#include "../include/visual.h"
#include "../modules/produtos.c"
#include "../modules/clientes.c"
#include "../include/entrega.h"
#include "../include/carga.h"
#include "../modules/vendas.c"
#include "../include/historico.h"

typedef struct {
  int total_itens;
  float soma_valores;
} AcumuladorCarga;

// ================= indicadores  ====================
int qtd_produtos( ) {
  return cursor_proximo_produto();
}

int qtd_entregas( ) {
  return cursor_proxima_entrega();
}
int qtd_cargas( ) {
  return cursor_proxima_carga();
}

int qtd_vendas( ) {
  return cursor_proxima_venda();
}
//==========================================

int inserir_produto(){
    Produto * novo_produto = alocar_produto();

  //==================== ler os campos do produto ====================
    printf(      "              ID: %03d\n", novo_produto->id);
    input_string("NOME DO PRODUTO", novo_produto->nome, sizeof(novo_produto->nome));
    input_float(   "          VALOR", &novo_produto->valor);
  //==================================================================

  //==================== validar =====================================
    validar_produto(novo_produto);
  //==================================================================

  //==================== inserir no banco de dados ===================
    inserirListaDupla(&bd()->produtos, novo_produto);
    return novo_produto->id;
  //==================================================================
}

void imprimir_ficha_produto(Produto * pro) {
  if (pro == NULL) {
    printf("  ┌──────────────────────────────────────────────────────────────┐\n");
    printf("  │                     PRODUTO INDISPONIVEL                     │\n");
    printf("  └──────────────────────────────────────────────────────────────┘\n");
    return;
  }
  printf("  ┌──────────────────────────────────────────────────────────────┐\n");
  printf("  │               PRODUTO DISPONIVEL %-4d                        │\n", pro->id);
  printf("  ├─────────────────────┬────────────────────────────────────────┤\n");
  printf("  │           DESCRICAO │ %s\n", pro->nome);
  printf("  │               PRECO │ %-11.2f %26s │\n", pro->valor, "");
  printf("  └─────────────────────┴────────────────────────────────────────┘\n");
}

void * buscar_produto(const int id) {
    Produto chave = {0};
    chave.id = id;
    Produto *encontrado = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
    return encontrado;
}

// Retorna 0 se nao encontrado
int buscar_produto_id(const int id) {
    Produto * encontrado = buscar_produto(id);
    if (encontrado) {
      return encontrado->id;
    }
    return 0;
}

void listar_produtos() {
  imprimir_cabecalho_produto();
  imprimirDuplo(bd()->produtos, iprimir_produto);
  system("pause");
}
void listar_clientes() {
  imprimir_cabecalho_cliente();
  imprimirDuplo(bd()->clientes, iprimir_cliente);
  system("pause");
}

void imprimir_ficha_produto_id(int id) {
  Produto* pro = buscar_produto(id);
  imprimir_ficha_produto(pro);
}

void imprimir_produto_id(int id) {
  imprimir_ficha_produto_id(id);
}

//==========================================

Cliente *buscar_cpf(const int cpf) {
  Cliente chave = {0};
  chave.cpf = cpf;
  Cliente *encontrado = pesquisarDuplo(bd()->clientes, &chave, localizar_cpf);
  return encontrado;
}

int inserir_cliente(){
  int cpf;
  input_inteiro(   "             CPF", &cpf);
  Cliente *ja_existe = buscar_cpf(cpf);
  if (ja_existe) {
    //==================== o cliente ja existe  ====================
    printf("\n║       (1) CLIENTE ENCONTRADO    \n");
    printf(  "║                 ID: %03d\n", ja_existe->id);
    printf(  "║    NOME DO CLIENTE: %s\n", ja_existe->nome);

    return ja_existe->id;
  };

  Cliente * novo_cliente = alocar_cliente();
  //==================== ler os campos do cliente ====================
  input_string("NOME DO CLIENTE", novo_cliente->nome, sizeof(novo_cliente->nome));
  // printf("                   CPF: %d", cpf);
  novo_cliente->cpf = cpf;

  // validar_cliente(novo_cliente);
  inserirListaDupla(&bd()->clientes, novo_cliente);
  return novo_cliente->id;
}

void * buscar_cliente(const int id) {
  Cliente chave = {0};
  chave.id = id;
  Cliente *encontrado = pesquisarDuplo(bd()->clientes, &chave, localizar_cliente);
  if (encontrado) {
    return encontrado;
  }
    return NULL;
}

//====================
int imprimir_ficha_entrega(Entrega * entrega, Produto * produto) {
  printf("  ┌──────────────────────────────────────────────────────────────┐\n");
  printf("  │               FICHA DE ENTREGA %-4d                          │\n", entrega->id);
  printf("  ├─────────────────────┬────────────────────────────────────────┤\n");
  printf("  │        DESTINATARIO │ %-38s │\n", entrega->destinatario);
  printf("  └─────────────────────┼────────────────────────────────────────┘\n");
  printf("  ┌─────────────────────┬────────────────────────────────────────┐\n");
  printf("  │                  ID │ %03d            1×%.0f\n", entrega->id_produto, entrega->valor);
  printf("  │             PRODUTO │ %s\n", produto->nome);
  printf("  └─────────────────────┴────────────────────────────────────────┘\n");
}

int inserir_entregas(int id_produto, int *id_cliente_ptr) {
    if (id_cliente_ptr == NULL) {
        alerta("ERRO", "Ponteiro id_cliente invalido\n");
        return 0;
    }

    if (id_produto == 0) {
        alerta("AVISO", "PRODUTO NAO ENCONTRADO\n");
        return 0;
    }

    /* Buscar produto */
    Produto chave_produto = {0};
    chave_produto.id = id_produto;
    Produto *pe = pesquisarDuplo(bd()->produtos, &chave_produto, localizar_produto);
    if (!pe) {
        char msg[128];
        snprintf(msg, sizeof(msg), "PRODUTO NAO ENCONTRADO (id=%d)\n", id_produto);
        alerta("AVISO", msg);
        return 0;
    }
    imprimir_ficha_produto(pe);

    /* Se id_cliente não definido, inserir cliente */
    if (*id_cliente_ptr == 0) {
        printf("\n  ┌──────────────────────────────────┐\n");
        printf("  │   INFORME OS DADOS DO CLIENTE    │\n");
        printf("  └──────────────────────────────────┘\n\n");

        int novo_id = inserir_cliente();
        if (novo_id == 0) {
            alerta("ERRO", "ERRO AO INSERIR O CLIENTE\n");
            return 0;
        }
        *id_cliente_ptr = novo_id;
    }

    if (*id_cliente_ptr == 0) {
        alerta("ERRO", "ERRO AO OBTER ID DO CLIENTE\n");
        return 0;
    }

    /* Alocar entrega (alocar_entrega deve usar calloc ou inicializar tudo) */
    Entrega *nova = alocar_entrega();
    if (!nova) {
        alerta("AVISO", "ERRO AO ALOCAR ENTREGA");
        return 0;
    }

    /* Inicializar campos básicos */
    nova->id_produto = pe->id;
    nova->valor = pe->valor;
    nova->quant = 1.0;

    /* Buscar cliente (verifica retorno) */
    Cliente *cliente_encontrado = buscar_cliente(*id_cliente_ptr);
    if (!cliente_encontrado) {
        alerta("ERRO", "CLIENTE NAO ENCONTRADO");
        free(nova);
        return 0;
    }

    /* Copiar nome de forma segura */
    strncpy(nova->destinatario, cliente_encontrado->nome, sizeof(nova->destinatario) - 1);
    nova->destinatario[sizeof(nova->destinatario) - 1] = '\0';

    /* Preparar buffer de mensagem e validar entrega */
    char mensagem[256];
    mensagem[0] = '\0';

    /* Se a sua validar_entrega tem outra assinatura, ajuste aqui */
    int val_ok = validar_entrega(nova, mensagem);
    if (!val_ok) {
        /* mostrar erro e abortar */
        char warnbuf[256];
        snprintf(warnbuf, sizeof(warnbuf), "Validacao falhou: %s\n", mensagem);
        alerta("AVISO", warnbuf);
        free(nova);
        return 0;
    }

    imprimir_ficha_entrega(nova, pe);

    /* Verifica fila e enfileira */
    Fila *f = bd()->entregas;
    if (!f) {
        alerta("AVISO", "FILA DE ENTREGAS NAO INICIALIZADA");
        free(nova);
        return 0;
    }

    enfileirar(f, nova);

    /* sucesso */
    return nova->id;
}

void buscar_entrega(const int id) {
  Entrega chave_entrega = {0};
  Entrega *entrega_encontrada = NULL;
  Produto chave_produto = {0};
  Produto *produto_encontrado = NULL;

  chave_entrega.id = id;
  entrega_encontrada = buscarFila(bd()->entregas, &chave_entrega, localizar_entrega);
  if (entrega_encontrada) {
    int id_produto = entrega_encontrada->id_produto;
    chave_produto.id = id_produto;
    produto_encontrado = (Produto *) pesquisarDuplo(bd()->produtos, &chave_produto, localizar_produto);
    if (produto_encontrado) {
      printf("\nENCONTRADO: %03d (1) %s -> %s\n",
      produto_encontrado->id,             //   id do produto
      produto_encontrado->nome,           // nome do produto
      entrega_encontrada->destinatario);  // nome do destinatario
    }
  }
  imprimir_ficha_entrega(entrega_encontrada, produto_encontrado);
}

int buscar_entrega_id(const int id) {
  Entrega chave = {0};
  Entrega *encontrado = NULL;
  chave.id = id;
  encontrado = buscarFila(bd()->entregas, &chave, localizar_entrega);
  if (encontrado) {
    return encontrado->id;
  }
  return 0;
}

void imprimir_produto_entrega(Produto * p, float valor){
  printf("");
  printf("  │ | %03d %-43s %8.2f │\n", p->id, p->nome, valor);
}

/** Esta funcao especial cria um agrupamento pelo campo destinatario\n
 *  vai permitir imprimir assim
 *  \code
        id nome               quant
       ──────────────────────────────
        E1 JOSE MATIAS
        P1 LIMAO              300,0
        P1 TOMATE              23,0
      ──────────────────────────────
    \endcode
 *
 * @param dado  a funcao para imprimir uma entrega
 * @param destinatario o agregador
 */
void iprimir_entrega_ag(void *dado, char * destinatario[SIZES], float * agregado) {
  Entrega * e= dado;
  printf("\n");
  if (strcmp(*destinatario, e->destinatario) != 0) {
    if (*agregado > 0.0)
      printf("  │                                              R$ %10.2f │\n", *agregado);

    *agregado = 0.0;
    printf("  ├──────────────────────────────────────────────────────────────┐\n");
    printf("  │                        ENTREGA %-4d                          │\n", e->id);
    printf("  ├─────────────────────┬────────────────────────────────────────┤\n");
    printf("  │        DESTINATARIO │ %-38s │\n", e->destinatario);
    printf("  ├─────────────────────└────────────────────────────────────────┤\n");
    *destinatario = e->destinatario ;
  }

  Produto chave = {0};
  chave.id = e->id_produto;
  Produto *p = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
  imprimir_produto_entrega(p, e->valor );
  *agregado += e->valor;

}

void imprimir_rodape_entrega(float quanti, float soma) {
  printf("\n");
  printf("  ├──────────────────────────────────────────────────────────────┤\n");
  printf("  │ TOTAL %2d itens                                R$ %10.2f  │\n",
         quanti, soma);
  printf("  └──────────────────────────────────────────────────────────────┘\n");
}

float somar_entregas() {

  if (bd()->entregas == NULL || bd()->entregas->inicio == NULL) {
    return 0.0;
  }
  float soma = 0.0;
  for (FilaX *cur = bd()->entregas->inicio; cur; cur = cur->proximo) {
    Entrega *e = cur->dado;
    soma += e->valor;
  }
  return soma;

}

void listar_entregas() {
  imprimir_cabecalho_entrega();
  char * destinatario [SIZES];
  destinatario[0] = "\0";
  float agregado = 0.0;
  imprimirFilaAg(bd()->entregas, iprimir_entrega_ag, destinatario, &agregado);
  int quanti = qtd_entregas();
  float soma = somar_entregas();
  imprimir_rodape_entrega(quanti, soma);
  system("pause");
}
//==========================================

static void imprimir_carga_relatorio(void *dado) {
    imprimir_carga(dado, imprimir_entrega);
}

void listar_cargas() {
    Arvore *raiz = bd()->cargas;

    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║                     RELATÓRIO DE CARGAS                      ║\n");
    printf(  "  ╠══════════════════════════════════════════════════════════════╣\n");

    if (!raiz) {
        printf("   ║                Nenhuma carga cadastrada.              ║\n");
        printf("   ╚═══════════════════════════════════════════════════════╝\n");
        return;
    }

    imprimir_cabecalha_carga();
    imprimirArvore(raiz, imprimir_carga_relatorio);


  printf("  ╠══════════════════════════════════════════════════════════════╣\n");
  printf("  ║ TOTAL DE CARGAS: %4d                       TOTAL: %9.2f ║\n",
         qtd_cargas(), 0);
  printf("  ╚══════════════════════════════════════════════════════════════╝\n");
  system("pause");
}

static void acumular_e_imprimir(void *dado, AcumuladorCarga *acc) {
    Carga *c = dado;

    imprimir_carga(c, imprimir_entrega);

    acc->total_itens += 1;
    acc->soma_valores += c->valor;
}

static void inorder_acumular(Arvore *raiz, AcumuladorCarga *acc) {
    if (!raiz) return;
    inorder_acumular(raiz->esq, acc);
    acumular_e_imprimir(raiz->dado, acc);
    inorder_acumular(raiz->dir, acc);
}

void buscar_carga(const int dia) {
  buscarArvoreId(bd()->cargas, dia);
  // imprimir_ficha_carga();
}

// encontrado = pesquisarDuplo(bd()->produtos, &chave, localizar_produto

void incluir_entrega_na_carga(int id_entrega, int *id_carga) {

    // ------------------------------------------------------------
    // 1. Buscar entrega
    // ------------------------------------------------------------
    Entrega chave_entrega = {0};
    chave_entrega.id = id_entrega;

    Entrega *entrega = buscarFila(bd()->entregas, &chave_entrega, localizar_entrega);
    if (!entrega) {
        alerta("AVISO", "Entrega não encontrada!");
        return;
    }

    // ------------------------------------------------------------
    // 2. Tentar localizar carga existente (por ID, se informado)
    // ------------------------------------------------------------
    Carga chave_carga = {0};
    chave_carga.id = *id_carga;

    Carga *carga_encontrada = NULL;

    if (*id_carga > 0) {
        carga_encontrada = buscarArvore(bd()->cargas,
                                        &chave_carga,
                                        localizar_carga);
    }

    // ------------------------------------------------------------
    // 3. Se carga não existe, pedir data e procurar carga por data
    // ------------------------------------------------------------
    char data_carga[SIZEDATE];
    int serial_data = 0;

    if (!carga_encontrada) {
        do {
            input_data_valid("   Insira a data da carga", data_carga);
            serial_data = serial_de_data_str(data_carga);

            if (serial_data <= 0)
                alerta2("ERRO", "Data inválida", data_carga);

        } while (serial_data <= 0);

        chave_carga.id = serial_data;
        carga_encontrada = buscarArvore(bd()->cargas,
                                        &chave_carga,
                                        localizar_carga);
    }

    // ------------------------------------------------------------
    // 4A. Se carga existe → inserir a entrega nela
    // ------------------------------------------------------------
    if (carga_encontrada) {

        *id_carga = carga_encontrada->id;

        Fila *fila = (Fila*) carga_encontrada->entregas;

        if (!fila) {
            fila = criarFila();
            enfileirar(fila, entrega);
            carga_encontrada->entregas = fila;
        } else {
            enfileirar(fila, entrega);
        }

        return;
    }

    // ------------------------------------------------------------
    // 4B. Se carga NÃO existe → criar carga nova
    // ------------------------------------------------------------
    Carga *nova = alocar_carga();
    nova->id   = serial_data;
    nova->data = serial_data;

    // Inserir entrega na nova fila
    Fila *nova_fila = criarFila();
    enfileirar(nova_fila, entrega);
    nova->entregas = nova_fila;

    // Inserir na árvore → ATENÇÃO: precisa ATRIBUIR a nova raiz!
    bd()->cargas = inserirArvore(bd()->cargas, nova->id, nova);

    *id_carga = nova->id;
}

void imprimir_resumo(void * c) {
  Carga *carga = c;
  printf("  │  %02d │ %-10s     │       │", carga->id, carga->nome, carga->valor);
}

//imprime apenas os dados basicos
void listar_resumo_cargas() {
  //
  // ┌─────┬─────────────────┬───────┐
  // │ ID  │  DATA           │ SETOR │
  // ┼─────┼─────────────────┼───────┼
  // │ 01  │  21/03/2026     │ SUD   │
  // │ 02  │  21/03/2026     │ SUD   │
  // │ 03  │  21/03/2026     │ SUD   │
  // └─────┼─────────────────┼───────┘
  //
  printf("  ┌─────┬─────────────────┬───────┐\n");
  printf("  │ ID  │  DATA           │ SETOR │\n");
  printf("  ┼─────┼─────────────────┼───────┼\n");
  imprimirArvore(bd()->cargas, imprimir_resumo);
  printf("  └─────┼─────────────────┼───────┘\n");
}

int inserir_vendas(const int id) {

  return 0;
}
void * buscar_vendas() {

}
void listar_vendas() {

}

void imprimir_cabecalho_historico(){
  printf("Entregas recem carregadas");

}

void listar_historico() {
  imprimir_cabecalho_historico();
  char * destinatario [SIZES];
  destinatario[0] = "\0";
  float agregado = 0.0;
  imprimirFilaAg(((void*)  ((Historico*)bd()->historico )->entrega), iprimir_entrega_ag, destinatario, &agregado);
  int quanti = qtd_entregas();
  float soma = somar_entregas();
  imprimir_rodape_entrega(quanti, soma);
  system("pause");
}

//cadastra dados de exemplo
void migrations() {
  // inserirListaDupla( bd() -> clientes, novo_cliente("LAMPARINA VITRIFICADA", 99.99));

  // inserirListaDupla( bd() -> produtos, novo_produto("LAMPARINA VITRIFICADA", 99.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("GOMA DE MASCAR", 9.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("ESTILINGUE", 29.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("CERA DE ABELHA", 99.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("ARMADURA DE LENHADOR", 99.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("BOTINA DE COURO", 99.99));
  // inserirListaDupla( bd() -> produtos, novo_produto("BOTAS DE BORRACHA", 99.99));
  // inserirListaDupla( bd()->produtos, novo_produto("AMPOLA DE GENIO ENGARRAFADO", 199.99));
  // inserirListaDupla( bd()->produtos, novo_produto("BOBINA DE INDUÇÃO GALVANIZADA", 349.90));
  // inserirListaDupla( bd()->produtos, novo_produto("ELETRODO DE COBRE VITORIANO", 89.50));
  // inserirListaDupla( bd()->produtos, novo_produto("LÂMPADA DE PLASMA EXPERIMENTAL", 159.99));
  // inserirListaDupla( bd()->produtos, novo_produto("TÚBOS DE VIDRO CRIOGÊNICO", 79.99));
  // inserirListaDupla( bd()->produtos, novo_produto("VELA DE LABORATÓRIO ", 19.99));
  // inserirListaDupla( bd()->produtos, novo_produto("COMPILADOR DE CELULA ARTIFICIAL", 899.99));
  // inserirListaDupla( bd()->produtos, novo_produto("TECIDOS BIO-ELETRIFICADOS", 349.99));
  // inserirListaDupla( bd()->produtos, novo_produto("PONTE DE GRAFITE ", 229.90));
  // inserirListaDupla( bd()->produtos, novo_produto("FRASCO VAPORIZADOR ", 189.99));
  // inserirListaDupla( bd()->produtos, novo_produto("CATALISADOR ALFA 88", 999.99));

  //inserirArvore( bd()->cargas, 25, nova_carga("CLIENTE 1", 999.99));

}

void vender() {
  vender_agora();
}
