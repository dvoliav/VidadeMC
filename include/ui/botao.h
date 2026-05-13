#ifndef BOTAO_H
#define BOTAO_H

#include "raylib.h"

typedef struct {
    Rectangle area;
    char texto[50];
} Botao;

bool botaoFoiClicado(Botao botao);

void desenharBotao(Botao botao);

#endif