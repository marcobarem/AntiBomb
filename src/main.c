#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "../include/utils.h"
#include "../include/mural.h"
#include "../include/exibicao.h"
#include "../include/tedax.h"
#include "../include/coordenador.h"

int tempo_restante = 180; // Variável global

void controle_tempo() {
    tempo_restante = config.tempo_jogo; // Inicializa o tempo
    char comando[50]; // Buffer para o comando do jogador

    while (tempo_restante > 0 && !mural_vazio()) {
        atualizar_exibicao(); // Atualiza a interface do jogo

        capturar_input(comando, sizeof(comando)); // Captura o comando do jogador

        if (processar_comando(comando)) { // Processa o comando
            sleep(1); // Avança o tempo somente se o comando foi válido
            tempo_restante--;
        }
    }

    // Exibe o resultado do jogo
    clear();
    if (mural_vazio()) {
        mvprintw(0, 0, "Todos os módulos foram desarmados! Parabéns!");
    } else {
        mvprintw(0, 0, "O tempo acabou! A bomba explodiu...");
    }
    refresh();

    jogo_ativo = false; // Marca o jogo como encerrado
}


int main() {
    // Configuração inicial do jogo
    definir_configuracao(3, 2, 60); // Configura 3 Tedax, 2 Bancadas, e 60 segundos de jogo

    // Inicialização dos componentes do jogo
    inicializar_sincronizacao();
    inicializar_mural();
    inicializar_exibicao();
    inicializar_tedax(config.num_tedax);
    inicializar_coordenador();

    // Controle principal do jogo
    controle_tempo();

    // Finalização dos componentes do jogo
    finalizar_coordenador();
    finalizar_tedax();
    finalizar_exibicao();
    finalizar_mural();
    finalizar_sincronizacao();

    return 0;
}
