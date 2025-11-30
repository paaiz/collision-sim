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
    DrawText(TextFormat("Ball Count: %d", state.balls.size()), 10, 10, 20, WHITE);
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 20, WHITE);
}
