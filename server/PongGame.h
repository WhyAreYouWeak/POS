#pragma once
#include "Ball.h"
#include "Paddle.h"
#include <string>

class PongGame {
private:
    int screenWidth;
    int screenHeight;
    Ball ball;
    Paddle player1Paddle;
    Paddle player2Paddle;
    int player1Score;
    int player2Score;
    TempStruct tempStruct;
    std::mutex mutex;

public:
    ~PongGame();
    PongGame(int width, int height);

    void run();
    void initializePositions();
    void update();
    void updatePaddle(int playerNumber, int direction);
    std::string getCoords();
    std::string getScore();
};