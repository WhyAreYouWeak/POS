cmake_minimum_required(VERSION 3.23)
project(POS)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(raylib)
add_executable(POS main.cpp
        Ball.cpp
        Paddle.cpp
        PongGame.cpp
        PongGame.h
        Paddle.h
        Ball.h)
target_link_libraries(POS PRIVATE raylib)
target_include_directories(POS PRIVATE raylib/src)