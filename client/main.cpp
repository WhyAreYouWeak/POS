#include <thread>
#include "sockets/my_socket.h"
#include "SocketReceive.h"
#include "PongGame.h"
#include <crtdbg.h>
#include "Objects.h"

int main() {
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    {
        MySocket *mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 19195);
        MessageBuffer messageBuffer;
        TempStruct tempStruct;
        std::thread readThread(ReadSocket, mySocket->connectSocket, std::ref(messageBuffer), std::ref(tempStruct));

        PongGame pongGame(800, 450, "Pong Game", mySocket, tempStruct);
        pongGame.run();
        mySocket->sendEndMessage();
        delete mySocket;
    }

    return 0;
}