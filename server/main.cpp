#include <stdio.h>
#include <stdbool.h>
#include <cstring>
#include <strings.h>
#include <pthread.h>
#include "pos_sockets/char_buffer.h"
#include "pos_sockets/active_socket.h"
#include "pos_sockets/passive_socket.h"
#include "PongGame.h"
#include "Objects.h"
#include <iostream>
#include <thread>

bool gameIsRunning;
_Bool deserializeCommand(int* direction, struct char_buffer* buf) {
    if (strcmp(buf->data, "up") == 0) {
        *direction = -1; //up
        return true;
    } else if (strcmp(buf->data, "down") == 0) {
        *direction = 1; //down
        return true;
    } else {
        return false;
    }
}


typedef struct thread_data {
    pthread_mutex_t mutex;
    pthread_cond_t is_full;
    pthread_cond_t is_empty;
    int player;
    PongGame* pongGame;
    short port;
    ACTIVE_SOCKET* my_socket;
} THREAD_DATA;

void thread_data_init(struct thread_data* data,
                      short port, ACTIVE_SOCKET* my_socket,
                      PongGame* pongGame, int player) {
    pthread_mutex_init(&data->mutex, NULL);
    pthread_cond_init(&data->is_full, NULL);
    pthread_cond_init(&data->is_empty, NULL);

    data->port = port;
    data->my_socket = my_socket;
    data->pongGame = pongGame;
    data->player = player;
}

void thread_data_destroy(struct thread_data* data) {
    pthread_mutex_destroy(&data->mutex);
    pthread_cond_destroy(&data->is_full);
    pthread_cond_destroy(&data->is_empty);

    data->port = 0;
    data->my_socket = NULL;
}

void* process_client_data(void* thread_data) {
    THREAD_DATA *data = (THREAD_DATA *)thread_data;
    PASSIVE_SOCKET p_socket;
    passive_socket_init(&p_socket);
    passive_socket_start_listening(&p_socket, data->port);
    passive_socket_wait_for_client(&p_socket, data->my_socket);
    passive_socket_stop_listening(&p_socket);
    passive_socket_destroy(&p_socket);

    printf("Player Connected\n");
    active_socket_start_reading(data->my_socket);
    printf("Player Disconnected\n");
    return NULL;
}

void* produce(void* thread_data) {
    struct thread_data* data = (struct thread_data*)thread_data;
    std::string coordsPrev;
    GameScore gameScorePrev;
    GameScore gameScore;
    while (true) {
        if (!gameIsRunning) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::string coordsStr = data->pongGame->getCoords();
        gameScore = data->pongGame->getScore();
        if (gameScore.playerScore1 != gameScorePrev.playerScore1 ||
            gameScore.playerScore2 != gameScorePrev.playerScore2) {
            gameScorePrev = gameScore;
            CHAR_BUFFER r_buf;
            char_buffer_init(&r_buf);
            std::string str = "s:" + std::to_string(static_cast<int>(gameScore.playerScore1)) + ","
                              + std::to_string(static_cast<int>(gameScore.playerScore2));
            const char *strToSend = str.c_str();
            char_buffer_append(&r_buf, strToSend, strlen(strToSend));
            active_socket_write_data(data->my_socket, &r_buf);
            continue;
        }

        if (coordsStr == coordsPrev) {
            continue;
        }

        coordsPrev = coordsStr;
        gameScorePrev = gameScore;
        const char *coords = coordsStr.c_str();

        CHAR_BUFFER r_buf;
        char_buffer_init(&r_buf);
        char_buffer_append(&r_buf, coords, strlen(coords));
        active_socket_write_data(data->my_socket, &r_buf);

    }
}

_Bool getClientCommand(struct active_socket* my_sock, int* direction) {
    _Bool result = false;
    CHAR_BUFFER r_buf;
    char_buffer_init(&r_buf);

    if(active_socket_try_get_read_data(my_sock, &r_buf)) {
        if(r_buf.size > 0) {
            //   std::cout << r_buf.data << std::endl;
            if(active_socket_is_end_message(my_sock, &r_buf)) {
                active_socket_stop_reading(my_sock);
            } else if (deserializeCommand(direction, &r_buf)) {
                result = true;
            } else {
                printf("Klient poslal spravu v zlom formate\ndata: %s\n", r_buf.data);
            }
        }
    }
    char_buffer_destroy(&r_buf);
    return result;
}

void* consume(void* thread_data) {
    int direction;
    struct thread_data* data = (struct thread_data*)thread_data;

    if (data->my_socket != NULL) {
        while (active_socket_is_reading(data->my_socket)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (getClientCommand(data->my_socket, &direction)) {
                data->pongGame->updatePaddle(data->player, direction);
            }
        }
    }
    return NULL;
}

int main() {
    PongGame pongGame(800, 450);

    pthread_t client1;
    pthread_t client2;
    pthread_t client1Consume;
    pthread_t client2Consume;
    pthread_t client1Produce;
    pthread_t client2Produce;

    struct active_socket socketClient1;
    struct active_socket socketClient2;

    active_socket_init(&socketClient1);
    active_socket_init(&socketClient2);

    struct thread_data dataClient1;
    struct thread_data dataClient2;
    thread_data_init(&dataClient1, 19195, &socketClient1, &pongGame, 1);
    thread_data_init(&dataClient2, 12456, &socketClient2, &pongGame, 2);

    pthread_create(&client1, NULL, process_client_data, &dataClient1);
    pthread_create(&client2, NULL, process_client_data, &dataClient2);

    while (true) {
        if (socketClient1.is_reading && socketClient2.is_reading) {
            std::cout << "Both players connected." << std::endl;
            std::cout << "The game is starting." << std::endl;
            gameIsRunning = true;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "Waiting for both players to connect." << std::endl;
    }

    pthread_create(&client1Consume, NULL, consume, &dataClient1);
    pthread_create(&client2Consume, NULL, consume, &dataClient2);
    pthread_create(&client1Produce, NULL, produce, &dataClient1);
    pthread_create(&client2Produce, NULL, produce, &dataClient2);

    pongGame.run();
    gameIsRunning = false;

    pthread_join(client1, NULL);
    pthread_join(client2, NULL);
    pthread_join(client1Consume, NULL);
    pthread_join(client2Consume, NULL);
    pthread_join(client1Produce, NULL);
    pthread_join(client2Produce, NULL);

    thread_data_destroy(&dataClient1);
    thread_data_destroy(&dataClient2);

    active_socket_destroy(&socketClient1);
    active_socket_destroy(&socketClient2);

    return 0;
}
