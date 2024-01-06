#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "raylib.h"
#include "sockets/my_socket.h"
#include "SocketReceive.h"
#include "Objects.h"

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
    MySocket* socket;
    TempStruct& tempStruct;

public:
    PongGame(int width, int height, const char* title, MySocket* socket, TempStruct& tempStruct);
    ~PongGame();
    std::mutex gameMutex;

    void run();
    void initializePositions();
    void update();
    //void updateData(MessageBuffer* messageBuffer);
    void updateData(int player1PaddleY, int player2PaddleY, int ballX, int ballY);
    void draw();
};