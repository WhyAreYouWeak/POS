#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>
#include "PongGame.h"
#include <stdio.h>
#include <cmath>
#include <unistd.h>

PongGame::PongGame(int width, int height)
        : screenWidth(width), screenHeight(height),
          ball(width / 2, height / 2, 20),
          player1Paddle(20, height / 2 - 100 / 2, 20, 100),
          player2Paddle(width - 20 - 20, height / 2 - 100 / 2, 20, 100),
          player1Score(0), player2Score(0){}

PongGame::~PongGame() {
}

void PongGame::run() {
    initializePositions();

    while (true) {
        update();

        if (player1Score == 5 || player2Score == 5) {

            //std::cout << "*********************************************************************************************" << std::endl;
            std::cout << "Game has ended!" << std::endl;
            std::cout << "Player 1 finished the game with score: " << player1Score << std::endl;
            std::cout << "Player 2 finished the game with score: " << player2Score << std::endl;
            break;
        }
    }
}

void PongGame::initializePositions() {
    mutex.lock();
    ball.setPosition(screenWidth / 2, screenHeight / 2);
    player1Paddle.setPositionY(screenHeight / 2 - 100 / 2);
    player2Paddle.setPositionY(screenHeight / 2 - 100 / 2);
    mutex.unlock();
}

void PongGame::update() {
    usleep(25000); // 25 ms
    mutex.lock();
    ball.move();
    ball.bounceOnWall(screenHeight);
    ball.bounceOnPaddle(player1Paddle);
    ball.bounceOnPaddle(player2Paddle);
    mutex.unlock();

    if (ball.getPositionX() <= 0) {
        mutex.lock();
        player2Score++;
        mutex.unlock();

        std::cout << "Player 2 scored!" << std::endl;
        initializePositions();
    } else if (ball.getPositionX() >= screenWidth) {
        mutex.lock();
        player1Score++;
        mutex.unlock();

        std::cout << "Player 1 scored!" << std::endl;
        initializePositions();
    }
}

void PongGame::updatePaddle(int playerNumber, int direction) {
    mutex.lock();
    if (playerNumber == 1) {
        player1Paddle.moveY(screenHeight, 5.0 * direction);
    } else if (playerNumber == 2){
        player2Paddle.moveY(screenHeight, 5.0 * direction);
    }
    mutex.unlock();
}

std::string PongGame::getCoords() {
    return std::to_string(static_cast<int>(player1Paddle.getPositionY())) + ","
           + std::to_string(static_cast<int>(player2Paddle.getPositionY())) + ","
           + std::to_string(static_cast<int>(std::round(ball.getPositionX()))) + ","
           + std::to_string(static_cast<int>(std::round(ball.getPositionY()))) + "," + "\0";
}

std::string PongGame::getScore() {
    return std::to_string(static_cast<int>(player1Score)) + ","
           + std::to_string(static_cast<int>(player2Score)) + "\0";
}
