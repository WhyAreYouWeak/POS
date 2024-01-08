#include <string>
#include <iostream>
#include "PongGame.h"
#include "Objects.h"
#include <thread>
#include <mutex>

PongGame::PongGame(int width, int height, const char* title, MySocket* socket, TempStruct& tempStruct)
        : screenWidth(width), screenHeight(height), windowTitle(title),
          ball(width / 2, height / 2, 20),
          player1Paddle(20, height / 2 - 100 / 2, 20, 100),
          player2Paddle(width - 20 - 20, height / 2 - 100 / 2, 20, 100),
          player1Score(0), player2Score(0), socket(socket), tempStruct(tempStruct) {
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
    std::unique_lock<std::mutex> lock(tempStruct.mutex);
    ball.setPosition(tempStruct.ballX, tempStruct.ballY);
    player1Paddle.setPositionY(tempStruct.player1PaddleY);
    player2Paddle.setPositionY(tempStruct.player2PaddleY);
    player1Score = tempStruct.playerScore1;
    player2Score = tempStruct.playerScore2;
    lock.unlock();

    if (IsKeyDown(KEY_UP)) {
        socket->sendData("up\0");
    }
    if (IsKeyDown(KEY_DOWN)) {
        socket->sendData("down\0");
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

    if (player1Score == 5) {
        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 40, scoreFontSize, BLACK);
        DrawText("Player 1 WON", screenWidth / 2 - MeasureText("Player 1 WON", 40) / 2, screenHeight / 2, scoreFontSize, RED);
    } else if (player2Score == 5) {
        DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 40, scoreFontSize, BLACK);
        DrawText("Player 2 WON", screenWidth / 2 - MeasureText("Player 2 WON", 40) / 2, screenHeight / 2, scoreFontSize, BLUE);
    }

    EndDrawing();
}
