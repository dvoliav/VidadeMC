#include <stdio.h>
#include "raylib.h"

#include "telas/tela_minigame.h"

#include "core/jogo.h"
#include "core/telas.h"
#include "minigames/ritmo.h"
#include "ui/botao.h"
#include "core/musicas.h"

#include "minigames/show.h"
#include <string.h>

static Texture2D background;

static bool texturaCarregada = false;
static char nomeMusica[50] = "";

static int tamanhoNome = 0;



static bool telaResultado = false;


static int pontosFinais = 0;

static int famaFinal = 0;



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

    if (telaResultado)
    {
        if (obterMinigameAtual() == MINIGAME_CRIAR_MUSICA)
    {
        int tecla = GetCharPressed();

        while (tecla > 0)
        {
            if ((tecla >= 32)
                && (tecla <= 125)
                && (tamanhoNome < 49))
            {
                nomeMusica[tamanhoNome] =
                    (char)tecla;

                tamanhoNome++;

                nomeMusica[tamanhoNome] = '\0';
            }

            tecla = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            tamanhoNome--;

            if (tamanhoNome < 0)
            {
                tamanhoNome = 0;
            }

            nomeMusica[tamanhoNome] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            adicionarMusica(
                nomeMusica,
                obterPontuacaoRitmo(),
                obterQualidadeMusica()
            );

            strcpy(nomeMusica, "");

            tamanhoNome = 0;

            telaResultado = false;

            mudarTela(TELA_MENU);
        }
    }
        if (botaoFoiClicado(botaoConcluir))
        {
            telaResultado = false;

            mudarTela(TELA_MENU);
        }

        return;
    }

    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_CRIAR_MUSICA:

        atualizarMinigameRitmo();

        if (minigameRitmoFinalizado())
        {
            marcarAcaoDaSemanaComoFeita();

            telaResultado = true;
        }

        break;
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

                telaResultado = true;
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


    if (telaResultado)
    {
        if (obterMinigameAtual()
        == MINIGAME_CRIAR_MUSICA)
    {
        DrawRectangle(
            0,
            0,
            1280,
            720,
            Fade(BLACK, 0.6f)
        );

        DrawText(
            "SUA MUSICA FOI CRIADA!",
            260,
            100,
            50,
            WHITE
        );

        char textoQualidade[100];

        sprintf(
            textoQualidade,
            "QUALIDADE: %s",
            obterQualidadeMusica()
        );

        DrawText(
            textoQualidade,
            390,
            230,
            40,
            WHITE
        );

        DrawText(
            "DIGITE O NOME DA MUSICA:",
            300,
            340,
            35,
            WHITE
        );

        DrawRectangle(
            320,
            420,
            650,
            70,
            Fade(WHITE, 0.2f)
        );

        DrawText(
            nomeMusica,
            340,
            440,
            35,
            WHITE
        );

        DrawText(
            "APERTE ENTER PARA CONFIRMAR",
            300,
            560,
            30,
            GRAY
        );

        return;
    }

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


    int tipo = obterMinigameAtual();

    switch (tipo)
    {
        case MINIGAME_CRIAR_MUSICA:

           desenharMinigameRitmo();

            break;
        case MINIGAME_SHOW:

            desenharMinigameShow();

            break;
    }
}