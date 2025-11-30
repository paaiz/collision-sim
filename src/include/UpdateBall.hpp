#pragma once
#include "GameState.hpp"
#include "QuadTree.hpp"

class UpdateBall
{
public:
    static void Update(GameState &state);
    static void LogicBall(GameState &state);
    static void spawnBall(GameState &state, Vector2 position);
    static void CheckWallCollisions(std::vector<Ball> &balls);
    static void bruteForceCollision(std::vector<Ball> &balls);
    static void quadtreeCollision(std::vector<Ball> &balls);
    static void resolveCollision(Ball &bola1, Ball &bola2);
};
