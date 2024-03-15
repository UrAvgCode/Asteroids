#include "raylib-cpp.hpp"

int main() {
    int screenWidth = 1280;
    int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    raylib::Window window(screenWidth, screenHeight, "");

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    Rectangle renderRec;

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginTextureMode(canvas);
        {
            ClearBackground(RAYWHITE);
            DrawText("Hello World", 500, 300, 45, DARKGRAY);
        }
        EndTextureMode();

        BeginDrawing();
        {
            window.ClearBackground(BLACK);

            float renderScale = std::min((float) GetScreenHeight() / (float) canvas.texture.height,
                                         (float) GetScreenWidth() / (float) canvas.texture.width);
            renderRec.width = (float) canvas.texture.width * renderScale;
            renderRec.height = (float) canvas.texture.height * renderScale;
            renderRec.x = ((float) GetScreenWidth() - renderRec.width) / 2.0f;
            renderRec.y = ((float) GetScreenHeight() - renderRec.height) / 2.0f;

            Rectangle source = Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height};
            DrawTexturePro(canvas.texture, source, renderRec, {}, 0, WHITE);
        }
        EndDrawing();
    }

    return 0;
}