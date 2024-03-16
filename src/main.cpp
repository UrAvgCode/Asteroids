#include <memory>
#include <list>

#include "raylib-cpp.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"

const int screenWidth = 3840;
const int screenHeight = 2160;

std::list<std::shared_ptr<Asteroid>> asteroids;
std::list<std::shared_ptr<Bullet>> bullets;
std::shared_ptr<Player> player;

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    raylib::Window window(screenWidth, screenHeight, "");

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    Rectangle renderRec;

    player = std::make_shared<Player>((float) screenWidth / 2.0f, (float) screenHeight / 2.0f);

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginTextureMode(canvas);
        {
            ClearBackground(BLACK);

            if (GetRandomValue(0, 100) < 5) {
                auto x = (float) GetRandomValue(0, GetScreenWidth());
                auto y = (float) GetRandomValue(0, GetScreenHeight());

                if (GetRandomValue(0, 1) == 0)
                    x = 0;
                else
                    y = 0;

                auto angle = (float) (atan((x - player->position.x) / (player->position.y - y)) * (180 / M_PI));

                if (player->position.y - y > 0)
                    angle += 180;

                angle += (float) GetRandomValue(-45, 45);

                asteroids.push_back(std::make_shared<Asteroid>(x, y, angle, 150));
            }

            player->update();
            player->draw();

            if (IsKeyDown(KEY_SPACE) && player->canShoot()) {
                bullets.push_back(player->shoot());
            }

            for (auto &bullet: bullets) {
                bullet->update();
                bullet->draw();
            }

            for (auto &asteroid: asteroids) {
                asteroid->update();
                asteroid->draw();
            }
        }
        EndTextureMode();

        BeginDrawing();
        {
            window.ClearBackground(CLITERAL(Color){15, 15, 15});

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