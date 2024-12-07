#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/utils.h"
#include "../include/mural.h"
#include "../include/exibicao.h"
#include "../include/tedax.h"
#include "../include/coordenador.h"

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

    // Controle de tempo do jogo
    int tempo_restante = config.tempo_jogo;
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
