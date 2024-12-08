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
    free(arg); // Libera a memória do ID

    while (jogo_ativo) {
        Modulo modulo = obter_modulo();

        if (strcmp(modulo.tipo, "vazio") == 0) {
            usleep(100000); // Aguarda antes de tentar novamente
            continue;
        }

        sleep(modulo.tempo_para_desarmar);

        if (jogo_ativo) { // Verifica o estado do jogo antes de exibir mensagens
            printf("Tedax %d desarmou o módulo %s\n", id, modulo.tipo);
        }
    }

    printf("Thread Tedax %d encerrando.\n", id);
    return NULL;
}

// Inicializa as threads Tedax
void inicializar_tedax(int num_tedax) {
    tedax_threads = malloc(num_tedax * sizeof(pthread_t));
    for (int i = 0; i < num_tedax; i++) {
        int *id = malloc(sizeof(int)); // Aloca memória para o ID
        *id = i + 1; // Define o ID único para a thread Tedax

        if (pthread_create(&tedax_threads[i], NULL, tedax_func, id) != 0) {
            fprintf(stderr, "Erro ao criar a thread Tedax %d\n", *id);
            free(id); // Libera memória em caso de erro
        }
    }
}




// Envia um módulo para um Tedax (lógica simulada)
int enviar_modulo_para_tedax(int tedax_id, int modulo_id, int bancada_id) {
    if (tedax_id < 1 || modulo_id < 1 || bancada_id < 1) {
        printf("Erro: IDs inválidos para Tedax (%d), Módulo (%d), ou Bancada (%d).\n",
               tedax_id, modulo_id, bancada_id);
        return 0; // Falha
    }

    // Simulação de processamento
    printf("Tedax %d está desarmando o Módulo %d na Bancada %d.\n", tedax_id, modulo_id, bancada_id);
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



