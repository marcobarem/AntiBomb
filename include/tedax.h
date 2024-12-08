#ifndef TEDAX_H
#define TEDAX_H
#include "../include/mural.h"

void *tedax_func(void *arg);
void inicializar_tedax(int num_tedax);
void finalizar_tedax();
int enviar_modulo_para_tedax(int tedax_id, int modulo_id, int bancada_id);

#endif
