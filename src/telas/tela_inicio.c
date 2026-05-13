#include "raylib.h"

#include "telas/tela_inicio.h"
#include "core/jogo.h"
#include "core/telas.h"

static Texture2D background;
static bool texturaCarregada = false;

static Rectangle botaoIniciar = {
    490,
    540,
    300,
    80
};

void atualizarTelaInicio(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture("assets/BackgroundVidadeMC.png");

        texturaCarregada = true;
    }

    Vector2 mouse = GetMousePosition();

    bool mouseEmCima = CheckCollisionPointRec(
        mouse,
        botaoIniciar
    );

    if (mouseEmCima &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        mudarTela(TELA_MENU);
    }
}

void desenharTelaInicio(void)
{
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, 1280, 720},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    Vector2 mouse = GetMousePosition();

    bool mouseEmCima = CheckCollisionPointRec(
        mouse,
        botaoIniciar
    );

    Color corBotao;

    if (mouseEmCima)
    {
        corBotao = (Color){255, 0, 180, 255};
    }
    else
    {
        corBotao = (Color){40, 15, 60, 220};
    }

    DrawRectangleRounded(
        botaoIniciar,
        0.3f,
        10,
        corBotao
    );

    DrawRectangleRoundedLines(
        botaoIniciar,
        0.3f,
        10,
        WHITE
    );

    int tamanhoFonte = 36;

    const char *texto = "INICIAR";

    int larguraTexto = MeasureText(
        texto,
        tamanhoFonte
    );

    DrawText(
        texto,
        botaoIniciar.x + (botaoIniciar.width - larguraTexto) / 2,
        botaoIniciar.y + 20,
        tamanhoFonte,
        WHITE
    );
}