#ifndef VISUAL_SIMPLIFICADO2H
#define VISUAL_SIMPLIFICADO2H

void enable_ansi(void);

int exibir_menu(const char *operacoes);

void input_string(const char *prompt, char *out, size_t size);

void input_string_required(const char *title, char *out, size_t size);

void input_moeda(char *title, float *out);

void input_inteiro(char *title, int *out);

void input_float(char *title, float *out);

int input_logico(char *title);

void input_senha(const char *title, char *out, size_t max_len);

#endif