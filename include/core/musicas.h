#ifndef MUSICAS_H
#define MUSICAS_H

#include <stdbool.h>

typedef struct Musica {

    char nome[50];

    int pontuacao;

    char qualidade[20];

    bool postada;

    struct Musica* prox;

} Musica;

void adicionarMusica(
    char nome[],
    int pontuacao,
    char qualidade[]
);

Musica* obterListaMusicas(void);

#endif