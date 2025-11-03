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

## 👨‍💻 Criação de novos arquivos

📦 Exemplo: models/produto.c
```C
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
```

🧩 Exemplo: include/produto.h
```
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
```
Para criar um arquivo de cabeçalho no Code Blocks clique no menu File-new-file e na janela que aparecer escolha a opção header (cabeçalho).

Como um arquivo de cabeçalho pode ser incluído em diversos arquivos diferentes, precisamos ter o cuidado de não carregá-lo mais de uma vez, isso irá duplicar nossas estruturas, funções e procedimentos podendo ocasionar em erros durante a execução do programa. Para evitar isso, podemos verificar se o arquivo já foi carregado por meio de uma estrutura if.

O `ifndef significa if not defined`, ou seja, se não existir uma definição chamada `NOME_MODULO`, então essa definição será criada (na linha seguinte), assim como as estruturas serão criadas e as assinaturas das nossas funções e procedimentos.

Caso a definição NOME_MODULO já exista, o fluxo de execução irá para endif e nada será feito.

O nome NOME_MODULO não precisa ser exatamente assim. O importante é que seja exatamente o mesmo nome na primeira e segunda linhas do arquivo.h, deve ser um nome diferente pra cada arquivo.

// arquivo pilha.h
```
#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
typedef struct no{
    int valor;
    struct no *proximo;
}No;
No* empilhar(No *pilha, int num);
No* desempilhar(No **pilha);
void imprimir(No *pilha);
#endif 
```

Agora que já temos nosso arquivo de cabeçalhos, perceba que ele possui apenas as estruturas que iremos utilizar e as assinaturas das funções e procedimentos, das operações da nossa TAD. Precisamos criar propriamente estas funções e procedimentos. Para isso vamos criar um novo arquivo chamado pilha.c.

É dentro deste arquivo pilha.c que teremos nossas funções e procedimentos para operar sobre nosso conjunto de dados, a pilha. Este arquivo precisa de dois includes, o arquivo de cabeçalho stdio.h, onde está definido a constante NULL e o arquivo de cabeçalho pilha.h que acabamos de criar.

Observe que a inclusão do nosso arquivo fica entre um par de aspas duplas. Isso diz para o computador procurar este arquivo dentro do diretório do nosso projeto. Ao utilizar os sinais de maior e menor o compilador irá procurar este arquivo diretamente na pasta padrão do compilador, como stdio.h. Como o arquivo pilha.h está na pasta do projeto e não na pasta padrão do compilador, teremos um erro se tentarmos usar os sinais de maior menor no lugar das aspas duplas.

// arquivo pilha.c
```C
#include <stdio.h>
#include "pilha.h"
No* empilhar(No *pilha, int num){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->proximo = pilha;
        return novo;
    }
    else
        printf("Erro ao alocar memoria!\n");
    return NULL;
}
No* desempilhar(No **pilha){
    No *remover = NULL;
    if(*pilha){
        remover = *pilha;
        *pilha = remover->proximo;
    }
    else
        printf("Pilha vazia!\n");
    return remover;
}
void imprimir(No *pilha){
    printf("\n\tPILHA\n");
    while(pilha){
        printf("\t%d\n", pilha->valor);
        pilha = pilha->proximo;
    }
    printf("\n");
}
```

Agora vamos criar nosso arquivo main.c. Neste arquivo, além dos includes que já estamos acostumados, também precisamos incluir nosso arquivo de cabeçalho pilha.h.

Perceba que a função fatorial não está definida no arquivo pilha.h nem no arquivo pilha.c, isso porque esta função não é uma operação que age sobre nosso conjunto de dados, como empilhar, desempilhar ou imprimir. Isso faz parte da organização do código. Imagine que além da estrutura pilha, também tivéssemos uma fila e uma lista encadeada (estruturas que veremos aqui no curso), poderíamos ter mais quatro arquivos:
– fila.h
– fila.c
– lista.h
– lista.c

