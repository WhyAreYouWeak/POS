//
// Created by Patrik Kuric on 1/5/2024.
//

#ifndef POS_SOCKETRECEIVE_H
#define POS_SOCKETRECEIVE_H

#include <vector>
#include <mutex>
#include <condition_variable>

struct MessageBuffer {
    std::vector<char> buffer;
    std::mutex mutex;
    std::condition_variable condVar;
    bool disconnectFlag = false; // Flag pre odpojenie zo servera
};

void ReadSocketAsync(unsigned long long socket, MessageBuffer& messageBuffer);

#endif //POS_SOCKETRECEIVE_H

