#include "../include/mural.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

Modulo mural[10];
int mural_count = 0;

void inicializar_mural() {
    pthread_mutex_init(&mutex_mural, NULL);
}

void gerar_modulo() {
    pthread_mutex_lock(&mutex_mural);
    if (mural_count < 10) {
        mural[mural_count].tempo_para_desarmar = rand() % 10 + 1;
        snprintf(mural[mural_count].tipo, sizeof(mural[mural_count].tipo), "M%d", mural_count + 1);
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

Modulo obter_modulo_por_id(const char *id) {
    pthread_mutex_lock(&mutex_mural);
    for (int i = 0; i < mural_count; i++) {
        if (strcmp(mural[i].tipo, id) == 0) {
            pthread_mutex_unlock(&mutex_mural);
            return mural[i];
        }
    }
    pthread_mutex_unlock(&mutex_mural);

    // Retorna um módulo vazio se não encontrado
    Modulo vazio = {"", 0, false};
    return vazio;
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
