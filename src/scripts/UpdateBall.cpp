#include "../include/UpdateBall.hpp"

#include <raylib.h>
#include <cmath>

// static const float GRAVITY = 600.0f; gperlu gravitasi lg
static const float BALL_BOUNCE_REDUCTION = 1.0f;

float MIN_SPEED = 50.0f;
float MAX_SPEED = 300.0f;

float RADIUS_BOLA = 20.0f;

void UpdateBall::Update(GameState &state)
{

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        float speed = GetRandomValue(MIN_SPEED, MAX_SPEED);
        float angle = GetRandomValue(0, 360) * DEG2RAD;

        Ball ball;
        ball.position = GetMousePosition();
        ball.velocity = {cosf(angle) * speed, sinf(angle) * speed};
        ball.radius = RADIUS_BOLA;
        ball.color = ColorFromHSV(GetRandomValue(0, 360), 0.75f, 0.95f);

        state.balls.push_back(ball);
    }

    LogicBall(state);

    bruteForceCollision(state.balls);

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

void UpdateBall::bruteForceCollision(std::vector<Ball> &balls)
{
    size_t bola = balls.size();

    for (size_t i = 0; i < bola; i++)
    {
        for (size_t j = i + 1; j < bola; j++)
        {
            Ball &bola1 = balls[i];
            Ball &bola2 = balls[j];

            float jarakMinimumBola = bola1.radius + bola2.radius;

            float jarakXBola1dan2 = bola2.position.x - bola1.position.x;
            float jarakYBola1dan2 = bola2.position.y - bola1.position.y;

            float jarakKuadrat = jarakXBola1dan2 * jarakXBola1dan2 + jarakYBola1dan2 * jarakYBola1dan2;
            float jarak = sqrtf(jarakKuadrat);

            // Apakah bola nabrak?!?!?!?!? ril or fake
            if (jarak < jarakMinimumBola && jarak > 0.0f)
            {
                float unitVektorX = jarakXBola1dan2 / jarak;
                float unitVektorY = jarakYBola1dan2 / jarak;

                float skalarHasil = (bola1.velocity.x - bola2.velocity.x) * unitVektorX + (bola1.velocity.y - bola2.velocity.y) * unitVektorY;

                bola1.velocity.x -= skalarHasil * unitVektorX;
                bola1.velocity.y -= skalarHasil * unitVektorY;

                bola2.velocity.x += skalarHasil * unitVektorX;
                bola2.velocity.y += skalarHasil * unitVektorY;
            }
        }
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
