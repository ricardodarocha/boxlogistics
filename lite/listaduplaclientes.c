#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


typedef struct No_Cliente {
    int vId_Cliente;
    char vNome_Cliente[25];
    char vCPF_Cliente[15];
    struct No_Cliente* proximo;
    struct No_Cliente* anterior;
} No_Cliente;

No_Cliente* CriarNoCliente(int vId_Cliente, const char *vNome_Cliente, const char *vCPF_Cliente) {
    No_Cliente* novoNo = (No_Cliente*)malloc(sizeof(No_Cliente));
    if (novoNo == NULL) {
        printf("    Erro na alocação de memória!\n");
        return NULL;
    }

    novoNo->vId_Cliente = vId_Cliente;
    strcpy(novoNo->vNome_Cliente, vNome_Cliente);
    strcpy(novoNo->vCPF_Cliente, vCPF_Cliente);
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    return novoNo;
}

void inserirClienteNoFimLista(No_Cliente** cabeca_ref) {
    static int vId_Cliente = 1;
    char vNome_Cliente[25];
    char vCPF_Cliente[15];

    printf("        Código: %d\n", vId_Cliente);
    printf("        Digite o nome do cliente: ");
    scanf(" %24[^\n]s", vNome_Cliente);
    printf("        Digite o CPF do cliente: ");
    scanf(" %14[^\n]s", vCPF_Cliente);
    No_Cliente* novoNo = CriarNoCliente(vId_Cliente, vNome_Cliente, vCPF_Cliente);
    vId_Cliente ++;
    if (novoNo == NULL) return;

    if (*cabeca_ref == NULL) {
        *cabeca_ref = novoNo;
        return;
    }

    No_Cliente* temp = *cabeca_ref;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNo;
    novoNo->anterior = temp;
}

No_Cliente* buscarClientePorId(No_Cliente* cabeca_ref, int id) {
    No_Cliente* temp = cabeca_ref;
    while (temp != NULL) {
        if (temp->vId_Cliente == id) {
            return temp;
        }
        temp = temp->proximo;
    }
}

void imprimirClientes(No_Cliente* cabeca_ref) {
    while (cabeca_ref != NULL) {
        printf("        Id.: %-3d    Cliente: %-23s   CPF: %-14s\n", cabeca_ref->vId_Cliente, cabeca_ref->vNome_Cliente, cabeca_ref->vCPF_Cliente);
        cabeca_ref = cabeca_ref->proximo;
    }
}
