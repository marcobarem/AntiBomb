#include "../include/exibicao.h"
#include "../include/exibicao.h"
#include <ncurses.h>


void inicializar_exibicao() {
    initscr();
    cbreak();
    noecho();
    refresh();
}

void atualizar_exibicao() {
    clear(); // Limpa a tela antes de imprimir novas informações

    // Exibe o tempo restante e outras informações relevantes do jogo
    mvprintw(0, 0, "Tempo restante: %d segundos", tempo_restante);

    // Opcional: Adicione outras informações de status do jogo
    mvprintw(1, 0, "Status dos módulos e Tedax...");

    refresh(); // Atualiza a exibição
}


void finalizar_exibicao() {
    endwin();
}

