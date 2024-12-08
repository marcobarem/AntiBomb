#include "../include/utils.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Mutexes globais
pthread_mutex_t mutex_bancadas;
pthread_mutex_t mutex_mural;

// Semáforos globais
sem_t sem_bancadas;
sem_t sem_modulos;
sem_t sem_comando;
Bancada *bancadas;
// Variável global para configuração
Config config;

// Inicializa mutexes e semáforos para sincronização
void inicializar_sincronizacao() {
    // Inicializa o mutex para proteger as bancadas
    if (pthread_mutex_init(&mutex_bancadas, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex para bancadas\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa o semáforo para controlar a disponibilidade das bancadas
    if (sem_init(&sem_bancadas, 0, config.num_bancadas) != 0) {
        fprintf(stderr, "Erro ao inicializar semáforo para bancadas\n");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para as bancadas e inicializa o estado de cada uma
    bancadas = malloc(config.num_bancadas * sizeof(Bancada));
    if (!bancadas) {
        fprintf(stderr, "Erro ao alocar memória para bancadas\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < config.num_bancadas; i++) {
        bancadas[i].tedax_id = -1;  // Nenhum Tedax está usando a bancada
        bancadas[i].ocupada = false; // Bancada está inicialmente livre
    }

    printf("Sincronização inicializada: %d bancadas disponíveis.\n", config.num_bancadas);
}


// Define a configuração inicial do jogo, com validação
void definir_configuracao(int num_tedax, int num_bancadas, int tempo_jogo) {
    if (num_tedax <= 0 || num_bancadas <= 0 || tempo_jogo <= 0) {
        fprintf(stderr, "Configuração inválida! Todos os valores devem ser positivos.\n");
        exit(EXIT_FAILURE);
    }

    config.num_tedax = num_tedax;
    config.num_bancadas = num_bancadas;
    config.tempo_jogo = tempo_jogo;

    printf("Configuração inicial definida:\n");
    printf("  Número de Tedax: %d\n", config.num_tedax);
    printf("  Número de Bancadas: %d\n", config.num_bancadas);
    printf("  Tempo de Jogo: %d segundos\n", config.tempo_jogo);
}

// Finaliza mutexes e semáforos
void finalizar_sincronizacao() {
    pthread_mutex_destroy(&mutex_bancadas);
    pthread_mutex_destroy(&mutex_mural);
    sem_destroy(&sem_bancadas);
    sem_destroy(&sem_modulos);
    sem_destroy(&sem_comando);
}
