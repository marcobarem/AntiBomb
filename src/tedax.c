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

void finalizar_tedax() {
    free(tedax_threads);
}
