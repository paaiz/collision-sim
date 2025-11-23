#pragma once
#include <vector>
#include <raylib.h>

struct Ball
{
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

class GameState
{
public:
    std::vector<Ball> balls;
};
