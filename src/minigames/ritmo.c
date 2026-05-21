#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "minigames/ritmo.h"

static float animacaoEntrada = 0;

static Texture2D fundo;
static Font fonteRitmo;

static bool assetsCarregados = false;

static char letras[] = {
    'A',
    'S',
    'K',
    'L'
};

static char letraAtual;

static Vector2 posicaoAtual;

static float tempoRestante;

static int tentativaAtual;

static int maxTentativas = 15;

static int pontuacao;

static bool finalizado = false;

static char feedback[20] = "";

static char qualidadeFinal[20] = "";

static float escalaCirculo = 120;

static float screenShake = 0;

void carregarAssetsRitmo(void)
{
    fonteRitmo =
    LoadFontEx(
        "assets/fonts/orbitron-Bold.ttf",
        80,
        0,
        0
    );
    if (assetsCarregados)
    {
        return;
    }

    fundo = LoadTexture(
        "assets/background_ritmo.png"
    );

    assetsCarregados = true;
}

void gerarNovaLetra(void)
{
    letraAtual = letras[rand() % 4];

    posicaoAtual.x =
        200 + rand() % 800;

    posicaoAtual.y =
        150 + rand() % 350;

    tempoRestante = 1.2f;
    escalaCirculo = 120;
    animacaoEntrada = 0;
}

void iniciarMinigameRitmo(void)
{
    carregarAssetsRitmo();

    tentativaAtual = 0;

    pontuacao = 0;

    finalizado = false;

    strcpy(feedback, "");

    gerarNovaLetra();
}

void atualizarMinigameRitmo(void)
{
        animacaoEntrada +=
        5 * GetFrameTime();

    if (animacaoEntrada > 1)
    {
        animacaoEntrada = 1;
    }
        escalaCirculo -= 120 * GetFrameTime();

    if (escalaCirculo < 60)
    {
        escalaCirculo = 60;
    }
    if (finalizado)
    {
        return;
    }

    tempoRestante -= GetFrameTime();

    if (tempoRestante <= 0)
    {
        strcpy(feedback, "MISS");

        tentativaAtual++;

        gerarNovaLetra();

        return;
    }

    int tecla = GetKeyPressed();

    if (tecla > 0)
    {
        if (tecla == letraAtual)
        {
            if (tempoRestante >= 0.65f)
            {
                pontuacao += 100;

                strcpy(feedback, "PERFECT!");
                screenShake = 10;
            }
            else if (tempoRestante >= 0.35f)
            {
                pontuacao += 70;

                strcpy(feedback, "NICE!");
            }
            else
            {
                pontuacao += 40;

                strcpy(feedback, "OK!");
            }
        }
        else
        {
            strcpy(feedback, "MISS");
        }

        tentativaAtual++;

        gerarNovaLetra();
    }

    if (tentativaAtual >= maxTentativas)
    {
        finalizado = true;

        if (pontuacao <= 300)
        {
            strcpy(qualidadeFinal, "RUIM");
        }
        else if (pontuacao <= 700)
        {
            strcpy(qualidadeFinal, "MEDIA");
        }
        else if (pontuacao <= 1000)
        {
            strcpy(qualidadeFinal, "BOA");
        }
        else if (pontuacao <= 1300)
        {
            strcpy(qualidadeFinal, "HYPE");
        }
        else
        {
            strcpy(qualidadeFinal, "HIT");
        }
    }
}

void desenharMinigameRitmo(void)
{
    DrawTexturePro(
        fundo,
        (Rectangle){
            0,
            0,
            fundo.width,
            fundo.height
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

    DrawText(
        "CRIE SUA MUSICA",
        420,
        40,
        45,
        WHITE
    );

    float offsetX = 0;
    float offsetY = 0;

    if (screenShake > 0)
    {
        offsetX = GetRandomValue(-5, 5);

        offsetY = GetRandomValue(-5, 5);

        screenShake -= 30 * GetFrameTime();
    }

    char letra[2] = {
        letraAtual,
        '\0'
    };

    DrawCircle(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        90,
        Fade(PINK, 0.08f)
    );

    DrawCircle(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        80,
        Fade(PINK, 0.12f)
    );

    DrawCircle(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        70,
        Fade(GRAY, 0.25f)
    );

    DrawCircleLines(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        escalaCirculo,
        Fade(WHITE, 0.7f)
    );

    DrawCircle(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        58 * animacaoEntrada,
        ColorAlpha(PINK, 0.8f)
    );

    DrawCircleLines(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        58 * animacaoEntrada,
        WHITE
    );

    DrawCircle(
        posicaoAtual.x + offsetX,
        posicaoAtual.y + offsetY,
        12,
        Fade(WHITE, 0.25f)
    );

    DrawTextEx(
        fonteRitmo,

        letra,

        (Vector2){
            posicaoAtual.x - 18 + offsetX,
            posicaoAtual.y - 35 + offsetY
        },

        60,

        2,

        WHITE
    );

    DrawText(
        feedback,
        540,
        620,
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
        35,
        WHITE
    );

    char textoTentativas[50];

    sprintf(
        textoTentativas,
        "LETRAS: %d/%d",
        tentativaAtual,
        maxTentativas
    );

    DrawText(
        textoTentativas,
        900,
        40,
        35,
        WHITE
    );
}

bool minigameRitmoFinalizado(void)
{
    return finalizado;
}

int obterPontuacaoRitmo(void)
{
    return pontuacao;
}

char* obterQualidadeMusica(void)
{
    return qualidadeFinal;
}