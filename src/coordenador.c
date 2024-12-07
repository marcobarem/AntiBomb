#include "coordenador.h"
#include "mural.h"
#include "utils.h"
#include "exibicao.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>

// Flag para indicar quando o jogo deve terminar
static bool jogo_ativo = true;

// Função auxiliar para capturar entrada do jogador
void capturar_input(char *input, size_t tamanho) {
    mvprintw(LINES - 2, 0, "Digite o comando (Ex: 1-M2-1 para Tedax 1 desarmar Módulo 2 na Bancada 1): ");
    refresh();
    getstr(input);
}

// Thread principal do coordenador
void *coordenador_func(void *arg) {
    char comando[50];

    while (jogo_ativo) {
        // Captura o comando do jogador
        capturar_input(comando, sizeof(comando));

        // Exemplo de comando: "1-M2-1" (Tedax 1, Módulo 2, Bancada 1)
        int tedax_id, bancada_id;
        char modulo_id[10];

        if (sscanf(comando, "%d-%[^-]-%d", &tedax_id, modulo_id, &bancada_id) == 3) {
            // Verifica se há bancadas disponíveis
            if (sem_trywait(&sem_bancadas) == 0) { // Bancada disponível
                pthread_mutex_lock(&mutex_mural);

                // Tenta obter o módulo do mural
                Modulo modulo = obter_modulo_por_id(modulo_id);
                if (modulo.desarmado) {
                    mvprintw(LINES - 1, 0, "Módulo já foi desarmado! Tente novamente.\n");
                } else {
                    mvprintw(LINES - 1, 0, "Designando módulo %s para Tedax %d na Bancada %d...\n",
                             modulo.tipo, tedax_id, bancada_id);
                    // Aqui, a lógica pode ser expandida para passar o módulo para o Tedax
                }

                pthread_mutex_unlock(&mutex_mural);
            } else {
                mvprintw(LINES - 1, 0, "Nenhuma bancada disponível! Aguarde...\n");
            }
        } else {
            mvprintw(LINES - 1, 0, "Comando inválido! Tente novamente.\n");
        }

        refresh();
    }

    return NULL;
}

void inicializar_coordenador() {
    pthread_t thread_coordenador;

    // Cria a thread do coordenador
    if (pthread_create(&thread_coordenador, NULL, coordenador_func, NULL) != 0) {
        fprintf(stderr, "Erro ao criar a thread do coordenador\n");
        exit(EXIT_FAILURE);
    }
}

void finalizar_coordenador() {
    jogo_ativo = false; // Encerra o loop da thread do coordenador
}
