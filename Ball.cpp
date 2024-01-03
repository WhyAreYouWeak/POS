#include "raylib.h"
#include "Paddle.cpp"
class Ball {
private:
    Vector2 position;
    Vector2 speed;
    int size;
public:
    Ball(float startPositionX, float startPositionY, int ballSize) {
        this->size = ballSize;
        this->position = {startPositionX, startPositionY};
        this->speed = {5, 5};
    };
    void move() {
        position.x += speed.x;
        position.y += speed.y;
    }

    void bounceOnWall(int screenHeight) {
        if ((position.y >= screenHeight - size) || (position.y <= 0)) {
            speed.y *= -1;
        }
    }

    void bounceOnPaddle(Paddle paddle) {
        if (CheckCollisionCircleRec(position, size / 2, paddle.getRectangle())) {
            speed.x *= -1;
        }
    }

    float getPositionX() {
        return this->position.x;
    }
    float getPositionY() {
        return this->position.y;
    }
    int getSize() {
        return this->size;
    }
};