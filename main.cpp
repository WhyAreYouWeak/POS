#include "sockets/my_socket.h"
#include "PongGame.h"


int main() {
    MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 18455);

    PongGame pongGame(800, 450, "Pong Game");
    pongGame.run();

    if (mySocket != nullptr) {
        std::string input;
        mySocket->sendData("441;441");
    }

    mySocket->sendEndMessage();
    delete mySocket;
    return 0;
}