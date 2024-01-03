#include "raylib.h"
class Paddle {
private:
    Rectangle rectangle;
public:
    Paddle(float x, float y, int width, int height) {
        this->rectangle = { x, y, static_cast<float>(width), static_cast<float>(height) };
    }

    void moveUp(int screenHeight, int speed) {
        if(rectangle.y > 0) {
            rectangle.y -= speed;
        }
    }

    void moveDown(int screenHeight, int speed) {
        if(rectangle.y < screenHeight - rectangle.height ) {
            rectangle.y += speed;
        }
    }
    Rectangle getRectangle() {
        return this->rectangle;
    }
    float getPossitionY() {
        return this->rectangle.y;
    };

    float getHeight() {
        return this->rectangle.height;
    }
    void setPositionY(float y) {
        this->rectangle.y = y;
    }
};