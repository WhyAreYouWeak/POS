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
    PongGame pongGame(800, 450, "Pong Game", mySocket, tempStruct);
    pongGame.run();
    mySocket->sendEndMessage();
    delete mySocket;
    return 0;
}