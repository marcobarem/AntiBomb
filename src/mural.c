#include "../include/mural.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex_mural;
Modulo mural[10];
int mural_count = 0;

void inicializar_mural() {
    pthread_mutex_init(&mutex_mural, NULL);
}

void gerar_modulo() {
    pthread_mutex_lock(&mutex_mural);
    if (mural_count < 10) {
        mural[mural_count].tempo_para_desarmar = rand() % 10 + 1;
        snprintf(mural[mural_count].tipo, 10, "M%d", mural_count + 1);
        mural[mural_count].desarmado = false;
        mural_count++;
    }
    pthread_mutex_unlock(&mutex_mural);
}

Modulo obter_modulo() {
    pthread_mutex_lock(&mutex_mural);
    Modulo modulo = mural[--mural_count];
    pthread_mutex_unlock(&mutex_mural);
    return modulo;
}

bool mural_vazio() {
    pthread_mutex_lock(&mutex_mural);
    bool vazio = (mural_count == 0);
    pthread_mutex_unlock(&mutex_mural);
    return vazio;
}

void finalizar_mural() {
    pthread_mutex_destroy(&mutex_mural);
}
