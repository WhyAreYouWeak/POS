#ifndef POS_SOCKETRECEIVE_H
#define POS_SOCKETRECEIVE_H

#include <condition_variable>
#include <vector>
#include <mutex>
#include "Objects.h"

struct MessageBuffer {
    std::vector<char> buffer;
    std::condition_variable condVar;
    bool disconnectFlag = false;
};

void ReadSocket(unsigned long long socket, MessageBuffer& messageBuffer, TempStruct& tempStruct);

#endif //POS_SOCKETRECEIVE_H

