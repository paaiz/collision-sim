#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "raylib");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Pak Hendra! Ihiyyyy", 200, 200, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
