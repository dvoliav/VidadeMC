#include "raylib.h"

#include "core/jogo.h"
#include "core/telas.h"
#include "telas/tela_inicio.h"
#include "telas/tela_save.h"
#include "telas/tela_criar_mc.h"
#include "telas/tela_menu.h"

#define LARGURA_TELA 1280
#define ALTURA_TELA 720
static int semanaAtual = 1;
static TelaAtual telaAtual;
static int famaAtual = 0;


int obterSemanaAtual(void)
{
    return semanaAtual;
}

void avancarSemana(void)
{
    semanaAtual++;
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
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Vida de MC");

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