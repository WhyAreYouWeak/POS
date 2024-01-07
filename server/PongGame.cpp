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
   // player1Score = 0;
  //  player2Score = 0;
    initializePositions();

    while (true) {
        update();

        if (gameScore.playerScore1 == 5 || gameScore.playerScore2 == 5) {

            //std::cout << "*********************************************************************************************" << std::endl;
            std::cout << "Game has ended!" << std::endl;
            std::cout << "Player 1 finished the game with score: " << gameScore.playerScore1 << std::endl;
            std::cout << "Player 2 finished the game with score: " << gameScore.playerScore2 << std::endl;
            break;
        }
    }
}

void PongGame::initializePositions() {
    ball.setPosition(screenWidth / 2, screenHeight / 2);
    player1Paddle.setPositionY(screenHeight / 2 - 100 / 2);
    player2Paddle.setPositionY(screenHeight / 2 - 100 / 2);
}

void PongGame::update() {
    //std::cout << "Ball X: " << ball.getPositionX() << std::endl;
   // std::cout << "Ball Y: " << ball.getPositionX() << std::endl;
    usleep(25000); // 15 ms
    ball.move();
    ball.bounceOnWall(screenHeight);
    ball.bounceOnPaddle(player1Paddle);
    ball.bounceOnPaddle(player2Paddle);

    if (ball.getPositionX() <= 0) {
        gameScore.playerScore2++;
        std::cout << "Player 2 scored!" << std::endl;
        initializePositions();
    } else if (ball.getPositionX() >= screenWidth) {
        gameScore.playerScore1++;
        std::cout << "Player 1 scored!" << std::endl;
        initializePositions();
    }
}

void PongGame::updatePaddle(int playerNumber, int direction) {
    if (playerNumber == 1) {
        player1Paddle.moveY(screenHeight, 5.0 * direction);
       // std::cout << "Player1 Paddle Y: " << player1Paddle.getPositionY() << std::endl;
    } else if (playerNumber == 2){
        player2Paddle.moveY(screenHeight, 5.0 * direction);
      //  std::cout << "Player2 Paddle Y: " << player2Paddle.getPositionY() << std::endl;
    }
}

std::string PongGame::getCoords() {
    return std::to_string(static_cast<int>(player1Paddle.getPositionY())) + ","
           + std::to_string(static_cast<int>(player2Paddle.getPositionY())) + ","
           + std::to_string(static_cast<int>(std::round(ball.getPositionX()))) + ","
           + std::to_string(static_cast<int>(std::round(ball.getPositionY()))) + "," + "\0";
}

GameScore PongGame::getScore() {
    return gameScore;
}
