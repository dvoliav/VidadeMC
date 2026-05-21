#include <stdio.h>
#include "minigames/ritmo.h"
#include "raylib.h"
#include "minigames/show.h"
#include "telas/tela_acoes.h"
#include "core/jogo.h"
#include "core/telas.h"
#include "ui/botao.h"
#include "core/assets.h"
static Texture2D background;
static bool texturaCarregada = false;

static Botao botaoCriarMusica = {
    .area = {440, 210, 400, 70},
    .texto = "CRIAR MUSICA"
};

static Botao botaoPostarMusica = {
    .area = {440, 310, 400, 70},
    .texto = "POSTAR MUSICA"
};

static Botao botaoShow = {
    .area = {440, 410, 400, 70},
    .texto = "FAZER SHOW"
};

static Botao botaoVoltar = {
    .area = {440, 510, 400, 70},
    .texto = "VOLTAR"
};

void atualizarTelaAcoes(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture("assets/Back.png");
        texturaCarregada = true;
    }

    if (botaoFoiClicado(botaoCriarMusica))
    {
        if (!acaoDaSemanaJaFoiFeita())
        {
            definirMinigameAtual(MINIGAME_CRIAR_MUSICA);

            iniciarMinigameRitmo();

            mudarTela(TELA_MINIGAME);
        }
    }

    if (botaoFoiClicado(botaoPostarMusica))
    {
        if (!acaoDaSemanaJaFoiFeita())
        {
            definirMinigameAtual(MINIGAME_POSTAR_MUSICA);
            mudarTela(TELA_MINIGAME);
        }
    }

    if (botaoFoiClicado(botaoShow))
{
    if (!acaoDaSemanaJaFoiFeita())
    {
        definirMinigameAtual(MINIGAME_SHOW);

        iniciarMinigameShow();

        mudarTela(TELA_MINIGAME);
    }
}

    if (botaoFoiClicado(botaoVoltar))
    {
        mudarTela(TELA_MENU);
    }
}

void desenharTelaAcoes(void)
{
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, 1280, 720},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    const char *titulo = "ESCOLHA UMA ACAO";

    int tamanhoFonteTitulo = 45;

    float larguraTitulo = MeasureTextEx(
        fonteMenu,
        titulo,
        tamanhoFonteTitulo,
        2
    ).x;

    DrawTextEx(
        fonteMenu,

        titulo,

        (Vector2){
            (1280 - larguraTitulo) / 2,
            90
        },

        tamanhoFonteTitulo,

        2,

        WHITE
    );
    desenharBotao(botaoCriarMusica);
    desenharBotao(botaoPostarMusica);
    desenharBotao(botaoShow);
    desenharBotao(botaoVoltar);
}