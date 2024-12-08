#include "../include/exibicao.h"
#include "../include/utils.h"
#include "../include/mural.h"
#include <ncurses.h>
#include <semaphore.h>

void inicializar_exibicao() {
    initscr();
    cbreak();
    noecho();
    refresh();
}

void atualizar_exibicao() {
    clear(); // Limpa a tela antes de imprimir novas informações

    mvprintw(0, 0, "Tempo restante: %d segundos", tempo_restante);

    pthread_mutex_lock(&mutex_mural);
    mvprintw(1, 0, "Módulos pendentes: %d", mural_count);
    for (int i = 0; i < mural_count; i++) {
        mvprintw(2 + i, 0, "- %s (%d segundos)", mural[i].tipo, mural[i].tempo_para_desarmar);
    }
    pthread_mutex_unlock(&mutex_mural);

    // Obtém o número de bancadas disponíveis usando sem_getvalue
    int bancadas_disponiveis;
    sem_getvalue(&sem_bancadas, &bancadas_disponiveis);

    mvprintw(LINES - 3, 0, "Bancadas disponíveis: %d", bancadas_disponiveis);

    refresh(); // Atualiza a exibição
}



void finalizar_exibicao() {
    endwin();
}

