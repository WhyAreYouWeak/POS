#include "Ball.h"

Ball::Ball(float startPositionX, float startPositionY, int ballSize)
        : position({startPositionX, startPositionY}), speed({7, 7}), size(ballSize) {}

Ball::~Ball() = default;

void Ball::move() {
    position.x += speed.x;
    position.y += speed.y;
}

void Ball::bounceOnWall(int screenHeight) {
    if ((position.y >= screenHeight - size) || (position.y <= 0)) {
        speed.y *= -1;
        setColor();
    }
}

void Ball::bounceOnPaddle(Paddle& paddle) {
    if (CheckCollisionCircleRec(position, size / 2, paddle.getRectangle())) {
        if (speed.x > 0) {
            position.x = paddle.getRectangle().x - size / 2;
        } else {
            position.x = paddle.getRectangle().x + paddle.getRectangle().width + size / 2;
        }

        speed.x *= -1;
        setColor();
    }
}

Color Ball::getColor() {
    return color;
}

float Ball::getPositionX() {
    return position.x;
}

float Ball::getPositionY() {
    return position.y;
}

int Ball::getSize() {
    return size;
}

void Ball::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void Ball::setColor() {
    color = (Color){static_cast<unsigned char>(GetRandomValue(0, 255)),
                    static_cast<unsigned char>(GetRandomValue(0, 255)),
                    static_cast<unsigned char>(GetRandomValue(0, 255)), 255};
}
