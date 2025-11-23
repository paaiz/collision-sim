#include "../include/UpdateBall.hpp"
#include <raylib.h>

#include <cmath>

static const float GRAVITY = 0.0f;
static const float BOUNCE_DAMPING = 0.6f;

void UpdateBall::Update(GameState &state)
{
    float dt = GetFrameTime();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Ball b;
        b.position = GetMousePosition();
        b.velocity = {0, 0};
        b.radius = 20.0f;
        b.color = RED;

        state.balls.push_back(b);
    }

    for (auto &b : state.balls)
    {
        b.velocity.y += GRAVITY * dt;

        b.position.x += b.velocity.x * dt;
        b.position.y += b.velocity.y * dt;

        float floorY = GetScreenHeight() - b.radius;

        if (b.position.y > floorY)
        {
            b.position.y = floorY;

            b.velocity.y *= -BOUNCE_DAMPING;

            if (fabs(b.velocity.y) < 10.0f)
                b.velocity.y = 0;
        }
    }
}
