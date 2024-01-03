#include <complex>
#include "Ball.cpp"
class PongGame {
private:
    Ball ball;
    Paddle paddleLeft;
    Paddle paddleRight;
    int screenWidth;
    int screenHeight;
public:
    PongGame(int width, int height): screenWidth(width), screenHeight(height),
              ball( screenWidth / 2, screenHeight / 2 , 20),
              paddleLeft(20, screenHeight / 2 - 100 / 2, 20, 100),
              paddleRight(screenWidth , screenHeight / 2 - 100 / 2, 20, 100 ) {}


    void initialize() {
    }

    void update() {
        ball.move();
        ball.bounceOnWall(screenHeight);
        ball.bounceOnPaddle(paddleLeft);
        ball.bounceOnPaddle(paddleRight);

        if (IsKeyDown(KEY_UP)) {
            paddleLeft.moveUp(screenHeight, 5);
        }
        if (IsKeyDown(KEY_DOWN)) {
            paddleRight.moveDown(screenHeight, 5);
        }

        if (this->ball.getPositionY() < paddleLeft.getPossitionY() + paddleLeft.getHeight() / 2) {
            paddleLeft.setPositionY(paddleLeft.getPossitionY() - ( 5 + std::abs(paddleLeft.getPossitionY() + paddleLeft.getHeight() / 2 - this->ball.getPositionY()) * 0.02));
        } else {
            paddleLeft.setPositionY(paddleLeft.getPossitionY() + ( 5 + std::abs(paddleLeft.getPossitionY() + paddleLeft.getHeight() / 2 - this->ball.getPositionY()) * 0.02));
        }

        if (this->ball.getPositionX() <= 0 || this->ball.getPositionX() >= screenWidth) {
            initialize();
        }
    }

    void draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(paddleLeft.getRectangle(), RED);
        DrawRectangleRec(paddleRight.getRectangle(), BLUE);
        DrawCircleV({this->ball.getPositionX(), this->ball.getPositionY()}, this->ball.getSize() / 2, GREEN);

        for (int i = 0; i < screenHeight; i += 20) {
            DrawRectangle(screenWidth / 2 - 1, i, 2, 10, BLACK);
        }
        EndDrawing();
    }
};