#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h> 


typedef struct {
    int tedax_id;   // ID do Tedax utilizando a bancada
    bool ocupada;   // Indica se a bancada está ocupada
} Bancada;

// Estrutura para configuração inicial
typedef struct {
    int num_tedax;
    int num_bancadas;
    int tempo_jogo;
} Config;

// Variável global para configuração
extern Config config;
extern Bancada *bancadas;
// Mutexes globais
extern pthread_mutex_t mutex_bancadas;
extern pthread_mutex_t mutex_mural;

// Semáforos globais
extern sem_t sem_bancadas;
extern sem_t sem_modulos;
extern sem_t sem_comando; // Declara o semáforo de comandos

// Funções utilitárias
void inicializar_sincronizacao();
void finalizar_sincronizacao();
void definir_configuracao(int num_tedax, int num_bancadas, int tempo_jogo);
void finalizar_sincronizacao();

#endif
