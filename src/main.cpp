#include "raylib-cpp.hpp"

int main() {
    int screenWidth = 1280;
    int screenHeight = 720;

    raylib::Window window(screenWidth, screenHeight, "");

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginDrawing();

        window.ClearBackground(RAYWHITE);

        EndDrawing();
    }

    return 0;
}