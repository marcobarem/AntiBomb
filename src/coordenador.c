#include "../include/coordenador.h"
#include "../include/mural.h"
#include "../include/utils.h"
#include "../include/exibicao.h"
#include "../include/tedax.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

// Flag para indicar quando o jogo deve terminar
bool jogo_ativo = true;

// Função para capturar entrada do jogador
void capturar_input(char *input, size_t tamanho) {
    while (1) {
        mvprintw(LINES - 2, 0, "Digite o comando (Ex: 1-M2-1 para Tedax 1 desarmar Módulo 2 na Bancada 1): ");
        clrtoeol();
        refresh();

        getstr(input);

        if (strlen(input) > 0) {
            return;
        }

        mvprintw(LINES - 1, 0, "Entrada inválida! Tente novamente.");
        refresh();
    }
}


// Processa comandos do jogador
int processar_comando(const char *comando) {
    int tedax_id, modulo_id, bancada_id;

    if (sscanf(comando, "%d-M%d-%d", &tedax_id, &modulo_id, &bancada_id) == 3) {
        if (tedax_id > 0 && modulo_id > 0 && bancada_id > 0) {
            if (enviar_modulo_para_tedax(tedax_id, modulo_id, bancada_id)) {
                mvprintw(LINES - 1, 0, "Tedax %d está desarmando o Módulo %d na Bancada %d.",
                         tedax_id, modulo_id, bancada_id);
                refresh();
                return 1; // Comando processado com sucesso
            }
        }
    }

    mvprintw(LINES - 1, 0, "Comando inválido! Use o formato correto (Ex: 1-M2-1).");
    refresh();
    return 0; // Comando inválido
}

// Thread principal do coordenador
void *coordenador_func(void *arg) {
    char comando[50];

    while (jogo_ativo) {
        capturar_input(comando, sizeof(comando)); // Captura o comando do jogador

        int tedax_id, bancada_id;
        char modulo_id[10];

        if (sscanf(comando, "%d-%[^-]-%d", &tedax_id, modulo_id, &bancada_id) == 3) {
            if (sem_trywait(&sem_bancadas) == 0) { // Bancada disponível
                pthread_mutex_lock(&mutex_mural);

                Modulo modulo = obter_modulo_por_id(modulo_id);
                if (modulo.desarmado) {
                    mvprintw(LINES - 1, 0, "Módulo já foi desarmado! Tente novamente.\n");
                } else {
                    mvprintw(LINES - 1, 0, "Designando módulo %s para Tedax %d na Bancada %d...\n",
                             modulo.tipo, tedax_id, bancada_id);
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

    if (pthread_create(&thread_coordenador, NULL, coordenador_func, NULL) != 0) {
        fprintf(stderr, "Erro ao criar a thread do coordenador\n");
        exit(EXIT_FAILURE);
    }

    // Detach da thread para evitar necessidade de join
    pthread_detach(thread_coordenador);
}

void finalizar_coordenador() {
    jogo_ativo = false; // Encerra o loop da thread do coordenador
}
