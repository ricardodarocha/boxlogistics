#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct No_Caminhao {
    int vId_Caminhao;
    char vPlaca_Caminhao[10];
    float vCapacidade_Peso_Max;
    float vAltura_Bau;
    float vLargura_Bau;
    float vComprimento_Bau;
    struct No_Caminhao* proximo;
    struct No_Caminhao* anterior;
} No_Caminhao;

No_Caminhao* CriarNoCaminhao(int vId_Caminhao, const char *vPlaca_Caminhao, float vCapacidade_Peso_Max, float vAltura_Bau, float vLargura_Bau, float vComprimento_Bau) {
    No_Caminhao* novoNo = (No_Caminhao*)malloc(sizeof(No_Caminhao));
    if (novoNo == NULL) {
        printf("Erro na alocação de memória!\n");
        return NULL;
    }

    novoNo->vId_Caminhao = vId_Caminhao;
    strcpy(novoNo->vPlaca_Caminhao, vPlaca_Caminhao);
    novoNo->vCapacidade_Peso_Max = vCapacidade_Peso_Max;
    novoNo->vAltura_Bau = vAltura_Bau;
    novoNo->vLargura_Bau = vLargura_Bau;
    novoNo->vComprimento_Bau = vComprimento_Bau;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    return novoNo;
}

void inserirCaminhoesNoFimLista(No_Caminhao** cabeca_ref) {
    static int vId_Caminhao = 1;
    char vPlaca_Caminhao[10];
    float vCapacidade_Peso_Max;
    float vAltura_Bau;
    float vLargura_Bau;
    float vComprimento_Bau;

    printf("Código: %d\n", vId_Caminhao);
    printf("Placa: ");
    scanf(" %9[^\n]s", vPlaca_Caminhao);
    printf("Capacidade Peso(KG): ");
    scanf("%f", &vCapacidade_Peso_Max);
    printf("Altura Baú (cm): ");
    scanf("%f", &vAltura_Bau);
    printf("largura Baú (cm): ");
    scanf("%f", &vLargura_Bau);
    printf("Comprimento Baú (cm): ");
    scanf("%f", &vComprimento_Bau);


    No_Caminhao* novoNo = CriarNoCaminhao(vId_Caminhao, vPlaca_Caminhao, vCapacidade_Peso_Max, vAltura_Bau, vLargura_Bau, vComprimento_Bau);
    vId_Caminhao ++;


    if (novoNo == NULL) {
        return;
    }

    if (*cabeca_ref == NULL) {
        *cabeca_ref = novoNo;
        return;
    }

    No_Caminhao* temp = *cabeca_ref;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNo;
    novoNo->anterior = temp;
}

float calcularVolumeCaminhao(No_Caminhao* caminhao) {
    if (caminhao == NULL) {
        return 0.0;
    }
    float caminhaVol = caminhao->vAltura_Bau * caminhao->vLargura_Bau * caminhao->vComprimento_Bau;
    return caminhaVol / 1000000.0;
}

void imprimirCaminhoes(No_Caminhao* cabeca_ref) {

    printf("%-5s %-10s %-15s %-15s\n", "ID", "Placa", "Peso Max (Kg)", "Volume Max (m³)");

    while (cabeca_ref != NULL) {
        printf("%-5d %-10s %-15.2f %-15.2f\n", cabeca_ref->vId_Caminhao, cabeca_ref->vPlaca_Caminhao, cabeca_ref->vCapacidade_Peso_Max, calcularVolumeCaminhao(cabeca_ref));
        cabeca_ref = cabeca_ref->proximo;
    }
}
