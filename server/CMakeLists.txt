cmake_minimum_required(VERSION 3.18)
project(server C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp buffer.h
        active_socket.cpp
        active_socket.h
        passive_socket.cpp
        passive_socket.h
        char_buffer.cpp
        char_buffer.h
        linked_list.h
        Ball.cpp
        Ball.h
        Paddle.cpp
        Paddle.h
        PongGame.cpp
        Objects.cpp
        Objects.h
        PongGame.h)



target_link_libraries(server pthread)