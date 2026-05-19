#include "raylib.h"

#include "telas/tela_minigame.h"

#include "core/jogo.h"
#include "core/telas.h"

#include "ui/botao.h"

static Texture2D background;

static bool texturaCarregada = false;

static Botao botaoSucesso = {
    .area = {440, 320, 400, 80},
    .texto = "SIMULAR SUCESSO"
};

static Botao botaoVoltar = {
    .area = {440, 440, 400, 80},
    .texto = "VOLTAR"
};

void atualizarTelaMinigame(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture(
            "assets/Back.png"
        );

        texturaCarregada = true;
    }

    if (botaoFoiClicado(botaoSucesso))
    {
        int tipo = obterMinigameAtual();

        switch (tipo)
        {
            case MINIGAME_CRIAR_MUSICA:
                aumentarFama(10);
                break;

            case MINIGAME_POSTAR_MUSICA:
                aumentarFama(15);
                break;

            case MINIGAME_SHOW:
                aumentarFama(20);
                break;
        }

        marcarAcaoDaSemanaComoFeita();

        mudarTela(TELA_MENU);
    }

    if (botaoFoiClicado(botaoVoltar))
    {
        mudarTela(TELA_ACOES);
    }
}

void desenharTelaMinigame(void)
{
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},

        (Rectangle){0, 0, 1280, 720},

        (Vector2){0, 0},

        0.0f,

        WHITE
    );

    const char *titulo =
        "MINIGAME EM DESENVOLVIMENTO";

    int tamanhoFonte = 45;

    int larguraTexto = MeasureText(
        titulo,
        tamanhoFonte
    );

    DrawText(
        titulo,

        (1280 - larguraTexto) / 2,

        140,

        tamanhoFonte,

        WHITE
    );

    desenharBotao(botaoSucesso);

    desenharBotao(botaoVoltar);
}