#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "raylib.h"
#include "my_socket.h"
#include "SocketReceive.h"
#include "Objects.h"
#include <thread>

class PongGame {
private:
    int screenWidth;
    int screenHeight;
    int player1Score;
    int player2Score;
    const char* windowTitle;
    Ball ball;
    Paddle player1Paddle;
    Paddle player2Paddle;
    MySocket* socket;
    TempStruct& tempStruct;
    std::mutex mutex;

public:
    PongGame(int width, int height, const char* title, MySocket* socket, TempStruct& tempStruct);
    ~PongGame();
    std::mutex gameMutex;

    void run();
    void initializePositions();
    void update();
    void draw();
};