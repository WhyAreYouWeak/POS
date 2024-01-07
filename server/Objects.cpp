//
// Created by Patrik Kuric on 1/5/2024.
//
#include "Objects.h"
#include <cmath>

bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec)
{
    bool collision = false;

    float recCenterX = rec.x + rec.width/2.0f;
    float recCenterY = rec.y + rec.height/2.0f;

    float dx = fabsf(center.x - recCenterX);
    float dy = fabsf(center.y - recCenterY);

    if (dx > (rec.width/2.0f + radius)) { return false; }
    if (dy > (rec.height/2.0f + radius)) { return false; }

    if (dx <= (rec.width/2.0f)) { return true; }
    if (dy <= (rec.height/2.0f)) { return true; }

    float cornerDistanceSq = (dx - rec.width/2.0f)*(dx - rec.width/2.0f) +
                             (dy - rec.height/2.0f)*(dy - rec.height/2.0f);

    collision = (cornerDistanceSq <= (radius*radius));

    return collision;
}

int GetRandomValue(int min, int max)
{
    int value = 0;

    if (min > max)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

    value = (rand()%(abs(max - min) + 1) + min);
    return value;
}