#pragma once
#include "GameState.hpp"

class UpdateBall
{
public:
    static void Update(GameState &state);
    static void LogicBall(GameState &state);
    static void CheckWallCollisions(std::vector<Ball> &balls);
    static void bruteForceCollision(std::vector<Ball> &balls);
};
