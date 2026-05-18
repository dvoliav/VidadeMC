#include "raylib.h"

#include "telas/tela_save.h"

#include "core/jogo.h"
#include "core/telas.h"

#include "ui/botao.h"


static Texture2D background;
static bool texturaCarregada = false;

static Botao botaoNovoJogo = {
    .area = {
        440,
        250,
        400,
        80
    },

    .texto = "NOVO JOGO"
};


static Botao botaoCarregar = {
    .area = {
        440,
        370,
        400,
        80
    },

    .texto = "CARREGAR SAVE"
};

static Botao botaoVoltar = {
    .area = {
        440,
        490,
        400,
        80
    },

    .texto = "VOLTAR"
};

void atualizarTelaSave(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture(
            "assets/Back.png"
        );

        texturaCarregada = true;
    }

    if (botaoFoiClicado(botaoNovoJogo))
    {
        mudarTela(TELA_CRIAR_MC);
    }

    if (botaoFoiClicado(botaoCarregar))
    {
    }

    if (botaoFoiClicado(botaoVoltar))
    {
        mudarTela(TELA_INICIO);
    }
}

void desenharTelaSave(void)
{
    ClearBackground((Color){20, 10, 30, 255});

    const char *textoTitulo = "SELECIONE UMA OPCAO";

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
    int tamanhoFonte = 40;

    int larguraTexto = MeasureText(
        textoTitulo,
        tamanhoFonte
    );

    DrawText(
        textoTitulo,

        (1280 - larguraTexto) / 2,

        120,

        tamanhoFonte,

        WHITE
    );


    desenharBotao(botaoNovoJogo);

    desenharBotao(botaoCarregar);

    desenharBotao(botaoVoltar);
}