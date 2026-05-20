#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "minigames/show.h"

static Texture2D fundoShow;

static Texture2D microfone;

static Texture2D nota1;
static Texture2D nota2;
static Texture2D nota3;

static float notaX;

static float velocidadeNota;

static int pontuacao;

static int tentativas;

static int maxTentativas = 15;

static bool finalizado = false;

static const float zonaPerfectX = 640;

static char resultadoAtual[20] = "";

static bool assetsCarregados = false;

void carregarAssetsShow(void)
{
    if (assetsCarregados)
    {
        return;
    }

    fundoShow =
        LoadTexture("assets/show/background_show.png");

    microfone =
        LoadTexture("assets/show/microfone.png");

    nota1 =
        LoadTexture("assets/show/nota1.png");

    nota2 =
        LoadTexture("assets/show/nota2.png");

    nota3 =
        LoadTexture("assets/show/nota3.png");

    assetsCarregados = true;
}

void iniciarMinigameShow(void)
{
    carregarAssetsShow();

    notaX = 0;

    velocidadeNota = 8.0f;

    pontuacao = 0;

    tentativas = 0;

    finalizado = false;

    strcpy(resultadoAtual, "");
}

void atualizarMinigameShow(void)
{
    if (finalizado)
    {
        return;
    }

    if (tentativas >= 5 && tentativas < 10)
    {
        velocidadeNota = 10.0f;
    }
    else if (tentativas >= 10 && tentativas < 13)
    {
        velocidadeNota = 12.0f;
    }
    else if (tentativas >= 13)
    {
        velocidadeNota = 14.0f;
    }
    else
    {
        velocidadeNota = 8.0f;
    }

    notaX += velocidadeNota;

    if (IsKeyPressed(KEY_SPACE))
    {
        float centroNota = notaX;

        float distancia =
            fabsf(centroNota - zonaPerfectX);

        if (distancia <= 15)
        {
            pontuacao += 100;

            strcpy(resultadoAtual, "PERFECT");
        }
        else if (distancia <= 40)
        {
            pontuacao += 50;

            strcpy(resultadoAtual, "OK");
        }
        else
        {
            strcpy(resultadoAtual, "MISS");
        }

        tentativas++;

        notaX = 0;
    }

    if (notaX > 1280)
    {
        strcpy(resultadoAtual, "MISS");

        tentativas++;

        notaX = 0;
    }

    if (tentativas >= maxTentativas)
    {
        finalizado = true;
    }
}

void desenharMinigameShow(void)
{
    DrawTexturePro(
        fundoShow,

        (Rectangle){0, 0, fundoShow.width, fundoShow.height},

        (Rectangle){0, 0, 1280, 720},

        (Vector2){0, 0},

        0.0f,

        WHITE
    );

    DrawText(
        "APERTE ESPACO NO TEMPO CERTO",
        320,
        100,
        35,
        WHITE
    );

    DrawRectangle(
        200,
        350,
        880,
        10,
        WHITE
    );

    DrawTextureEx(
        microfone,

        (Vector2){
            zonaPerfectX - 40,
            280
        },

        0.0f,

        0.15f,

        WHITE
    );

    Texture2D notaAtual;

    if (tentativas % 3 == 0)
    {
        notaAtual = nota1;
    }
    else if (tentativas % 3 == 1)
    {
        notaAtual = nota2;
    }
    else
    {
        notaAtual = nota3;
    }

    DrawTextureEx(
        notaAtual,

        (Vector2){
            notaX,
            310
        },

        0.0f,

        0.12f,

        WHITE
    );

    DrawText(
        resultadoAtual,
        560,
        470,
        40,
        WHITE
    );

    char textoPontos[50];

    sprintf(
        textoPontos,
        "PONTOS: %d",
        pontuacao
    );

    DrawText(
        textoPontos,
        40,
        40,
        30,
        WHITE
    );

    char textoTentativas[50];

    sprintf(
        textoTentativas,
        "BATIDAS: %d/%d",
        tentativas,
        maxTentativas
    );

    DrawText(
        textoTentativas,
        930,
        40,
        30,
        WHITE
    );

    char textoVelocidade[50];

    sprintf(
        textoVelocidade,
        "VELOCIDADE: %.0f",
        velocidadeNota
    );

    DrawText(
        textoVelocidade,
        500,
        40,
        30,
        WHITE
    );
}

bool minigameShowFinalizado(void)
{
    return finalizado;
}

int obterPontuacaoShow(void)
{
    return pontuacao;
}

float calcularFatorSorte(int porcentagem)
{
    float min;
    float max;

    if (porcentagem <= 50)
    {
        min = 0.0f;
        max = 0.5f;
    }
    else if (porcentagem <= 70)
    {
        min = 0.51f;
        max = 0.70f;
    }
    else
    {
        min = 0.71f;
        max = 1.0f;
    }

    float aleatorio =
        (float) rand() / RAND_MAX;

    return min + aleatorio * (max - min);
}