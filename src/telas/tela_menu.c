#include <stdio.h>

#include "raylib.h"

#include "telas/tela_menu.h"
#include "core/jogo.h"
#include "core/telas.h"
#include "ui/botao.h"
#include "core/assets.h"
static Texture2D background;
static bool texturaCarregada = false;

static Botao botaoAcoes = {
    .area = {440, 230, 400, 80},
    .texto = "CARREIRA  "
};

static Botao botaoRanking = {
    .area = {440, 350, 400, 80},
    .texto = "RANKING"
};

static Botao botaoVoltar = {
    .area = {440, 470, 400, 80},
    .texto = "VOLTAR"
};

static Botao botaoAvancarSemana = {
    .area = {980, 620, 260, 55},
    .texto = "DESCANSAR SEMANA"
};

void atualizarTelaMenu(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture("assets/Back.png");
        texturaCarregada = true;
    }

    if (botaoFoiClicado(botaoAcoes))
    {
        mudarTela(TELA_ACOES);
    }

    if (botaoFoiClicado(botaoRanking))
    {
        mudarTela(TELA_RANKING);
    }

    if (botaoFoiClicado(botaoVoltar))
    {
        mudarTela(TELA_SAVE);
    }

    if (botaoFoiClicado(botaoAvancarSemana))
    {
        avancarSemana();
    }
}

void desenharTelaMenu(void)
{
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, 1280, 720},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    const char *titulo = "MENU PRINCIPAL";
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
            100
        },

        tamanhoFonteTitulo,

        2,

        WHITE
    );

    char textoSemana[30];
    snprintf(textoSemana, sizeof(textoSemana), "Semana %d", obterSemanaAtual());

    int tamanhoFonteSemana = 28;
    float larguraSemana = MeasureTextEx(
        fonteMenu,
        textoSemana,
        tamanhoFonteSemana,
        2
    ).x;
    DrawTextEx(
        fonteMenu,

        textoSemana,

        (Vector2){
            1280 - larguraSemana - 40,
            35
        },

        tamanhoFonteSemana,

        2,

        WHITE
    );

    char textoFama[30];
    snprintf(textoFama, sizeof(textoFama), "Fama: %d", obterFamaAtual());

    DrawTextEx(
        fonteMenu,

        textoFama,

        (Vector2){
            40,
            35
        },

        28,

        2,

        WHITE
    );

    desenharBotao(botaoAcoes);
    desenharBotao(botaoRanking);
    desenharBotao(botaoVoltar);
    desenharBotao(botaoAvancarSemana);
}