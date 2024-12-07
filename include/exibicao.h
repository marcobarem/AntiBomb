#ifndef EXIBICAO_H
#define EXIBICAO_H

#include <stddef.h> // Adiciona a definição de size_t

extern int tempo_restante;

void capturar_input(char *input, size_t tamanho);
void inicializar_exibicao();
void atualizar_exibicao();
void finalizar_exibicao();

#endif
