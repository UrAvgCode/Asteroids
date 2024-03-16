#include "raylib-cpp.hpp"
#include "Player.hpp"

int main() {
    int screenWidth = 3840;
    int screenHeight = 2160;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    raylib::Window window(screenWidth, screenHeight, "");

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    Rectangle renderRec;

    Player player((float) screenWidth / 2.0f, (float) screenHeight / 2.0f);

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginTextureMode(canvas);
        {
            ClearBackground(BLACK);

            player.update();
            player.draw();

        }
        EndTextureMode();

        BeginDrawing();
        {
            window.ClearBackground(CLITERAL(Color){15,15,15});

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