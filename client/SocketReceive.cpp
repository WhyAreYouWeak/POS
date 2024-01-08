#include <mutex>
#include "winsock2.h"
#include "SocketReceive.h"
#include "Objects.h"
#include <algorithm>

void ReadSocket(SOCKET socket, MessageBuffer& messageBuffer, TempStruct& tempStruct) {
    while (true) {
        char buffer[1024];
        int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::unique_lock<std::mutex> lock(tempStruct.mutex);

            messageBuffer.buffer.insert(messageBuffer.buffer.end(), buffer, buffer + bytesRead);

            auto score = std::find(messageBuffer.buffer.begin(), messageBuffer.buffer.end(), 's');
            if (score != messageBuffer.buffer.end()) {
                int playerScore1 = *(score + 2) - '0';
                int playerScore2 = *(score + 4) - '0';
                tempStruct.playerScore1 = playerScore1;
                tempStruct.playerScore2 = playerScore2;
            } else {
                sscanf(messageBuffer.buffer.data(), "%d,%d,%d,%d", &tempStruct.player1PaddleY, &tempStruct.player2PaddleY, &tempStruct.ballX, &tempStruct.ballY);
            }

            messageBuffer.buffer.clear();
            lock.unlock();


            messageBuffer.condVar.notify_one();
            if (strstr(buffer, ":end") != nullptr) {
                Sleep(5);
                messageBuffer.disconnectFlag = true;
                messageBuffer.condVar.notify_one();
                break;
            }
        }
    }
}
