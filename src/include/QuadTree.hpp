#pragma once
#include <vector>
#include <raylib.h>
#include "UpdateBall.hpp"

struct QNode
{
    Rectangle batasan;
    int kapasitas;
    bool divided;

    std::vector<Ball *> balls;

    QNode *kiriAtas;
    QNode *kananAtas;
    QNode *kiriBawah;
    QNode *kananBawah;

    QNode(Rectangle boundary, int kapasitas)
        : batasan(boundary), kapasitas(kapasitas), divided(false),
          kiriAtas(nullptr), kananAtas(nullptr), kiriBawah(nullptr), kananBawah(nullptr) {}

    ~QNode()
    {
        delete kiriAtas;
        delete kananAtas;
        delete kiriBawah;
        delete kananBawah;
    }

    void draw(Color color = Fade(WHITE, 0.3f))
    {
        DrawRectangleLines(batasan.x, batasan.y, batasan.width, batasan.height, color);

        if (divided)
        {
            kiriAtas->draw(color);
            kananAtas->draw(color);
            kiriBawah->draw(color);
            kananBawah->draw(color);
        }
    }

    bool insert(Ball *ball)
    {
        if (!CheckCollisionPointRec(ball->position, batasan))
            return false;

        if (balls.size() < kapasitas)
        {
            balls.push_back(ball);
            return true;
        }

        if (!divided)
            subdivide();

        return kiriAtas->insert(ball) || kananAtas->insert(ball) || kiriBawah->insert(ball) || kananBawah->insert(ball);
    }

    void subdivide()
    {
        float x = batasan.x;
        float y = batasan.y;
        float w = batasan.width / 2;
        float h = batasan.height / 2;

        kiriAtas = new QNode({x, y, w, h}, kapasitas);
        kananAtas = new QNode({x + w, y, w, h}, kapasitas);
        kiriBawah = new QNode({x, y + h, w, h}, kapasitas);
        kananBawah = new QNode({x + w, y + h, w, h}, kapasitas);

        divided = true;
    }

    void query(Rectangle range, std::vector<Ball *> &found)
    {
        if (!CheckCollisionRecs(batasan, range))
            return;

        for (Ball *o : balls)
        {
            if (CheckCollisionPointRec(o->position, range))
                found.push_back(o);
        }

        if (divided)
        {
            kiriAtas->query(range, found);
            kananAtas->query(range, found);
            kiriBawah->query(range, found);
            kananBawah->query(range, found);
        }
    }
};
