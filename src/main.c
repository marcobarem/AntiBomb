#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include "../include/utils.h"
#include "../include/mural.h"
#include "../include/exibicao.h"
#include "../include/tedax.h"
#include "../include/coordenador.h"

int tempo_restante; // Variável global

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
        printf("Tempo restante: %d\n", tempo_restante);
        printf("Mural vazio: %d\n", mural_vazio());

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
    definir_configuracao(3, 2, 180); // Configura 3 Tedax, 2 Bancadas, e 180 segundos de jogo
    printf("Configuração inicial concluída.\n");

    inicializar_sincronizacao();
    printf("Sincronização inicializada.\n");

    inicializar_mural();
    printf("Mural inicializado.\n");

    inicializar_exibicao();
    printf("Exibição inicializada.\n");

    inicializar_tedax(config.num_tedax);
    printf("Threads Tedax inicializadas.\n");

    inicializar_coordenador();
    printf("Coordenador inicializado.\n");

    controle_tempo(); // Controle principal do jogo

    finalizar_coordenador();
    printf("Coordenador finalizado.\n");

    finalizar_tedax();
    printf("Threads Tedax finalizadas.\n");

    finalizar_exibicao();
    printf("Exibição finalizada.\n");

    finalizar_mural();
    printf("Mural finalizado.\n");

    finalizar_sincronizacao();
    printf("Sincronização finalizada.\n");

    return 0;
}

