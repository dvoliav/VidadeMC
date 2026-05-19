#ifndef TELAS_H
#define TELAS_H

typedef enum {
    TELA_INICIO,
    TELA_SAVE,
    TELA_CRIAR_MC,
    TELA_MENU,
    TELA_ACOES,
    TELA_RANKING,
    TELA_MINIGAME
} TelaAtual;

typedef enum {
    MINIGAME_CRIAR_MUSICA,
    MINIGAME_POSTAR_MUSICA,
    MINIGAME_SHOW
} TipoMinigame;

#endif