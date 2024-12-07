#include "../include/tedax.h"
#include "../include/mural.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t *tedax_threads;

void *tedax_func(void *arg) {
    int id = *(int *)arg;
    while (1) {
        Modulo modulo = obter_modulo();
        sleep(modulo.tempo_para_desarmar);
        printf("Tedax %d desarmou o módulo %s\n", id, modulo.tipo);
    }
}

void inicializar_tedax(int num_tedax) {
    tedax_threads = malloc(num_tedax * sizeof(pthread_t));
    for (int i = 0; i < num_tedax; i++) {
        pthread_create(&tedax_threads[i], NULL, tedax_func, &i);
    }
}

int enviar_modulo_para_tedax(int tedax_id, int modulo_id, int bancada_id) {
    // Simula o envio de um módulo para o Tedax
    printf("Tedax %d desarmando Módulo %d na Bancada %d\n", tedax_id, modulo_id, bancada_id);
    return 1; // Sucesso
}

void finalizar_tedax() {
    free(tedax_threads);
}
