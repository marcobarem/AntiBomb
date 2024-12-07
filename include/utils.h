#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <semaphore.h>

// Estrutura para configuração inicial
typedef struct {
    int num_tedax;
    int num_bancadas;
    int tempo_jogo;
} Config;

// Variável global para configuração
extern Config config;

// Mutexes globais
extern pthread_mutex_t mutex_bancadas;
extern pthread_mutex_t mutex_mural;

// Semáforos globais
extern sem_t sem_bancadas;
extern sem_t sem_modulos;

// Funções utilitárias
void inicializar_sincronizacao();
void finalizar_sincronizacao();
void definir_configuracao(int num_tedax, int num_bancadas, int tempo_jogo);

#endif
