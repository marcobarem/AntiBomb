#include "../include/tedax.h"
#include "../include/mural.h"
#include "../include/utils.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

// Array de threads e flag para controle do jogo
pthread_t *tedax_threads;
static bool jogo_ativo = true;

// Função que cada thread Tedax executará
void *tedax_func(void *arg) {
    int id = *(int *)arg;
    free(arg);

    while (jogo_ativo) {
        sem_wait(&sem_modulos); // Aguarda até que um módulo esteja disponível

        pthread_mutex_lock(&mutex_mural);
        if (mural_count > 0) {
            Modulo modulo = mural[--mural_count];
            pthread_mutex_unlock(&mutex_mural);

            printf("Tedax %d está desarmando o módulo %s\n", id, modulo.tipo);
            sleep(modulo.tempo_para_desarmar); // Simula o tempo de desarme
            printf("Tedax %d desarmou o módulo %s\n", id, modulo.tipo);
        } else {
            pthread_mutex_unlock(&mutex_mural);
        }
    }
    return NULL;
}




// Inicializa as threads Tedax
void inicializar_tedax(int num_tedax) {
    tedax_threads = malloc(num_tedax * sizeof(pthread_t));
    for (int i = 0; i < num_tedax; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;

        if (pthread_create(&tedax_threads[i], NULL, tedax_func, id) != 0) {
            fprintf(stderr, "Erro ao criar a thread Tedax %d\n", *id);
            free(id);
        } else {
            printf("Thread Tedax %d criada com sucesso.\n", *id); // Log
        }
    }
}





// Envia um módulo para um Tedax (lógica simulada)
int enviar_modulo_para_tedax(int tedax_id, int modulo_id, int bancada_id) {
    if (tedax_id < 1 || tedax_id > config.num_tedax || 
        modulo_id < 1 || bancada_id < 1 || bancada_id > config.num_bancadas) {
        printf("Erro: IDs inválidos para Tedax (%d), Módulo (%d), ou Bancada (%d).\n",
               tedax_id, modulo_id, bancada_id);
        return 0; // Falha
    }

    // Verifica a disponibilidade da bancada especificada
    pthread_mutex_lock(&mutex_bancadas);
    if (bancadas[bancada_id - 1].ocupada) {
        printf("Erro: Bancada %d já está ocupada.\n", bancada_id);
        pthread_mutex_unlock(&mutex_bancadas);
        return 0; // Falha
    }

    // Marca a bancada como ocupada e atribui o Tedax a ela
    bancadas[bancada_id - 1].ocupada = true;
    bancadas[bancada_id - 1].tedax_id = tedax_id;
    pthread_mutex_unlock(&mutex_bancadas);

    // Simulação do desarme
    printf("Tedax %d está desarmando o Módulo %d na Bancada %d.\n", tedax_id, modulo_id, bancada_id);
    sleep(2); // Simula o tempo de desarme

    // Libera a bancada após o desarme
    pthread_mutex_lock(&mutex_bancadas);
    bancadas[bancada_id - 1].ocupada = false;
    bancadas[bancada_id - 1].tedax_id = -1;
    pthread_mutex_unlock(&mutex_bancadas);

    printf("Tedax %d desarmou o Módulo %d na Bancada %d. Bancada liberada.\n", tedax_id, modulo_id, bancada_id);
    return 1; // Sucesso
}


// Finaliza as threads Tedax
void finalizar_tedax() {
    jogo_ativo = false; // Marca o jogo como encerrado

    for (int i = 0; i < config.num_tedax; i++) {
        if (pthread_join(tedax_threads[i], NULL) != 0) {
            fprintf(stderr, "Erro ao aguardar a finalização da thread Tedax %d\n", i + 1);
        } else {
            printf("Thread Tedax %d finalizada com sucesso.\n", i + 1);
        }
    }

    free(tedax_threads); // Libera a memória alocada para as threads
    printf("Todas as threads Tedax foram finalizadas com sucesso.\n");
}



