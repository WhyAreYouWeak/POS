#include <mutex>
#include "iostream"
#include "winsock2.h"
#include "thread"
#include "SocketReceive.h"
#include "Objects.h"

void ReadSocket(SOCKET socket, MessageBuffer& messageBuffer, TempStruct& tempStruct) {
    while (true) {
        char buffer[1024];
        int bytesRead = recv(socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::unique_lock<std::mutex> lock(messageBuffer.mutex);

            messageBuffer.buffer.insert(messageBuffer.buffer.end(), buffer, buffer + bytesRead);

            sscanf(messageBuffer.buffer.data(), "%d,%d,%d,%d", &tempStruct.player1PaddleY, &tempStruct.player2PaddleY, &tempStruct.ballX, &tempStruct.ballY);

            tempStruct.changed.notify_one();


/*
            std::cout << "Obsah vektora: ";
            for (size_t i = 0; i < messageBuffer.buffer.size(); ++i) {
                std::cout << messageBuffer.buffer[i];
            }
            std::cout << std::endl;
*/
            /*
            std::cout << std::endl;
            std::cout << "player1PaddleY: " << player1PaddleY << std::endl;
            std::cout << std::endl;
            std::cout << "player2PaddleY: " << player2PaddleY << std::endl;
            std::cout << std::endl;
            std::cout << "size:" << messageBuffer.buffer.size() << std::endl;
            std::cout << std::endl;
             */
          //  std::cout << "ballX: " << ballX << std::endl;
          //  std::cout << "ballY: " << ballY << std::endl;

            messageBuffer.buffer.clear();
            lock.unlock();
            messageBuffer.condVar.notify_one();

            // Ak je prijatá správa ":end", okamžite oznam odpojenie
            if (strstr(buffer, ":end") != nullptr) {
                //ten sleep tu musi byt, lebo inak sa nestihnu vypisat vsetky spravy v metode PrintMessages
                Sleep(5);
                messageBuffer.disconnectFlag = true;
                messageBuffer.condVar.notify_one();
                break;
            }

        } else if (bytesRead == 0) {
            std::cout << "Pripojenie zatvorene serverom." << std::endl;
            messageBuffer.disconnectFlag = true; // Nastavenie flagu na odpojenie zo servera
            messageBuffer.condVar.notify_one();   // Oznámenie všetkým vláknami, že je čas skončiť
            break;
        } else {
            std::cerr << "Chyba pri cítani dat zo soketu." << std::endl;
            messageBuffer.disconnectFlag = true; // Nastavenie flagu na odpojenie zo servera
            messageBuffer.condVar.notify_one();   // Oznámenie všetkým vláknami, že je čas skončiť
            break;
        }
    }
}
