#include <stdio.h>
#include "mural.h"
#include "exibicao.h"
#include "tedax.h"
#include "coordenador.h"
#include "utils.h"

int main() {
    inicializar_sincronizacao();
    inicializar_mural();
    inicializar_exibicao();
    inicializar_tedax(3);  // Exemplo com 3 Tedax
    inicializar_coordenador();

    // Aguarda finalização do jogo
    while (!mural_vazio()) {
        atualizar_exibicao();
    }

    finalizar_coordenador();
    finalizar_tedax();
    finalizar_exibicao();
    finalizar_mural();
    finalizar_sincronizacao();

    return 0;
}
