#include "raylib.h"

#include <stdlib.h>
#include <time.h>

#include "core/jogo.h"
#include "core/telas.h"
#include "telas/tela_inicio.h"
#include "telas/tela_save.h"
#include "telas/tela_criar_mc.h"
#include "telas/tela_menu.h"
#include "telas/tela_acoes.h"
#include "telas/tela_minigame.h"
#include "core/assets.h"
#define LARGURA_TELA 1280
#define ALTURA_TELA 720

static int semanaAtual = 1;

static TelaAtual telaAtual;

static int famaAtual = 0;

static int minigameAtual;

static bool acaoRealizadaNaSemana = false;

bool acaoDaSemanaJaFoiFeita(void)
{
    return acaoRealizadaNaSemana;
}

void marcarAcaoDaSemanaComoFeita(void)
{
    acaoRealizadaNaSemana = true;
}

void definirMinigameAtual(int minigame)
{
    minigameAtual = minigame;
}

int obterMinigameAtual(void)
{
    return minigameAtual;
}

int obterSemanaAtual(void)
{
    return semanaAtual;
}

void avancarSemana(void)
{
    semanaAtual++;

    acaoRealizadaNaSemana = false;
}

int obterFamaAtual(void)
{
    return famaAtual;
}

void aumentarFama(int quantidade)
{
    famaAtual += quantidade;
}

void iniciarJogo(void)
{
    
    srand(time(NULL));

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Vida de MC");
    carregarAssetsGlobais();
    SetTargetFPS(60);

    telaAtual = TELA_INICIO;
}

void executarJogo(void)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(BLACK);

            switch (telaAtual)
            {
                case TELA_INICIO:

                    atualizarTelaInicio();
                    desenharTelaInicio();

                    break;

                case TELA_SAVE:

                    atualizarTelaSave();
                    desenharTelaSave();

                    break;

                case TELA_CRIAR_MC:

                    atualizarTelaCriarMc();
                    desenharTelaCriarMc();

                    break;

                case TELA_MENU:

                    atualizarTelaMenu();
                    desenharTelaMenu();

                    break;

                case TELA_ACOES:

                    atualizarTelaAcoes();
                    desenharTelaAcoes();

                    break;

                case TELA_MINIGAME:

                    atualizarTelaMinigame();
                    desenharTelaMinigame();

                    break;
            }

        EndDrawing();
    }
}

void finalizarJogo(void)
{
    CloseWindow();
}

void mudarTela(int novaTela)
{
    telaAtual = novaTela;
}