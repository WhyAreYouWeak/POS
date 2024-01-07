cmake_minimum_required(VERSION 3.18)
project(server C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp buffer.h
        pos_sockets/active_socket.c
        pos_sockets/active_socket.h
        pos_sockets/passive_socket.c
        pos_sockets/passive_socket.h
        pos_sockets/char_buffer.c
        pos_sockets/char_buffer.h
        pos_sockets/linked_list.h
        Ball.cpp
        Ball.h
        Paddle.cpp
        Paddle.h
        PongGame.cpp
        Objects.cpp
        Objects.h)



target_link_libraries(server pthread)