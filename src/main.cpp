#include <raylib-cpp.hpp>
#include <vector>
#include <iostream>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"

#include "GameManager.hpp"

int main() {
    int display = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(display);
    int screenHeight = GetMonitorHeight(display);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    raylib::Window window(screenWidth, screenHeight, "Asteroids");

    raylib::Texture background("resources/bg.png");
    float backgroundWidth = background.width;
    float backgroundHeight = background.height;

    SetTargetFPS(60);

    GameManager gameManager = GameManager();

    while (!window.ShouldClose()) {
        BeginDrawing();

        window.ClearBackground(BLACK);

        background.SetWidth(GetScreenWidth());
        background.SetHeight(backgroundHeight * ((float) GetScreenWidth() / (float) backgroundWidth));

        background.Draw(0, 0);

        gameManager.gameLoop();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}