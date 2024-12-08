#ifndef MURAL_H
#define MURAL_H

#include <stdbool.h>

#define MAX_MODULOS 10 // Define o número máximo de módulos no mural
// Estrutura de um módulo
typedef struct {
    char tipo[15];             // Tipo do módulo
    int tempo_para_desarmar;   // Tempo necessário para desarmar
    bool desarmado;            // Status de desarme
} Modulo;


extern Modulo mural[MAX_MODULOS];
extern int mural_count;


// Funções do mural
void inicializar_mural();
void gerar_modulo();
Modulo obter_modulo();
Modulo obter_modulo_por_id(const char *id);
bool mural_vazio();
void finalizar_mural();

#endif
