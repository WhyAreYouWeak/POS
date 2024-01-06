cmake_minimum_required(VERSION 3.23)
project(POS)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(raylib)
add_executable(POS main.cpp
        Paddle.h
        Ball.h
        sockets/my_socket.h
        main.cpp
        Ball.cpp
        Paddle.cpp
        sockets/my_socket.cpp SocketReceive.cpp SocketReceive.h PongGame.cpp PongGame.h)
target_link_libraries(POS PRIVATE raylib wsock32 ws2_32)


target_include_directories(POS PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}  # Include project source directory
        raylib/src                   # Include raylib headers
)