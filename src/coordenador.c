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

    // Valida o formato do comando
    if (sscanf(comando, "%d-M%d-%d", &tedax_id, &modulo_id, &bancada_id) != 3) {
        mvprintw(LINES - 1, 0, "Erro: Comando inválido! Use o formato: Tedax-Módulo-Bancada (Ex: 1-M2-1).");
        refresh();
        return 0; // Comando inválido
    }

    // Valida IDs
    if (tedax_id < 1 || tedax_id > config.num_tedax) {
        mvprintw(LINES - 1, 0, "Erro: Tedax %d é inválido! Escolha entre 1 e %d.", tedax_id, config.num_tedax);
        refresh();
        return 0; // Comando inválido
    }
    if (modulo_id < 1 || modulo_id > MAX_MODULOS) {
        mvprintw(LINES - 1, 0, "Erro: Módulo %d é inválido! Escolha entre 1 e %d.", modulo_id, MAX_MODULOS);
        refresh();
        return 0; // Comando inválido
    }
    if (bancada_id < 1 || bancada_id > config.num_bancadas) {
        mvprintw(LINES - 1, 0, "Erro: Bancada %d é inválida! Escolha entre 1 e %d.", bancada_id, config.num_bancadas);
        refresh();
        return 0; // Comando inválido
    }

    // Obtém o módulo correspondente do mural
    pthread_mutex_lock(&mutex_mural);
    Modulo *modulo = NULL;
    for (int i = 0; i < mural_count; i++) {
        if (atoi(mural[i].tipo + 1) == modulo_id) { // Extrai o ID numérico do módulo
            modulo = &mural[i];
            break;
        }
    }
    pthread_mutex_unlock(&mutex_mural);

    if (!modulo) {
        mvprintw(LINES - 1, 0, "Erro: Módulo %d não encontrado no mural.", modulo_id);
        refresh();
        return 0; // Comando inválido
    }

    // Tenta enviar o módulo para o Tedax e a bancada especificados
    if (!enviar_modulo_para_tedax(tedax_id, modulo_id, bancada_id)) {
        mvprintw(LINES - 1, 0, "Erro: Não foi possível atribuir o Módulo %d ao Tedax %d na Bancada %d.", modulo_id, tedax_id, bancada_id);
        refresh();
        return 0; // Comando inválido
    }

    // Mensagem de sucesso
    mvprintw(LINES - 1, 0, "Tedax %d desarmando Módulo %d na Bancada %d.", tedax_id, modulo_id, bancada_id);
    refresh();
    return 1; // Comando processado com sucesso
}

// Thread principal do coordenador
void *coordenador_func(void *arg) {
    char comando[50];

    while (jogo_ativo) {
        capturar_input(comando, sizeof(comando)); // Captura o comando do jogador
        sem_post(&sem_comando); // Sinaliza que há um novo comando

        if (processar_comando(comando)) {
            mvprintw(LINES - 1, 0, "Comando processado com sucesso.");
        } else {
            mvprintw(LINES - 1, 0, "Erro ao processar o comando.");
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
