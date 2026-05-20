#include "raylib.h"

#include "telas/tela_minigame.h"

#include "core/jogo.h"
#include "core/telas.h"

#include "ui/botao.h"

#include "minigames/show.h"

static Texture2D background;

static bool texturaCarregada = false;

/*
    ESTADO DA TELA
*/

static bool telaResultado = false;

/*
    RESULTADOS
*/

static int pontosFinais = 0;

static int famaFinal = 0;

/*
    BOTAO
*/

static Botao botaoConcluir = {
    .area = {440, 500, 400, 80},
    .texto = "CONCLUIR SHOW"
};

void atualizarTelaMinigame(void)
{
    if (!texturaCarregada)
    {
        background =
            LoadTexture("assets/show/background_show.png");

        texturaCarregada = true;
    }

    /*
        TELA RESULTADO
    */

    if (telaResultado)
    {
        if (botaoFoiClicado(botaoConcluir))
        {
            telaResultado = false;

            mudarTela(TELA_MENU);
        }

        return;
    }

    /*
        GAMEPLAY
    */

    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_SHOW:

            atualizarMinigameShow();

            if (minigameShowFinalizado())
            {
                pontosFinais =
                    obterPontuacaoShow();

                int porcentagem =
                    (pontosFinais * 100) / 1500;

                float fator =
                    calcularFatorSorte(porcentagem);

                int famaBase = 100;

                famaFinal =
                    (int)(famaBase * fator);

                aumentarFama(famaFinal);

                marcarAcaoDaSemanaComoFeita();

                /*
                    MUDA PRA TELA RESULTADO
                */

                telaResultado = true;
            }

            break;
    }
}

void desenharTelaMinigame(void)
{
    /*
        FUNDO
    */

    DrawTexturePro(
        background,

        (Rectangle){0, 0, background.width, background.height},

        (Rectangle){0, 0, 1280, 720},

        (Vector2){0, 0},

        0.0f,

        WHITE
    );

    /*
        TELA RESULTADO
    */

    if (telaResultado)
    {
        /*
            ESCURECER TELA
        */

        DrawRectangle(
            0,
            0,
            1280,
            720,
            Fade(BLACK, 0.5f)
        );

        DrawText(
            "RESULTADO DO SHOW",
            350,
            140,
            55,
            WHITE
        );

        char textoPontos[100];

        sprintf(
            textoPontos,
            "PONTOS: %d",
            pontosFinais
        );

        DrawText(
            textoPontos,
            460,
            280,
            45,
            WHITE
        );

        char textoFama[100];

        sprintf(
            textoFama,
            "FAMA GANHA: %d",
            famaFinal
        );

        DrawText(
            textoFama,
            420,
            370,
            45,
            WHITE
        );

        desenharBotao(botaoConcluir);

        return;
    }

    /*
        GAMEPLAY
    */

    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_SHOW:

            desenharMinigameShow();

            break;
    }
}