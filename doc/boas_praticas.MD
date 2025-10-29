# Boas práticas

Este documento orienta os programadores do time a aderir ao guia de boas práticas, baseado nos conceitos mais modernos de boas práticas de desenvolvimento da comunidade de software.
 - Ergonomia: São as decisões de fluxo de trabalho, equipamentos, ambiente e ferramentas do dia a dia que propiciem boa qualidade de vida, clareza, acessibilidade e bem estar dos programadores e testadores.
 - Clean Code: Código Limpo é uma premissa de organização de código, escrita de código claro, de fácil leitura, fácil de dar manutenção e com baixa carga cognitiva (baixo tempo de aprendizado).
 - SOLID: SOLID são princípios de Programação Orientada a Objetos POO mas que são aplicáveis em certa medida em todos os tipos de sistema, consitem em criar código preciso, unitário, coezo e com níveis certos de abstração.
 - KISS: Sigla para Keep It Stupdly Simple, uma premissa que norteia a criação de código simples, que exija o menor esforço possível para a solução do problema do domínio específico
 - DRY: Sigla para _Dont Repeat Yourself_ um lema do reaproveitamento de código e organização de modo a compartilhar código entre diferentes projetos ou de projetar fluxos de trabalho que minimizem a ação de copiar e colar.

## Regras gerais

Para ajudar na compreensão e facilitar a comunicação do time, devem-se adotar alguns padrões

Nomes de variável em português, sempre que possível, exceto convenções (*main, peek, push, tail etc*)
Componentes simples, pequenos, fáceis de entender
Não usar funções complicadas
Não usar lógica complicada
Não usar código duplicado
Evitar Referência Circular

Nomenclatura de variáveis
```C
nomeVariavel  //pascalCase
NomeStruct    //CamelCase
nome_funcao() //snake_case()
```

## Organização das pastas

Adotamos uma estrutura modular e escalável, ideal para um time de 3 pessoas com papéis claros (Tecnologia, Domínio e Aplicação).

🎯 Objetivo

Organizar o projeto em camadas:

```C
lib/ → infraestrutura genérica (listas, árvores, utilitários)

models/ → definições de structs de domínio (Produto, Cliente, etc.)

src/ → aplicação principal (lógica de negócio, main)

include/ → headers (.h) de toda a aplicação, para controle claro de dependências

📁 Estrutura de pastas
meu_programa/
│
├── include/                    # Cabeçalhos públicos
│   ├── listagenerica.h
│   ├── arvore.h
│   ├── produto.h
│   ├── cliente.h
│   └── app.h
│
├── lib/                        # Implementações genéricas e reutilizáveis
│   ├── listagenerica.c
│   └── arvore.c
│
├── models/                     # Modelos de domínio
│   ├── produto.c
│   └── cliente.c
│
├── src/                        # Código da aplicação
│   ├── main.c
│   ├── cadastro.c
│   ├── login.c
│   └── entrega.c
│
├── Makefile                    # Automação de build
└── README.md
```

## 👨‍💻 Divisão de responsabilidades (para o time)

Papel	Diretório principal	Responsabilidade
Gerente Técnico	lib/, include/	Mantém as tecnologias genéricas (lista, árvore, hash, etc.)
Desenvolvedor de Domínio	models/	Define e mantém as structs e suas funções específicas (Produto, Cliente, etc.)
Equipe de Customer Success / Aplicação	src/	Usa as libs e modelos para criar as regras do negócio e interface do programa
🧱 Exemplo: include/listagenerica.h
#ifndef LISTAGENERICA_H
#define LISTAGENERICA_H

typedef struct Nodo {
    void *dados;
    struct Nodo *prox;
    struct Nodo *ant;
} Nodo;

typedef struct {
    Nodo *inicio;
    Nodo *fim;
    int tamanho;
} ListaGenerica;

ListaGenerica *criar_lista();
void inserir(ListaGenerica *lista, void *dados);
void *buscar(ListaGenerica *lista, int (*comparar)(void*, void*), void *chave);
void liberar_lista(ListaGenerica *lista, void (*destruir)(void*));

#endif

⚙️ Exemplo: lib/listagenerica.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/listagenerica.h"

ListaGenerica *criar_lista() {
    ListaGenerica *lista = malloc(sizeof(ListaGenerica));
    lista->inicio = lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

void inserir(ListaGenerica *lista, void *dados) {
    Nodo *n = malloc(sizeof(Nodo));
    n->dados = dados;
    n->prox = NULL;
    n->ant = lista->fim;
    if (lista->fim)
        lista->fim->prox = n;
    else
        lista->inicio = n;
    lista->fim = n;
    lista->tamanho++;
}

📦 Exemplo: models/produto.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/produto.h"

Produto *criar_produto(int id, const char *nome, float valor) {
    Produto *p = malloc(sizeof(Produto));
    p->id = id;
    snprintf(p->nome, sizeof(p->nome), "%s", nome);
    p->valor = valor;
    return p;
}

void exibir_produto(Produto *p) {
    printf("ID: %d | Nome: %s | Valor: %.2f\n", p->id, p->nome, p->valor);
}

🧩 Exemplo: include/produto.h
#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct {
    int id;
    char nome[100];
    float valor;
} Produto;

Produto *criar_produto(int id, const char *nome, float valor);
void exibir_produto(Produto *p);

#endif

🚀 Exemplo: src/main.c
#include <stdio.h>
#include "../include/listagenerica.h"
#include "../include/produto.h"

int main() {
    printf("=== Sistema de Cadastro ===\n");

    ListaGenerica *listaProdutos = criar_lista();

    Produto *p1 = criar_produto(1, "Arroz", 10.50);
    Produto *p2 = criar_produto(2, "Feijão", 8.90);

    inserir(listaProdutos, p1);
    inserir(listaProdutos, p2);

    exibir_produto(p1);
    exibir_produto(p2);

    return 0;
}

🧰 Makefile simples
CC = gcc
CFLAGS = -Iinclude -Wall
OBJ = lib/listagenerica.o models/produto.o src/main.o

meu_programa: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) meu_programa

💡 Benefícios dessa organização

✅ Cada área tem autonomia sem interferir nas outras.
✅ Facilita testes isolados (por ex. make test-lib para testar lib/).
✅ Padroniza inclusão de headers (#include "../include/...").
✅ Evita dependências circulares.
✅ Fácil expansão — basta adicionar novas structs em models/.
