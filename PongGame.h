#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "raylib.h"
#include "sockets/my_socket.h"

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
    PongGame(int width, int height, const char* title);
    ~PongGame();

    void run();
    void initializePositions();
    void update();
    void draw();
};