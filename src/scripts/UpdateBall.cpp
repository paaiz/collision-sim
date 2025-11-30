#include "../include/UpdateBall.hpp"

#include <raylib.h>
#include <cmath>

// static const float GRAVITY = 600.0f; gperlu gravitasi lg
static const float BALL_BOUNCE_REDUCTION = 1.0f;

float MIN_SPEED = 150.0f;
float MAX_SPEED = 400.0f;

float RADIUS_BOLA = 5.0f;

float spawnTimer = 0.0f;
float spawnDelay = 0.1f;

bool SHOW_QTREE_GRID = true;
bool TOGGLE_QTREE = false;

void UpdateBall::Update(GameState &state)
{
    int SCREEN_HEIGHT = GetScreenHeight();
    int SCREEN_WIDTH = GetScreenWidth();

    float dt = GetFrameTime();
    spawnTimer -= dt;

    const char *resetText = "Press 'R' to reset balls";
    int resetTextWidth = MeasureText(resetText, 20);

    DrawText(resetText, (SCREEN_WIDTH - resetTextWidth) - 10, 10, 20, WHITE);
    if (IsKeyPressed(KEY_R))
    {
        state.balls.clear();
    }

    const char *showQtreeGridText = "Press 'G' to toggle QTree grid";
    int showQtreeGridTextWidth = MeasureText(showQtreeGridText, 20);

    DrawText(showQtreeGridText, (SCREEN_WIDTH - showQtreeGridTextWidth) - 10, 40, 20, WHITE);
    if (IsKeyPressed(KEY_G))
    {
        SHOW_QTREE_GRID = !SHOW_QTREE_GRID;
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && spawnTimer <= 0.0f)
    {
        spawnBall(state, GetMousePosition());
        spawnTimer = spawnDelay;
    }

    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON) && spawnTimer <= 0.0f)
    {
        for (int i = 0; i < 3; i++)
        {
            spawnBall(state, GetMousePosition());
            spawnTimer = spawnDelay * 0.3f;
        }
    }

    LogicBall(state);

    // Implement Qtree or Brute Force ketika bola banyak sekali-li-li-li
    const int BALL_LIMIT = 500; // ini udah ga kepake. karena udah ada toggle manual. Lebih jelas perbandingannya wakowkaowakowa

    const char *toggleQtreeText = "Press 'B' to switch collision algorithm";
    int toggleQtreeTextWidth = MeasureText(toggleQtreeText, 20);

    DrawText(toggleQtreeText, (SCREEN_WIDTH - toggleQtreeTextWidth) - 10, 70, 20, WHITE);
    if (IsKeyPressed(KEY_B))
    {
        TOGGLE_QTREE = !TOGGLE_QTREE;
    }

    if (!TOGGLE_QTREE)
    {
        DrawText("Using Brute Force Algorithm!", 10, 70, 20, RED);
        bruteForceCollision(state.balls);
    }
    else
    {
        DrawText("Using Quadtree Algorithm!", 10, 70, 20, GREEN);
        quadtreeCollision(state.balls);
    }

    // if (state.balls.size() < BALL_LIMIT)
    // {
    //     DrawText("Using Brute Force Algorithm!", 10, 70, 20, RED);
    //     bruteForceCollision(state.balls);
    // }
    // else
    // {
    //     DrawText(TextFormat("Ball exceeded limit (%d). Quadtree enabled!", BALL_LIMIT), 10, 70, 20, GREEN);
    //     quadtreeCollision(state.balls);
    // }

    CheckWallCollisions(state.balls);
}

void UpdateBall::spawnBall(GameState &state, Vector2 position)
{
    float speed = GetRandomValue(MIN_SPEED, MAX_SPEED);
    float angle = GetRandomValue(0, 360) * DEG2RAD;

    Ball ball;
    ball.position = position;
    ball.velocity = {cosf(angle) * speed, sinf(angle) * speed};
    ball.radius = RADIUS_BOLA;
    ball.color = ColorFromHSV(GetRandomValue(0, 360), 0.75f, 0.95f);

    state.balls.push_back(ball);
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

void UpdateBall::resolveCollision(Ball &bola1, Ball &bola2)
{
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

        // Overlap issue
        float overlap = jarakMinimumBola - jarak;
        float geserBola = overlap * 0.8f;

        bola1.position.x -= unitVektorX * geserBola;
        bola1.position.y -= unitVektorY * geserBola;

        bola2.position.x += unitVektorX * geserBola;
        bola2.position.y += unitVektorY * geserBola;
    }
}

void UpdateBall::bruteForceCollision(std::vector<Ball> &balls)
{
    size_t bola = balls.size();

    for (size_t i = 0; i < bola; i++)
    {
        for (size_t j = i + 1; j < bola; j++)
        {
            resolveCollision(balls[i], balls[j]);
        }
    }
}

void UpdateBall::quadtreeCollision(std::vector<Ball> &balls)
{
    Rectangle boundary = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    QNode qtree(boundary, 6);

    for (auto &b : balls)
        qtree.insert(&b);

    if (SHOW_QTREE_GRID)
        qtree.draw();

    // Sama, cek collision.
    for (size_t i = 0; i < balls.size(); i++)
    {
        Ball &bola1 = balls[i];

        Rectangle range = {
            bola1.position.x - bola1.radius * 2,
            bola1.position.y - bola1.radius * 2,
            bola1.radius * 4,
            bola1.radius * 4};

        std::vector<Ball *> candidates;
        qtree.query(range, candidates);

        for (Ball *bola2 : candidates)
        {
            if (&bola1 == bola2)
                continue;

            float jarakMinimumBola = bola1.radius + bola2->radius;

            float dx = bola2->position.x - bola1.position.x;
            float dy = bola2->position.y - bola1.position.y;

            float jarak = dx * dx + dy * dy;

            if (jarak < jarakMinimumBola * jarakMinimumBola && jarak > 0.0f)
            {
                resolveCollision(bola1, *bola2);
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
