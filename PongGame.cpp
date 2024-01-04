#include <string>
#include "PongGame.h"

PongGame::PongGame(int width, int height, char* title)
        : screenWidth(width), screenHeight(height), windowTitle(title),
          ball(width / 2, height / 2, 20),
          player1Paddle(20, height / 2 - 100 / 2, 20, 100),
          player2Paddle(width - 20 - 20, height / 2 - 100 / 2, 20, 100),
          player1Score(0), player2Score(0) {
    InitWindow(screenWidth, screenHeight, windowTitle);
    SetTargetFPS(60);
}

PongGame::~PongGame() {
    CloseWindow();
}

void PongGame::run() {
    initializePositions();

    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void PongGame::initializePositions() {
    ball.setPosition(screenWidth / 2, screenHeight / 2);
    player1Paddle.setPositionY(screenHeight / 2 - 100 / 2);
    player2Paddle.setPositionY(screenHeight / 2 - 100 / 2);
}

void PongGame::update() {
    ball.move();
    ball.bounceOnWall(screenHeight);
    ball.bounceOnPaddle(player1Paddle);
    ball.bounceOnPaddle(player2Paddle);

    //
    if (IsKeyDown(KEY_UP)) {
        player2Paddle.moveY(screenHeight, -5.0);
    }
    if (IsKeyDown(KEY_DOWN)) {
        player2Paddle.moveY(screenHeight, 5.0);
    }

    if (ball.getPositionY() < player1Paddle.getPositionY() + player1Paddle.getHeight() / 2) {
        player1Paddle.moveY(screenHeight, -5.0);
    } else {
        player1Paddle.moveY(screenHeight, 5.0);
    }

    if (ball.getPositionX() <= 0) {
        player2Score++;
        initializePositions();
    } else if (ball.getPositionX() >= screenWidth) {
        player1Score++;
        initializePositions();
    }
}

void PongGame::draw() {
    BeginDrawing();

    Color backgroundColor = {41, 57, 76, 255};
    ClearBackground(backgroundColor);

    DrawRectangleRec(player1Paddle.getRectangle(), RED);
    DrawRectangleLinesEx(player1Paddle.getRectangle(), 2, BLACK);
    DrawRectangleRec(player2Paddle.getRectangle(), BLUE);
    DrawRectangleLinesEx(player2Paddle.getRectangle(), 2, BLACK);
    DrawCircleV({ball.getPositionX(), ball.getPositionY()}, ball.getSize() / 2, ball.getColor());
    DrawCircleLines(ball.getPositionX(), ball.getPositionY(), ball.getSize() / 2, BLACK);


    DrawLine(screenWidth / 2, screenHeight, screenWidth / 2, 0, BLACK);

    int textFontSize = 20;
    int scoreFontSize = 40;

    DrawText("Player 1", screenWidth / 4 - MeasureText("Player 1", textFontSize) - 20, 20, textFontSize, WHITE);
    DrawText(std::to_string(player1Score).c_str(), screenWidth / 4, 20, scoreFontSize, RED);

    DrawText("Player 2", 3 * screenWidth / 4 + 40, 20, textFontSize, WHITE);
    DrawText(std::to_string(player2Score).c_str(), 3 * screenWidth / 4, 20, scoreFontSize, BLUE);

    EndDrawing();
}