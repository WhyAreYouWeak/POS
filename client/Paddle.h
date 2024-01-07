#pragma once
#include "raylib.h"

class Paddle {
private:
    Rectangle rectangle;

public:
    Paddle(float x, float y, int width, int height);
    ~Paddle();

    void moveY(int screenHeight, float distance);
    float getPositionY();
    float getHeight();
    void setPositionY(float y);
    Rectangle getRectangle();
};