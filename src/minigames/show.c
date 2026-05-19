#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#include "minigames/show.h"

static float notaX;

static float velocidadeNota;

static int pontuacao;

static int tentativas;

static int maxTentativas = 15;

static bool finalizado = false;

static const float zonaPerfectX = 640;

static const float zonaLargura = 80;

static char resultadoAtual[20] = "";

void iniciarMinigameShow(void)
{
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

    /*
        DIFICULDADE DINÂMICA
    */

    if (tentativas >= 7 && tentativas < 11)
    {
        velocidadeNota = 10.0f;
    }
    else if (tentativas >= 11 && tentativas < 14)
    {
        velocidadeNota = 12.0f;
    }
    else if (tentativas >= 14)
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
    DrawText(
        "APERTE ESPACO NO TEMPO CERTO",
        320,
        120,
        35,
        WHITE
    );

    DrawRectangle(
        200,
        350,
        880,
        10,
        GRAY
    );

    DrawRectangle(
        zonaPerfectX - (zonaLargura / 2),
        320,
        zonaLargura,
        70,
        GREEN
    );

    DrawCircle(
        notaX,
        355,
        15,
        PINK
    );

    DrawText(
        resultadoAtual,
        560,
        450,
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

    /*
        MOSTRAR VELOCIDADE ATUAL
    */

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