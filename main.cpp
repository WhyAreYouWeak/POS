#include <complex>
#include "raylib.h"
#include "PongGame.cpp"
int main() {
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);
    PongGame game(screenWidth, screenHeight);
    game.initialize();
    while (!WindowShouldClose()) {
        game.update();
        game.draw();
    }
    CloseWindow();
    return 0;
}