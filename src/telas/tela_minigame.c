#include "raylib.h"

#include "telas/tela_minigame.h"

#include "core/jogo.h"
#include "core/telas.h"

#include "ui/botao.h"

#include "minigames/show.h"

static Texture2D background;

static bool texturaCarregada = false;

void atualizarTelaMinigame(void)
{
    if (!texturaCarregada)
    {
        background = LoadTexture("assets/Back.png");

        texturaCarregada = true;
    }

    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_SHOW:

            atualizarMinigameShow();

            if (minigameShowFinalizado())
            {
                int pontos = obterPontuacaoShow();

                int porcentagem = (pontos * 100) / 1000;

                float fator = calcularFatorSorte(porcentagem);

                int famaBase = 100;

                int famaFinal = (int)(famaBase * fator);

                aumentarFama(famaFinal);

                marcarAcaoDaSemanaComoFeita();

                mudarTela(TELA_MENU);
            }

            break;
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

    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_SHOW:

            desenharMinigameShow();

            break;
    }
}