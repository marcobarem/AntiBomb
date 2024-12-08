#ifndef COORDENADOR_H
#define COORDENADOR_H
#include <stdbool.h>

extern bool jogo_ativo;
void *coordenador_func(void *arg);
void inicializar_coordenador();
void finalizar_coordenador();
int processar_comando(const char *comando);

#endif
