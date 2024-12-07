#include "../include/exibicao.h"
#include <ncurses.h>

void inicializar_exibicao() {
    initscr();
    noecho();
    cbreak();
}

void atualizar_exibicao() {
    clear();
    mvprintw(0, 0, "Atualizando informações do jogo...");
    refresh();
}

void finalizar_exibicao() {
    endwin();
}
