#ifndef SHOW_H
#define SHOW_H

#include <stdbool.h>

void iniciarMinigameShow(void);

void atualizarMinigameShow(void);

void desenharMinigameShow(void);

bool minigameShowFinalizado(void);

int obterPontuacaoShow(void);

float calcularFatorSorte(int porcentagem);

#endif