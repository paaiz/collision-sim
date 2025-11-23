#include "../include/UpdateBall.hpp"

#include <raylib.h>
#include <cmath>

static const float GRAVITY = 600.0f;
static const float BOUNCE_DAMPING = 0.6f;

void UpdateBall::Update(GameState &state)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Ball ball;
        ball.position = GetMousePosition();
        ball.velocity = {0, 0};
        ball.radius = 20.0f;
        ball.color = RED;

        state.balls.push_back(ball);
    }

    LogicBall(state);

    CheckWallCollisions(state.balls);
}

void UpdateBall::LogicBall(GameState &state)
{
    float dt = GetFrameTime();

    for (auto &ball : state.balls)
    {
        ball.velocity.y += GRAVITY * dt;

        ball.position.x += ball.velocity.x * dt;
        ball.position.y += ball.velocity.y * dt;
    }
}

void UpdateBall::CheckWallCollisions(std::vector<Ball> &balls)
{
    const float bounceFactor = BOUNCE_DAMPING;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    for (auto &b : balls)
    {
        // Dinding Kiri
        if (b.position.x < b.radius)
        {
            b.position.x = b.radius;
            b.velocity.x *= -bounceFactor;
        }

        // Dinding Kanan
        if (b.position.x > screenW - b.radius)
        {
            b.position.x = screenW - b.radius;
            b.velocity.x *= -bounceFactor;
        }

        // Atap
        if (b.position.y < b.radius)
        {
            b.position.y = b.radius;
            b.velocity.y *= -bounceFactor;
        }

        // Lantai
        if (b.position.y > screenH - b.radius)
        {
            b.position.y = screenH - b.radius;
            b.velocity.y *= -bounceFactor;
        }
    }
}
