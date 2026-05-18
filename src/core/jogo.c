#include "raylib.h"

#include "core/jogo.h"
#include "core/telas.h"
#include "telas/tela_inicio.h"
#include "telas/tela_save.h"
#include "telas/tela_criar_mc.h"

#define LARGURA_TELA 1280
#define ALTURA_TELA 720

static TelaAtual telaAtual;


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

                case TELA_MENU:

                    ClearBackground((Color){20, 10, 30, 255});

                    DrawText(
                        "MENU PRINCIPAL",
                        420,
                        300,
                        50,
                        WHITE
                    );

                    break;

                case TELA_SAVE:

                    atualizarTelaSave();

                    desenharTelaSave();

                    break;

                case TELA_CRIAR_MC:
                    atualizarTelaCriarMc();
                    desenharTelaCriarMc();
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