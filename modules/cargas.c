#include <stdlib.h>
#include <stdio.h>
#include "../app/config.h"
#include "../include/fila.h"
#include "../include/calendario.h"

// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>

// #include "../app/config.h"
#include "../include/carga.h"


static int proxima_carga = 0;

int cursor_proxima_carga(void) {
    return proxima_carga;
}

void imprimir_cabecalha_carga() {

}

void imprimir_carga(void *dado, void (*imprimir_entrega)(void *)) {
    Carga *c = dado;
    printf("  ╠──────────────────────────────────────────────────────────────╣\n");
    printf("  │ CARGA %03d   %-40s            │\n", c->id, c->nome);
    printf("  ├──────────────────────────────────────────────────────────────┤\n");
    printf("  │ Data................: %-38s │\n", formatar_data(c->data));
    printf("  │ Valor total.........: %10.2f                             │\n", c->valor);
    // printf("│ Motorista...........: %-54s │\n", c->motorista_nome);
    // printf("│ CNH.................: %-54s │\n", c->motorista_cnh);
    // printf("│ Placa do Caminhão...: %-54s │\n", c->placa_caminhao);
    printf("  ├──────────────────────────────────────────────────────────────┤\n");
    printf("  │ ENTREGAS                                                     │\n");
    printf("  ├────┬─────────────────────────────────────────┬───────────────┤\n");
    printf("  │ ID │ Nome                                    │ Quantidade    │\n");
    printf("  ├────┼─────────────────────────────────────────┼───────────────┤\n");

    if (!c->entregas) {
        printf("  │ -- Nenhuma entrega cadastrada --                             │\n");
        printf("  └──────────────────────────────────────────────────────────────┘\n");
        return;
    }

    Fila *fila = c->entregas;

    if (!fila->inicio) {
        printf("│ -- Nenhuma entrega cadastrada --                             │\n");
        printf("└──────────────────────────────────────────────────────────────┘\n");
        return;
    }

    for (FilaX *cur = fila->inicio; cur; cur = cur->proximo) {
        imprimir_entrega(cur->dado);
    }

    printf("  ├────┘─────────────────────────────────────────┘───────────────┤\n");
}

int localizar_carga(void *a, void *b) {
    if (!a || !b) return NOTFOUND;

    Carga *pa = a;
    Carga *pb = b;
    if (pa->id == pb->id)
        return FOUND;
    return (pa->id > pb->id ? DIREITA : ESQUERDA);
}

int validar_carga(void *dado) {
    if (!dado) return INVALID;

    Carga *p = dado;

    if (p->nome[0] == '\0') return INVALID;
    if (p->valor < 0) return INVALID;

    return VALID;
}

Carga *alocar_carga(void) {
    Carga *carga = malloc(sizeof(Carga));
    if (!carga) {
        perror("malloc");
        return NULL;
    }
    memset(carga, 0, sizeof(Carga));
    carga->id = ++proxima_carga;
    carga->data = 0;

    memset(carga->nome, 0, sizeof(carga->nome));
    carga->valor = 0.0f;

    return carga;
}

void * inserir_nova_carga(void *entrega, int *id_carga, float valor_entrega) {
    Carga * carga = alocar_carga();
    * id_carga = carga->id;
    carga->entregas = entrega;
    carga->valor = valor_entrega;
    return carga;
}

Carga *nova_carga(const char *nome, const float valor) {
    Carga *result = alocar_carga();
    strcpy(result->nome, nome);
    result->valor = valor;
    return result;
}