#include "../include/RenderBall.hpp"
#include <raylib.h>

void RenderBall::Draw(const GameState &state)
{
    for (const auto &b : state.balls)
    {
        DrawCircleV(b.position, b.radius, b.color);
    }
}
