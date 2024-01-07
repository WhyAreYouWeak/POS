#include "Paddle.h"

Paddle::Paddle(float x, float y, int width, int height) : rectangle({x, y, static_cast<float>(width), static_cast<float>(height)}) {}

Paddle::~Paddle() = default;

void Paddle::moveY(int screenHeight, float distance) {
    rectangle.y += distance;

    if (rectangle.y < 0) {
        rectangle.y = 0;
    } else if (rectangle.y + rectangle.height > screenHeight) {
        rectangle.y = screenHeight - rectangle.height;
    }
}

float Paddle::getPositionY() {
    return rectangle.y;
}

float Paddle::getHeight() {
    return rectangle.height;
}

Rectangle Paddle::getRectangle() {
    return rectangle;
}

void Paddle::setPositionY(float y) {
    rectangle.y = y;
}