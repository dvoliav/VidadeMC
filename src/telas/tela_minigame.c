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
static Texture2D backgroundResultadoMusica;
static bool backgroundResultadoCarregado = false;

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
    if (!backgroundResultadoCarregado)
    {
        backgroundResultadoMusica =
            LoadTexture(
                "assets/background_resultado_musica.png"
            );

        backgroundResultadoCarregado = true;
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
    DrawTexturePro(
        backgroundResultadoMusica,

        (Rectangle){
            0,
            0,
            backgroundResultadoMusica.width,
            backgroundResultadoMusica.height
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

    DrawRectangle(
        0,
        0,
        1280,
        720,
        Fade(BLACK, 0.45f)
    );

    DrawRectangleRounded(
        (Rectangle){250, 120, 780, 420},
        0.08f,
        10,
        Fade(BLACK, 0.55f)
    );

    DrawRectangleRoundedLines(
        (Rectangle){250, 120, 780, 420},
        0.08f,
        10,
        Fade(PINK, 0.8f)
    );

    const char* titulo =
        "SUA MUSICA FOI CRIADA!";

    int larguraTitulo =
        MeasureText(titulo, 42);

    DrawText(
        titulo,

        (1280 - larguraTitulo) / 2,

        170,

        42,

        WHITE
    );

    char textoQualidade[100];

    sprintf(
        textoQualidade,
        "QUALIDADE: %s",
        obterQualidadeMusica()
    );

    Color corQualidade = WHITE;

    if (strcmp(obterQualidadeMusica(), "RUIM") == 0)
    {
        corQualidade = GRAY;
    }
    else if (strcmp(obterQualidadeMusica(), "MEDIA") == 0)
    {
        corQualidade = SKYBLUE;
    }
    else if (strcmp(obterQualidadeMusica(), "BOA") == 0)
    {
        corQualidade = GREEN;
    }
    else if (strcmp(obterQualidadeMusica(), "HYPE") == 0)
    {
        corQualidade = PURPLE;
    }
    else if (strcmp(obterQualidadeMusica(), "HIT") == 0)
    {
        corQualidade = GOLD;
    }

int larguraQualidade =
    MeasureText(textoQualidade, 36);

    DrawText(
        textoQualidade,

        (1280 - larguraQualidade) / 2,

        250,

        36,

        corQualidade
    );

const char* textoNome =
    "DIGITE O NOME DA MUSICA";

int larguraNome =
    MeasureText(textoNome, 30);

    DrawText(
        textoNome,

        (1280 - larguraNome) / 2,

        325,

        30,

        WHITE
    );

    DrawRectangleRounded(
        (Rectangle){340, 380, 600, 65},
        0.15f,
        10,
        Fade(BLACK, 0.5f)
    );

    DrawRectangleRoundedLines(
        (Rectangle){340, 370, 600, 65},
        0.15f,
        10,
        Fade(PINK, 0.8f)
    );

    DrawText(
        nomeMusica,
        365,
        388,
        32,
        WHITE
    );

    const char* textoConfirmar =
        "APERTE ENTER PARA CONFIRMAR";

    int larguraConfirmar =
        MeasureText(textoConfirmar, 22);

    DrawText(
        textoConfirmar,

        (1280 - larguraConfirmar) / 2,

        470,

        22,

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