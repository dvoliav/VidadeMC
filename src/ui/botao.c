#include <string.h>

#include "raylib.h"

#include "ui/botao.h"

bool botaoFoiClicado(Botao botao)
{
    Vector2 mouse = GetMousePosition();

    bool mouseEmCima = CheckCollisionPointRec(
        mouse,
        botao.area
    );

    return mouseEmCima &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void desenharBotao(Botao botao)
{
    Vector2 mouse = GetMousePosition();

    bool mouseEmCima = CheckCollisionPointRec(
        mouse,
        botao.area
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
        botao.area,
        0.3f,
        10,
        corBotao
    );

    DrawRectangleRoundedLines(
        botao.area,
        0.3f,
        10,
        WHITE
    );

    int tamanhoFonte = 36;

    if (botao.area.width <= 280)
    {
        tamanhoFonte = 24;
    }
    int larguraTexto = MeasureText(
        botao.texto,
        tamanhoFonte
    );

    DrawText(
        botao.texto,
        botao.area.x +
        (botao.area.width - larguraTexto) / 2,

        botao.area.y + (botao.area.height - tamanhoFonte) / 2,

        tamanhoFonte,
        WHITE
    );
}