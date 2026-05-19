#ifndef JOGO_H
#define JOGO_H
#include <stdbool.h>

void iniciarJogo(void);
void executarJogo(void);
void finalizarJogo(void);
void mudarTela(int novaTela);
int obterSemanaAtual(void);
int obterFamaAtual(void);
void aumentarFama(int quantidade);
void avancarSemana(void);
void definirMinigameAtual(int minigame);
int obterMinigameAtual(void);
bool acaoDaSemanaJaFoiFeita(void);
void marcarAcaoDaSemanaComoFeita(void);

#endif