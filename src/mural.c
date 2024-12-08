#include "../include/mural.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_MODULOS 10

Modulo mural[MAX_MODULOS];
int mural_count = 0;

// Inicializa o mural e o mutex associado
void inicializar_mural() {
    pthread_mutex_init(&mutex_mural, NULL);
}

// Gera um novo módulo e o adiciona ao mural
void gerar_modulo() {
    pthread_mutex_lock(&mutex_mural);
    if (mural_count < MAX_MODULOS) {
        mural[mural_count].tempo_para_desarmar = rand() % 10 + 1;
        snprintf(mural[mural_count].tipo, sizeof(mural[mural_count].tipo), "M%d", mural_count + 1);
        mural[mural_count].desarmado = false;
        mural_count++;
    } else {
        printf("Mural cheio! Não é possível gerar mais módulos.\n");
    }
    pthread_mutex_unlock(&mutex_mural);
}

// Retorna e remove o módulo mais recente do mural
Modulo obter_modulo() {
    pthread_mutex_lock(&mutex_mural);
    if (mural_count > 0) {
        Modulo modulo = mural[--mural_count];
        pthread_mutex_unlock(&mutex_mural);
        return modulo;
    }
    pthread_mutex_unlock(&mutex_mural);
    Modulo vazio = {"", 0, false};
    return vazio;
}

// Retorna e remove o módulo especificado pelo ID
Modulo obter_modulo_por_id(const char *id) {
    pthread_mutex_lock(&mutex_mural);
    for (int i = 0; i < mural_count; i++) {
        if (strcmp(mural[i].tipo, id) == 0) {
            Modulo modulo = mural[i];

            // Remove o módulo do mural
            for (int j = i; j < mural_count - 1; j++) {
                mural[j] = mural[j + 1];
            }
            mural_count--;

            pthread_mutex_unlock(&mutex_mural);
            return modulo;
        }
    }
    pthread_mutex_unlock(&mutex_mural);

    // Retorna um módulo vazio se não encontrado
    Modulo vazio = {"", 0, false};
    return vazio;
}

// Verifica se o mural está vazio
bool mural_vazio() {
    pthread_mutex_lock(&mutex_mural);
    bool vazio = (mural_count == 0);
    pthread_mutex_unlock(&mutex_mural);
    return vazio;
}

// Finaliza o mural, destruindo o mutex
void finalizar_mural() {
    pthread_mutex_destroy(&mutex_mural);
}
