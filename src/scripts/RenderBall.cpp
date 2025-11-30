#include "../include/RenderBall.hpp"
#include <raylib.h>

void RenderBall::Draw(const GameState &state)
{
    for (const auto &b : state.balls)
    {
        DrawCircleV(b.position, b.radius, b.color);
    }
}

void RenderBall::DrawInformationTable(const GameState &state)
{
    DrawText(TextFormat("Total Bola: %d", state.balls.size()), 10, 10, 20, WHITE);
    DrawText(TextFormat("Total FPS: %d", GetFPS()), 10, 40, 20, WHITE);
}

void RenderBall::DrawIfQtree(const GameState &state)
{
    if (state.balls.size() >= 100)
    {
        DrawText("Ball exceeded limit (100). Quadtree enabled!", 10, 70, 20, GREEN);
    }
    else
    {
        DrawText("Ball below limit (100). Quadtree disabled!", 10, 70, 20, RED);
    }
}
