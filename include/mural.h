#ifndef MURAL_H
#define MURAL_H

#include <stdbool.h>
#include <pthread.h>

typedef struct {
    char tipo[10];
    int tempo_para_desarmar;
    bool desarmado;
} Modulo;

void inicializar_mural();
void gerar_modulo();
Modulo obter_modulo();
bool mural_vazio();
void finalizar_mural();

#endif
