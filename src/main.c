#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"
#include "../include/mural.h"
#include "../include/exibicao.h"
#include "../include/tedax.h"
#include "../include/coordenador.h"
#include <ncurses.h>

int tempo_restante; // Variável global

void controle_tempo() {
    tempo_restante = config.tempo_jogo; // Inicializa o tempo com a configuração inicial
    char comando[50]; // Buffer para o comando do jogador

    while (tempo_restante > 0 && !mural_vazio()) {
        atualizar_exibicao(); // Atualiza a interface do jogo

        // Solicita o comando do jogador
        mvprintw(LINES - 1, 0, "Digite o comando (Ex: 1-M2-1 para Tedax 1 desarmar Módulo 2 na Bancada 1): ");
        clrtoeol(); // Limpa a linha atual antes de capturar a entrada
        refresh();

        capturar_input(comando, sizeof(comando)); // Captura o comando do jogador

        if (strlen(comando) == 0) {
            mvprintw(LINES - 1, 0, "Comando vazio! Por favor, digite um comando válido.");
            refresh();
            continue; // Volta para o início do loop
        }

        // Processa o comando do jogador
        if (processar_comando(comando)) { // processar_comando deve retornar 1 ou 0
            // Avança o tempo do jogo somente se o comando foi válido
            sleep(1);
            tempo_restante--;
        }
    }

    // Exibe o resultado do jogo
    clear(); // Limpa a tela para exibir o resultado final
    if (mural_vazio()) {
        mvprintw(0, 0, "Todos os módulos foram desarmados! Parabéns!");
    } else {
        mvprintw(0, 0, "O tempo acabou! A bomba explodiu...");
    }
    refresh();
}



int main() {
    // Definir a configuração inicial
    definir_configuracao(3, 2, 60); // 3 Tedax, 2 Bancadas, 60 segundos de jogo

    // Inicializar recursos de sincronização
    inicializar_sincronizacao();

    // Inicializar componentes do jogo
    inicializar_mural();
    inicializar_exibicao();
    inicializar_tedax(config.num_tedax);
    inicializar_coordenador();

    controle_tempo();

    // Controle de tempo do jogo
    tempo_restante = config.tempo_jogo;

    while (tempo_restante > 0 && !mural_vazio()) {
        sleep(1); // Avança um segundo
        tempo_restante--;

        // Atualiza a exibição com o tempo restante e status do jogo
        atualizar_exibicao();

        // Informações de depuração (opcional)
        printf("Tempo restante: %d segundos\n", tempo_restante);
    }

    // Finalizar o jogo e exibir resultados
    if (mural_vazio()) {
        printf("Todos os módulos foram desarmados! Parabéns!\n");
    } else {
        printf("O tempo acabou! A bomba explodiu...\n");
    }

    // Finalizar componentes do jogo
    finalizar_coordenador();
    finalizar_tedax();
    finalizar_exibicao();
    finalizar_mural();
    finalizar_sincronizacao();

    return 0;
}
