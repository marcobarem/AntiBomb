#include "../include/utils.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

// Mutexes globais
pthread_mutex_t mutex_bancadas;
pthread_mutex_t mutex_mural;

// Semáforos globais
sem_t sem_bancadas;
sem_t sem_modulos;

// Variável global para configuração
Config config;

void inicializar_sincronizacao() {
    // Inicializa mutexes
    if (pthread_mutex_init(&mutex_bancadas, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex para bancadas\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_init(&mutex_mural, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex para mural de módulos\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa semáforos
    if (sem_init(&sem_bancadas, 0, config.num_bancadas) != 0) {
        fprintf(stderr, "Erro ao inicializar semáforo para bancadas\n");
        exit(EXIT_FAILURE);
    }
    if (sem_init(&sem_modulos, 0, 0) != 0) {
        fprintf(stderr, "Erro ao inicializar semáforo para módulos\n");
        exit(EXIT_FAILURE);
    }
}

void finalizar_sincronizacao() {
    pthread_mutex_destroy(&mutex_bancadas);
    pthread_mutex_destroy(&mutex_mural);
    sem_destroy(&sem_bancadas);
    sem_destroy(&sem_modulos);
}

void definir_configuracao(int num_tedax, int num_bancadas, int tempo_jogo) {
    config.num_tedax = num_tedax;
    config.num_bancadas = num_bancadas;
    config.tempo_jogo = tempo_jogo;

    printf("Configuração inicial definida:\n");
    printf("  Número de Tedax: %d\n", config.num_tedax);
    printf("  Número de Bancadas: %d\n", config.num_bancadas);
    printf("  Tempo de Jogo: %d segundos\n", config.tempo_jogo);
}
