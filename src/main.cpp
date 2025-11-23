#include <iostream>
#include "raylib.h"

#include "./include/GameState.hpp"
#include "./include/UpdateBall.hpp"
#include "./include/RenderBall.hpp"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Collision Simulation Physics made by Paiz with ♥");

    SetTargetFPS(60);

    GameState game;

    while (!WindowShouldClose())
    {
        UpdateBall::Update(game);

        BeginDrawing();
        ClearBackground(BLACK);

        RenderBall::Draw(game);
        RenderBall::DrawInformationTable(game);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
