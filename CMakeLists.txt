cmake_minimum_required(VERSION 3.23)
project(Pong)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(raylib)
add_executable(Pong main.cpp
        Ball.cpp
        Paddle.cpp
        PongGame.cpp
)
target_link_libraries(Pong PRIVATE raylib)
target_include_directories(Pong PRIVATE raylib/src)