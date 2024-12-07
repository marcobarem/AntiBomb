#ifndef MURAL_H
#define MURAL_H

#include <stdbool.h>

// Estrutura de um módulo
typedef struct {
    char tipo[10];             // Tipo do módulo
    int tempo_para_desarmar;   // Tempo necessário para desarmar
    bool desarmado;            // Status de desarme
} Modulo;

// Funções do mural
void inicializar_mural();
void gerar_modulo();
Modulo obter_modulo();
Modulo obter_modulo_por_id(const char *id);
bool mural_vazio();
void finalizar_mural();

#endif
