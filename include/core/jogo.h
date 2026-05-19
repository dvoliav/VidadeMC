#ifndef JOGO_H
#define JOGO_H

void iniciarJogo(void);
void executarJogo(void);
void finalizarJogo(void);
void mudarTela(int novaTela);
int obterSemanaAtual(void);
int obterFamaAtual(void);
void aumentarFama(int quantidade);
void avancarSemana(void);

#endif