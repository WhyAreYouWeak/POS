#include <string>
#include <iostream>
#include "PongGame.h"
#include "Objects.h"
#include <thread>

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
/*
    InitWindow(screenWidth, screenHeight, "End screen");
    SetTargetFPS(60);
    DrawText("NDSAJNDSAJKDSANKJ", screenWidth / 2, screenHeight / 2, 40, RED);
    while (!WindowShouldClose() && !IsKeyDown(KEY_SPACE)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    CloseWindow();
    */
}

void PongGame::initializePositions() {
    ball.setPosition(screenWidth / 2, screenHeight / 2);
    player1Paddle.setPositionY(screenHeight / 2 - 100 / 2);
    player2Paddle.setPositionY(screenHeight / 2 - 100 / 2);
}

void PongGame::update() {
    ball.setPosition(tempStruct.ballX, tempStruct.ballY);
    player1Paddle.setPositionY(tempStruct.player1PaddleY);
    player2Paddle.setPositionY(tempStruct.player2PaddleY);
    player1Score = tempStruct.playerScore1;
    player2Score = tempStruct.playerScore2;
    /*
    ball.move();
    ball.bounceOnWall(screenHeight);
    ball.bounceOnPaddle(player1Paddle);
    ball.bounceOnPaddle(player2Paddle);
     */

    if (IsKeyDown(KEY_UP)) {
      //  std::cout << "Sending up" << std::endl;
        socket->sendData("up\0");
       // player2Paddle.moveY(screenHeight, -5.0);
    }
    if (IsKeyDown(KEY_DOWN)) {
      //  std::cout << "Sending down" << std::endl;
        socket->sendData("down\0");
      //  player2Paddle.moveY(screenHeight, 5.0);
    }

    if (ball.getPositionY() < player1Paddle.getPositionY() + player1Paddle.getHeight() / 2) {
        player1Paddle.moveY(screenHeight, -5.0);
    } else {
        player1Paddle.moveY(screenHeight, 5.0);
    }
/*
    if (ball.getPositionX() <= 0) {
        player2Score++;
        initializePositions();
    } else if (ball.getPositionX() >= screenWidth) {
        player1Score++;
        initializePositions();
    }
    */
}
/*
void updateData(MessageBuffer* messageBuffer) {
    // komunikacia zo servera -> mutex lock a unlock
}
*/
/*
void PongGame::updateData(int player1PaddleY, int player2PaddleY, int ballX, int ballY) {
    player1Paddle.setPositionY(player1PaddleY);
    player2Paddle.setPositionY(player2PaddleY);
    ball.setPosition(ballX, ballY);

    std::cout << "player1PaddleY: " << player1PaddleY << std::endl;
    std::cout << "player2PaddleY: " << player2PaddleY << std::endl;
    std::cout << "ballX: " << ballX << std::endl;
    std::cout << "ballY: " << ballY << std::endl;
}
*/
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
