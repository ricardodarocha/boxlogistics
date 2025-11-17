typedef struct Carga {
    int idCarga;
    char diaSaida[11];
    No_Caminhao* caminhao_associado;
    FilaW entregas_da_carga; // FilaW interna
    float peso_atual_kg;
    float volume_atual_m3;
} Carga;


typedef struct No_Arvore_Carga {
    Carga dados_carga;
    struct No_Arvore_Carga* esquerda;
    struct No_Arvore_Carga* direita;
} No_Arvore_Carga;



No_Arvore_Carga* criarNoArvore(Carga novaCarga) {
    No_Arvore_Carga* novo = (No_Arvore_Carga*)malloc(sizeof(No_Arvore_Carga));
    novo->dados_carga = novaCarga;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No_Arvore_Carga* inserirCargaNaArvore(No_Arvore_Carga* raiz, Carga novaCarga) {
    if (raiz == NULL) {
        return criarNoArvore(novaCarga);
    }
    if (novaCarga.idCarga < raiz->dados_carga.idCarga) {
        raiz->esquerda = inserirCargaNaArvore(raiz->esquerda, novaCarga);
    } else {
        raiz->direita = inserirCargaNaArvore(raiz->direita, novaCarga);
    }
    return raiz;
}

void imprimirCargasEmOrdem(No_Arvore_Carga* raiz) {
    if (raiz != NULL) {
        imprimirCargasEmOrdem(raiz->esquerda);

        Carga* dadosCarga = &raiz->dados_carga;
        No_Caminhao* cam = dadosCarga->caminhao_associado;

        printf("\n    --- CARGA ID: %d (Placa: %s) ---\n", dadosCarga->idCarga, cam->vPlaca_Caminhao);
        printf("    Data Saída: %s\n", dadosCarga->diaSaida);

        printf("    Peso: %.2f Kg / %.2f Kg (%.1f%%)\n",
               dadosCarga->peso_atual_kg, cam->vCapacidade_Peso_Max,
               (dadosCarga->peso_atual_kg / cam->vCapacidade_Peso_Max) * 100.0);

        float vol_max = calcularVolumeCaminhao(cam);

        printf("    Volume: %.2f m³ / %.2f m³ (%.1f%%)\n",
               dadosCarga->volume_atual_m3, vol_max,
               (dadosCarga->volume_atual_m3 / vol_max) * 100.0);

        printf("    Entregas nesta Carga (%d):\n", dadosCarga->entregas_da_carga.tamanho);


        if (dadosCarga->entregas_da_carga.tamanho > 0) {
            imprimirFilaWEntregas(&dadosCarga->entregas_da_carga);
        } else {
            printf("    (Nenhuma entrega alocada)\n");
        }

        imprimirCargasEmOrdem(raiz->direita);
    }
}

No_Arvore_Carga* buscarCargaPorId_Recursivo(No_Arvore_Carga* raiz, int id) {
    if (raiz == NULL || raiz->dados_carga.idCarga == id) {
        return raiz;
    }
    if (id < raiz->dados_carga.idCarga) {
        return buscarCargaPorId_Recursivo(raiz->esquerda, id);
    } else {
        return buscarCargaPorId_Recursivo(raiz->direita, id);
    }
}

Carga* buscarCargaPorId(int id) {
    No_Arvore_Carga* no = buscarCargaPorId_Recursivo(G_Raiz_Cargas, id);
    if (no != NULL) {
        return &no->dados_carga;
    }
    return NULL;
}

int tentarAlocarEntrega(Carga* carga, No_Entregas* entrega) {
    if (carga == NULL || entrega == NULL || entrega->vProduto_da_Entrega == NULL || carga->caminhao_associado == NULL) {
        printf("    [FALHA] Erro interno de ponteiro nulo ao alocar.\n");
        return 0;
    }

    No_Produto* produto = entrega->vProduto_da_Entrega;
    No_Caminhao* caminhao = carga->caminhao_associado;

    float volume_produto_m3 = calcularVolumeProduto(produto);
    float volume_max_caminhao_m3 = calcularVolumeCaminhao(caminhao);

    float peso_novo_total = carga->peso_atual_kg + produto->vPeso;
    if (peso_novo_total > caminhao->vCapacidade_Peso_Max) {
        printf("    [FALHA] Entrega %d (Prod: %s) não coube.\nMOTIVO: Excesso de PESO.\n", entrega->vId_Entrega, produto->vNomeProd);
        return 0;
    }
    float volume_novo_total = carga->volume_atual_m3 + volume_produto_m3;
    if (volume_novo_total > volume_max_caminhao_m3) {
        printf("    [FALHA] Entrega %d (Prod: %s) não coube.\nMOTIVO: Excesso de VOLUME.\n", entrega->vId_Entrega, produto->vNomeProd);
        return 0;
    }

    carga->peso_atual_kg = peso_novo_total;
    carga->volume_atual_m3 = volume_novo_total;

    enfileirarNoMovido(&carga->entregas_da_carga, entrega);
    return 1;
}