#include "sockets/my_socket.h"
#include "PongGame.h"


int main() {
    PongGame pongGame(800, 450, "Pong Game");
    pongGame.run();
    MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 12735);
    if (mySocket != nullptr) {
        std::string input;
        mySocket->sendData("441;441");
        mySocket->sendEndMessage();
    }
    mySocket->sendEndMessage();
    delete mySocket;
    return 0;
}