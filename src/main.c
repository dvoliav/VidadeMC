#include "raylib.h"

int main() {
    InitWindow(1280, 720, "Vida de MC");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("VIDA DE MC", 500, 300, 40, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}