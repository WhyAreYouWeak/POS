#pragma once
#include "raylib.h"
#include "Paddle.h"

class Ball {
private:
    Vector2 position;
    Vector2 speed;
    int size;
    Color color = BLACK;

public:
    Ball(float startPositionX, float startPositionY, int ballSize);
    ~Ball();

    void move();
    void bounceOnWall(int screenHeight);
    void bounceOnPaddle(Paddle& paddle);

    float getPositionX();
    float getPositionY();
    int getSize();
    Color getColor();
    void setPosition(float x, float y);
    void setColor();
};