#pragma once
#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"

class PongGame {
private:
    int screenWidth;
    int screenHeight;
    const char* windowTitle;
    Ball ball;
    Paddle player1Paddle;
    Paddle player2Paddle;
    int player1Score;
    int player2Score;

public:
    PongGame(int width, int height, char* title);
    ~PongGame();

    void run();
    void initializePositions();
    void update();
    void draw();
};