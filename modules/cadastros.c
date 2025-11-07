#include "../include/bd.h"
#include "../include/cadastros.h"
#include "../include/visual.h"
#include "../modules/produtos.c"
#include "../modules/clientes.c"
#include "../modules/entregas.c"
#include "../modules/cargas.c"
#include "../modules/vendas.c"

// ================= indicadores  ====================
int qtd_produtos(void) {
  return cursor_proximo_produto();
}

int qtd_entregas(void) {
  return 0;
}

int qtd_cargas(void) {
  return 0;
}

int qtd_vendas(void) {
  return 0;
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

void * buscar_produto(const int id) {
    Produto chave = {0};
    Produto *encontrado = NULL;
    chave.id = id;
    encontrado = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
    if (encontrado) {
      return encontrado;
    }
    return NULL;
}

int buscar_produto_id(const int id) {
    Produto chave = {0};
    Produto *encontrado = NULL;
    chave.id = id;
    encontrado = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
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
    printf(      "║       (1) CLIENTE ENCONTRADO    ");
    printf(      "║                ID: %03d\n", ja_existe->id);
    printf(      "║   NOME DO CLIENTE: %s", ja_existe->nome);
    printf("                      CPF: %d", cpf);

    return ja_existe->id;
  };

  Cliente * novo_cliente = alocar_cliente();
  //==================== ler os campos do cliente ====================
  printf(      "              ID: %03d\n", novo_cliente->id);
  input_string("NOME DO CLIENTE", novo_cliente->nome, sizeof(novo_cliente->nome));
  printf("                   CPF: %d", cpf);
  novo_cliente->cpf = cpf;

  validar_cliente(novo_cliente);
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

void listar_clientes() {
  imprimir_cabecalho_cliente();
  imprimirDuplo(bd()->clientes, iprimir_cliente);
  system("pause");
}
//====================

int inserir_entregas(int id_produto, int *id_cliente) {
    // --- Pré-condição: id_produto já deve ser válido (executar_cadastro_entregas o garantiu) ---
    // Se quiser dupla verificação, use uma função que apenas teste existência sem remapear.
    if (id_produto == 0) {
        printf("PRODUTO NAO ENCONTRADO (id_produto==0)\n");
        return 0;
    }

    // Se id_cliente não definido, criar e guardar no ponteiro
    if (id_cliente == NULL) {
        printf("PONTEIRO id_cliente inválido\n");
        return 0;
    }

    if (*id_cliente == 0) {
    printf("  ┌──────────────────────────────────┐");
    printf("  │   INFORME OS DADOS DO CLIENTE    │");
    printf("  └──────────────────────────────────┘");
        printf(" \n");
        *id_cliente = inserir_cliente();
    }

    if (*id_cliente == 0) {
        printf("ERRO AO INSERIR CLIENTE\n");
        return 0;
    }

    // Buscar e validar o cliente
    Cliente chave_cliente = {0};
    chave_cliente.id = *id_cliente;
    Cliente *cliente_encontrado =
        pesquisarDuplo(bd()->clientes, &chave_cliente, localizar_cliente);
    if (!cliente_encontrado) {
        printf("CLIENTE NAO ENCONTRADO (id=%d)\n", *id_cliente);
        return 0;
    }

    // Buscar e validar o produto (aqui assumimos id_produto já ok, mas conferimos na BD)
    Produto chave_produto = {0};
    chave_produto.id = id_produto;
    Produto *produto_encontrado =
        pesquisarDuplo(bd()->produtos, &chave_produto, localizar_produto);
    if (produto_encontrado==NULL) {
        printf("ERRO AO BUSCAR PRODUTO (id=%d)\n", id_produto);
        return 0;
    }

    // Criar nova entrega — use calloc para zerar a struct
    Entrega *nova = alocar_entrega();
    if (!nova) {
        printf("ERRO AO ALOCAR ENTREGA\n");
        return 0;
    }
    nova->id_produto  = produto_encontrado->id;

    strncpy(nova->destinatario, cliente_encontrado->nome, sizeof(nova->destinatario)-1);
    nova->destinatario[sizeof(nova->destinatario)-1] = '\0';

    // Mostra dados — prints seguros
    printf("                  ID: %03d\n", nova->id);
    printf("        DESTINATARIO: %s\n", cliente_encontrado->nome);
    printf("             PRODUTO: %s\n", produto_encontrado->nome);

    // Validar entrega (se validar_entrega depender de id_cliente/id_produto/strings, tudo ok)
    validar_entrega(nova);

    // Verifica fila válida antes de enfileirar
    Fila *f = bd()->entregas;
    if (!f) {
        // Se a fila não existe, crie/initializa aqui ou falhe explicitamente.
        printf("FILA DE ENTREGAS NAO INICIALIZADA\n");
        // opcional: f = bd()->entregas = criar_fila(); // se tiver função
        return 0;
    }

    enfileirar(f, nova);

    return nova->id;
}

void* buscar_entregas(const int id) {
  Entrega chave_entrega = {0};
  Entrega *entrega_encontrada = NULL;
  Produto chave_produto = {0};
  Produto *produto_encontrado = NULL;

  chave_entrega.id = id;
  entrega_encontrada = pesquisarFila(bd()->entregas, &chave_entrega, localizar_entrega);
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
  return entrega_encontrada;
}

void imprimir_produto_entrega(Produto * p, float valor){
  printf("");
  printf("  │ %03d    %-43s %8.2f │\n", p->id, p->nome, valor);
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
void iprimir_entrega_ag(void *dado, char * destinatario[SIZES]) {
  Entrega * e= dado;
  printf("\n");
  if (strcmp(*destinatario, e->destinatario) != 0) {

    printf("  ┌──────────────────────────────────────────────────────────────┐\n");
    printf("  │                        ENTREGA %-4d                          │\n", e->id);
    printf("  ├──────────────────────────────────────────────────────────────┤\n");
    printf("  │ DESTINATÁRIO: %-40s │\n", e->destinatario);
    printf("  ├──────────────────────────────────────────────────────────────┤\n");
    *destinatario = e->destinatario ;
  }

  Produto chave = {0};
  chave.id = e->id_produto;
  Produto *p = pesquisarDuplo(bd()->produtos, &chave, localizar_produto);
  imprimir_produto_entrega(p, e->valor );

}

void imprimir_rodape_entrega(float quantidade, float soma) {
  printf("├─────────────────────────────────────────────────────────────────┤\n");
  printf("│ TOTAL: %-5d itens                                R$ %10.2f │\n",
         quantidade, soma);
  printf("└─────────────────────────────────────────────────────────────────┘\n");
}

void listar_entregas() {
  imprimir_cabecalho_entrega();
  char * destinatario [SIZES];
  destinatario[0] = "\0";
  imprimirFilaAg(bd()->entregas, iprimir_entrega_ag, destinatario);
  float quantidade = 999;
  float soma = 999.99;
  imprimir_rodape_entrega(quantidade, soma);
  system("pause");
}
//==========================================

int inserir_cargas() {
return 0;
}

void * buscar_cargas(const int id) {

}
void listar_cargas() {

}

int inserir_vendas(const int id) {

  return 0;
}
void * buscar_vendas() {

}
void listar_vendas() {

}

void relatorios(){
}
