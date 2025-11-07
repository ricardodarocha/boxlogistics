
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "../include/login.h"
#include "../include/visual.h"
#define ACESSO_NEGADO 0
#define ACESSO_CONCEDIDO 1

char _login[INPUTSIZE];

void boas_vindas_ao_sistema(const char *login) {
    printf("\nBem vindo ao sistema %s\n", login);
}

int confere(const char *a,const char *b) {
    return _stricmp(a, b) == 0;
}

int user(char * login) {
    char senha[INPUTSIZE];

    input_senha("senha", senha, 64);

    if (confere(login, "jacimar") && confere(senha, "jacimar")) return ACESSO_CONCEDIDO;
    if (confere(login, "wemerson") && confere(senha, "wemerson")) return ACESSO_CONCEDIDO;
    if (confere(login, "teste") && confere(senha, "123")) return ACESSO_CONCEDIDO;
    if (confere(login, "sistema") && confere(senha, "123")) return ACESSO_CONCEDIDO;

    return ACESSO_NEGADO;
}

int admin(char * login) {
    char email[INPUTSIZE];
    char senha[INPUTSIZE];
    char repete_senha[INPUTSIZE];

    input_string_required("    novo login", login, sizeof(login));
    input_string_required("         email", email, sizeof(email));

    do {
        input_senha(      "         senha", senha, 64);
        input_senha(      "repita a senha", repete_senha, 64);

        if (!confere(senha, repete_senha)) {
            printf(" senha invalida\n");
        }
    } while (!confere(senha, repete_senha));

    boas_vindas_ao_sistema(login);
    return ACESSO_CONCEDIDO;
}

int verificar_permissoes(char * login) {
    //aqui verificamos permissoes do usuario
    //por exemplo se o modulo balanca esta habilitado para um usuario
    return ACESSO_CONCEDIDO;
}

int efetuar_login(char * login) {
    char senha[INPUTSIZE];
    int tentativas = 3;
    input_string_required("login", login, sizeof(login));
    if (confere(login, "admin")) {
        do {
            input_senha("senha", senha, sizeof(senha));
            if (!confere(senha, "admin")) {
                printf("\nSenha invalida (%d)\n", tentativas);
                tentativas --;
            } else {
                return admin(login);
            }
            if (tentativas==0) {
                return ACESSO_NEGADO;
            }
        } while (!confere(senha, "admin"));

    } else {

        do {
            if (user(login)){
                boas_vindas_ao_sistema(login);
                return ACESSO_CONCEDIDO;
            } else {
                tentativas --;
                if (tentativas==0) return ACESSO_NEGADO;
                printf(" verifique usuario e senha\n");
                input_string_required("login", login, sizeof(login));
            }

        } while (!confere(senha, "admin"));

    }
}