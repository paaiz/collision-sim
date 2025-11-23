#include "../include/UpdateBall.hpp"

#include <raylib.h>
#include <cmath>

// static const float GRAVITY = 600.0f; gperlu gravitasi lg
static const float BALL_BOUNCE_REDUCTION = 1.0f;

float MIN_SPEED = 50.0f;
float MAX_SPEED = 300.0f;

void UpdateBall::Update(GameState &state)
{

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        float speed = GetRandomValue(MIN_SPEED, MAX_SPEED);
        float angle = GetRandomValue(0, 360) * DEG2RAD;

        Ball ball;
        ball.position = GetMousePosition();
        ball.velocity = {cosf(angle) * speed, sinf(angle) * speed};
        ball.radius = 5.0f;
        ball.color = ColorFromHSV(GetRandomValue(0, 360), 0.75f, 0.95f);

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
        // ball.velocity.y += GRAVITY * dt;

        ball.position.x += ball.velocity.x * dt;
        ball.position.y += ball.velocity.y * dt;
    }
}

void UpdateBall::CheckWallCollisions(std::vector<Ball> &balls)
{
    const float bounceFactor = BALL_BOUNCE_REDUCTION;

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
