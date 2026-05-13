#include "raylib.h"

#include "telas/tela_inicio.h"

#include "core/jogo.h"
#include "core/telas.h"

#include "ui/botao.h"

static Texture2D background;

static bool texturaCarregada = false;

static Botao botaoIniciar = {
    .area = {
        490,
        540,
        300,
        80
    },

    .texto = "INICIAR"
};

void atualizarTelaInicio(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture(
            "assets/BackgroundVidadeMC.png"
        );

        texturaCarregada = true;
    }

    if (botaoFoiClicado(botaoIniciar))
    {
        mudarTela(TELA_SAVE);
    }
}

void desenharTelaInicio(void)
{
    DrawTexturePro(
        background,
        (Rectangle){
            0,
            0,
            background.width,
            background.height
        },

        (Rectangle){
            0,
            0,
            1280,
            720
        },

        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    desenharBotao(botaoIniciar);
}