//
// Created by Patrik Kuric on 1/5/2024.
//

#ifndef POS_SOCKETRECEIVE_H
#define POS_SOCKETRECEIVE_H

#include <condition_variable>
#include <vector>
#include <mutex>
#include "Objects.h"

struct MessageBuffer {
    std::vector<char> buffer;
    std::mutex mutex;
    std::condition_variable condVar;
    bool disconnectFlag = false; // Flag pre odpojenie zo servera
};

void ReadSocket(unsigned long long socket, MessageBuffer& messageBuffer, TempStruct& tempStruct);

#endif //POS_SOCKETRECEIVE_H

