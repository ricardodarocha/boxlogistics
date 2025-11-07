#ifndef TFINAL_LOGIN_C_H
#define TFINAL_LOGIN_C_H

int confere(const char *a,const char *b);
int user(char * login);
int admin(char * login);
int verificar_permissoes(char * login);
int efetuar_login(char * login);

extern char _login[INPUTSIZE];

#endif