#include "raylib.h"
#include <string.h>

#include "telas/tela_criar_mc.h"
#include "core/jogo.h"
#include "core/telas.h"
#include "ui/botao.h"

static char nomeMc[30] = "";
static int quantidadeLetras = 0;

static Botao botaoConfirmar = {
    .area = {440, 500, 400, 80},
    .texto = "CONFIRMAR"
};

static Texture2D background;
static bool texturaCarregada = false;

void atualizarTelaCriarMc(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture(
            "assets/Back.png"
        );

        texturaCarregada = true;
    }

    int tecla = GetCharPressed();

    while (tecla > 0)
    {
        if ((tecla >= 32) && (tecla <= 125) && quantidadeLetras < 29)
        {
            nomeMc[quantidadeLetras] = (char)tecla;
            quantidadeLetras++;
            nomeMc[quantidadeLetras] = '\0';
        }

        tecla = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && quantidadeLetras > 0)
    {
        quantidadeLetras--;
        nomeMc[quantidadeLetras] = '\0';
    }

    if (botaoFoiClicado(botaoConfirmar) && quantidadeLetras > 0)
    {
        mudarTela(TELA_MENU);
    }
}

void desenharTelaCriarMc(void)
{
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, 1280, 720},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    const char *titulo = "CRIE SEU MC";
    int tamanhoFonteTitulo = 50;
    int larguraTitulo = MeasureText(titulo, tamanhoFonteTitulo);

    DrawText(
        titulo,
        (1280 - larguraTitulo) / 2,
        100,
        tamanhoFonteTitulo,
        WHITE
    );

    DrawRectangleRounded(
        (Rectangle){340, 250, 600, 90},
        0.25f,
        10,
        (Color){40, 15, 60, 220}
    );

    DrawRectangleRoundedLines(
        (Rectangle){340, 250, 600, 90},
        0.25f,
        10,
        WHITE
    );

    DrawText(
        nomeMc,
        370,
        280,
        35,
        WHITE
    );

    if (quantidadeLetras == 0)
    {
        DrawText(
            "Digite o nome artistico...",
            370,
            280,
            35,
            (Color){180, 180, 180, 255}
        );
    }

    desenharBotao(botaoConfirmar);
}