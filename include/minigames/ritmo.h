#ifndef RITMO_H
#define RITMO_H

#include <stdbool.h>

void iniciarMinigameRitmo(void);

void atualizarMinigameRitmo(void);

void desenharMinigameRitmo(void);

bool minigameRitmoFinalizado(void);

int obterPontuacaoRitmo(void);

char* obterQualidadeMusica(void);

#endif