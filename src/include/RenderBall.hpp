#pragma once
#include "GameState.hpp"

class RenderBall
{
public:
    static void Draw(const GameState &state);
    static void DrawInformationTable(const GameState &state);
    static void DrawIfQtree(const GameState &state);
};
