#include <thread>
#include "sockets/my_socket.h"
#include "SocketReceive.h"
#include "PongGame.h"
#include <mutex>
#include "Objects.h"

int main() {
    MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 12456);
    MessageBuffer messageBuffer;
    TempStruct tempStruct;
    std::thread readThread(ReadSocket, mySocket->connectSocket, std::ref(messageBuffer), std::ref(tempStruct));

   // mySocket->sendData("441;441");
   // mySocket->sendEndMessage();

    PongGame pongGame(800, 450, "Pong Game", mySocket, tempStruct);
    pongGame.run();
    /*
    auto updateCallback = [&](int player1PaddleY, int player2PaddleY, int ballX, int ballY) {
        std::lock_guard<std::mutex> lock(pongGame.gameMutex);

        pongGame.updateData(player1PaddleY, player2PaddleY, ballX, ballY );
    };
    std::thread readThread(ReadSocketAsync, mySocket->connectSocket, std::ref(messageBuffer), std::function<void(int, int, int, int)> updateCallback);
    std::thread communicationThread(&PongGame::updateData, &pongGame, std::ref(messageBuffer));
    //
    pongGame.run();
    if (mySocket != nullptr) {
        std::string input;
        mySocket->sendData("441;441");
    }
*/
    mySocket->sendEndMessage();
    delete mySocket;
    return 0;
}
/*
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
 */