#include <iostream>
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

const int MAX_HEALTH = 100;
int health = MAX_HEALTH;
int score = 0;

void spawnAsteroid() {
    auto x = static_cast<float>(GetRandomValue(0, screenWidth));
    auto y = static_cast<float>(GetRandomValue(0, screenHeight));

    (GetRandomValue(0, 1) == 0) ? x = 0 : y = 0;

    auto angle = static_cast<float>(std::atan((x - player->position.x) / (player->position.y - y)) * (180 / M_PI));

    if (player->position.y - y > 0) {
        angle += 180;
    }

    angle += static_cast<float>(GetRandomValue(-45, 45));

    asteroids.push_back(std::make_shared<Asteroid>(x, y, angle, 150));
}

void checkCollisions() {
    std::list<std::shared_ptr<Asteroid>> asteroidsToDelete;
    std::list<std::shared_ptr<Bullet>> bulletsToDelete;

    for (const auto &asteroid: asteroids) {
        if (player->checkCollision(asteroid)) {
            health -= static_cast<int>(asteroid->size) / 10;
            asteroidsToDelete.push_back(asteroid);
        }

        for (const auto &bullet: bullets) {
            if (asteroid->checkCollision(bullet)) {
                if (asteroid->canSplit()) {
                    asteroids.push_back(asteroid->split());
                    asteroids.push_back(asteroid->split());
                } else {
                    score += 1;
                }

                asteroidsToDelete.push_back(asteroid);
                bulletsToDelete.push_back(bullet);
            }
        }
    }

    for (const auto &asteroid: asteroidsToDelete) {
        asteroids.remove(asteroid);
    }

    for (const auto &bullet: bulletsToDelete) {
        bullets.remove(bullet);
    }
}

void drawGui() {
    int healthbarWidth = 500;
    int healthbarHeight = 50;
    auto healthbarColor = health > 50 ? GREEN : health > 25 ? YELLOW : RED;

    DrawText("Health", 50, 30, 28, WHITE);
    DrawRectangle(50, 70, healthbarWidth / MAX_HEALTH * health, healthbarHeight, healthbarColor);
    DrawRectangleLines(50, 70, healthbarWidth, healthbarHeight, LIGHTGRAY);

    DrawText("Score:", 50, 135, 28, WHITE);
    DrawText(std::to_string(score).c_str(), 150, 135, 28, WHITE);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    raylib::Window window(screenWidth, screenHeight, "");

    RenderTexture2D canvas = LoadRenderTexture(screenWidth, screenHeight);
    Rectangle renderRec;

    player = std::make_shared<Player>(static_cast<float>(screenWidth) / 2.0f, static_cast<float>(screenHeight / 2.0f));

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginTextureMode(canvas);
        {
            ClearBackground(BLACK);

            checkCollisions();

            if (GetRandomValue(0, 100) < 5) {
                spawnAsteroid();
            }

            player->update();
            player->draw();

            if (IsKeyDown(KEY_SPACE) && player->canShoot()) {
                bullets.push_back(player->shoot());
            }

            std::list<std::shared_ptr<Bullet>> bulletsToDelete;
            for (const auto &bullet: bulletsToDelete) {
                bullets.remove(bullet);
            }

            for (const auto &bullet: bullets) {
                bullet->update();
                bullet->draw();

                if (bullet->isOffScreen()) bulletsToDelete.push_back(bullet);
            }

            std::list<std::shared_ptr<Asteroid>> asteroidsToDelete;
            for (const auto &asteroid: asteroidsToDelete) {
                asteroids.remove(asteroid);
            }

            for (const auto &asteroid: asteroids) {
                asteroid->update();
                asteroid->draw();

                if (asteroid->isOffScreen()) asteroidsToDelete.push_back(asteroid);
            }

            drawGui();

        }
        EndTextureMode();

        BeginDrawing();
        {
            window.ClearBackground(CLITERAL(Color){15, 15, 15});

            float widthScale = static_cast<float>(GetScreenWidth()) / static_cast<float>(canvas.texture.width);
            float heightScale = static_cast<float>(GetScreenHeight()) / static_cast<float>(canvas.texture.height);
            float renderScale = std::min(widthScale, heightScale);
            renderRec.width = static_cast<float>(canvas.texture.width) * renderScale;
            renderRec.height = static_cast<float>(canvas.texture.height) * renderScale;
            renderRec.x = (static_cast<float>(GetScreenWidth()) - renderRec.width) / 2.0f;
            renderRec.y = (static_cast<float>(GetScreenHeight()) - renderRec.height) / 2.0f;

            auto sourceWidth = static_cast<float>(canvas.texture.width);
            auto sourceHeight = static_cast<float>(-canvas.texture.height);
            Rectangle source = Rectangle{0, 0, sourceWidth, sourceHeight};

            DrawTexturePro(canvas.texture, source, renderRec, {}, 0, WHITE);
        }
        EndDrawing();
    }

    return 0;
}