Assim, cada arquivo contém o código de um TAD, deixando o código mais organizado e tornando a manutenção mais rápida e precisa.
```C
/*
                 arquivo main.c
                 Código escrito por Wagner Gaspar
                 Julho de 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
int fatorial(int num){
    No *remover, *pilha = NULL;
    while(num > 1){
        pilha = empilhar(pilha, num);
        num--;
    }
    imprimir(pilha); // 2 3
    while(pilha){
        remover = desempilhar(&pilha);
        num = num * remover->valor;
        free(remover);
    }
    return num;
}
int main(){
    int valor;
    printf("Digite um valor maior que zero para o fatorial: ");
    scanf("%d", &valor);
    printf("\tFatorial de %d: %d\n", valor, fatorial(valor));
}
```

🚀 Exemplo: src/main.c
```C
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
```

## 🧰 Makefile simples

```C
CC = gcc
CFLAGS = -Iinclude -Wall
OBJ = lib/listagenerica.o models/produto.o src/main.o

meu_programa: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) meu_programa
```

## 💡 Benefícios dessa organização

✅ Cada área tem autonomia sem interferir nas outras.
✅ Facilita testes isolados (por ex. make test-lib para testar lib/).
✅ Padroniza inclusão de headers (#include "../include/...").
✅ Evita dependências circulares.
✅ Fácil expansão — basta adicionar novas structs em models/.

## Configuração do terminal

o terminal fica com caracteres estranhos como habilitar caracteres especiais no codigo para imprimri direto no terminal

esse problema é muito comum em programas C que imprimem arte ASCII ou box drawings (como ╔═╗, ║ ║, ╚═╝).
Quando o terminal mostra caracteres estranhos (�, ç, etc.), normalmente é por causa de incompatibilidade de codificação.
Aqui vai um guia completo pra resolver em Windows, no seu código em C, no terminal e no VSCode/Dev-C++ 👇

🧩 1️⃣ Entendendo o problema

Esses caracteres (╔, ║, ╚, ─, etc.) fazem parte da tabela de caracteres estendida (OEM 437 ou 850).
Mas o Windows Terminal, CMD ou VSCode geralmente usa UTF-8 (codepage 65001).

Você precisa configurar o terminal e o código fonte para a mesma codificação.

🧩 2️⃣ Soluções práticas
✅ Opção 1 – Usar UTF-8 (recomendada)

No início do seu main(), adicione:

```C
#include <windows.h>
#include <stdio.h>

int main(void) {
    // Define UTF-8 no terminal
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("╔══════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA BOX LOGISTICS     ║\n");
    printf("║              Versão 0.1 (2025)           ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    return 0;
}
```


💡 Certifique-se de que o arquivo .c está salvo em UTF-8 sem BOM (no VSCode: “Salvar com codificação → UTF-8”).
💡 No terminal, digite antes de rodar:
chcp 65001

✅ Opção 2 – Usar o conjunto `OEM 437` (modo clássico do DOS)

Se quiser rodar igual aos antigos sistemas DOS:

```C
#include <windows.h>
#include <stdio.h>

int main(void) {
    SetConsoleOutputCP(437); // Código OEM dos box-drawings antigos

    printf("╔══════════════════════════════════════════╗\n");
    printf("║   BEM-VINDO AO SISTEMA BOX LOGISTICS     ║\n");
    printf("║              Versão 0.1 (2025)           ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    return 0;
}
```

Digite no terminal: `chcp 437 `

🎨 Isso garante compatibilidade com os caracteres da tabela ASCII estendida original (usada em Turbo C e DOS).

🧩 3️⃣ Dica bônus — Teste automático de charset

Você pode detectar se o terminal suporta UTF-8 e ajustar:

UINT codepage = GetConsoleOutputCP();
if (codepage != CP_UTF8) SetConsoleOutputCP(CP_UTF8);

🧩 4️⃣ Verificação no VSCode

Vá em Arquivo → Salvar com codificação → UTF-8 sem BOM

Vá em Configurações → Terminal → Integrated: Set locale to UTF-8


## Referencias bibliograficas

1. https://wagnergaspar.com/como-criar-arquivos-de-cabecalho-h-na-linguagem-c/
2. https://medium.com/@fabiano.salles/generic-linked-list-in-c-157dc49767bc
