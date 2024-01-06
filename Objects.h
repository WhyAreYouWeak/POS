//
// Created by Patrik Kuric on 1/6/2024.
//
#include <mutex>
#include <condition_variable>
#ifndef POS_OBJECTS_H
#define POS_OBJECTS_H


typedef struct TempStruct {
    int player1PaddleY;
    int player2PaddleY;
    int ballX;
    int ballY;
    std::condition_variable changed;
    std::mutex mutex;
} TempStruct;



#endif //POS_OBJECTS_H
