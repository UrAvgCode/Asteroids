#include <iostream>
#include <memory>
#include <list>

#include "raylib-cpp.hpp"
#include "../include/Player.hpp"
#include "../include/Asteroid.hpp"

const int screen_width = 3840;
const int screen_height = 2160;

std::list<std::shared_ptr<Asteroid>> asteroids;
std::list<std::shared_ptr<Bullet>> bullets;
std::shared_ptr<Player> player;

const int max_health = 100;
int health = max_health;
int score = 0;

void spawnAsteroid() {
    auto x = static_cast<float>(GetRandomValue(0, screen_width));
    auto y = static_cast<float>(GetRandomValue(0, screen_height));

    (GetRandomValue(0, 1) == 0) ? x = 0.0f : y = 0.0f;

    auto angle = static_cast<float>(std::atan((x - player->position.x) / (player->position.y - y)) * (180.0f / M_PI));

    if (player->position.y - y > 0.0f) {
        angle += 180.0f;
    }

    angle += static_cast<float>(GetRandomValue(-45, 45));

    asteroids.push_back(std::make_shared<Asteroid>(x, y, angle, 150));
}

void checkCollisions() {
    std::list<std::shared_ptr<Asteroid>> asteroids_to_delete;
    std::list<std::shared_ptr<Bullet>> bullets_to_delete;

    for (const auto &asteroid: asteroids) {
        if (player->checkCollision(asteroid)) {
            health -= static_cast<int>(asteroid->size) / 10;
            asteroids_to_delete.push_back(asteroid);
        }

        for (const auto &bullet: bullets) {
            if (asteroid->checkCollision(bullet)) {
                if (asteroid->canSplit()) {
                    asteroids.push_back(asteroid->split());
                    asteroids.push_back(asteroid->split());
                } else {
                    score += 1;
                }

                asteroids_to_delete.push_back(asteroid);
                bullets_to_delete.push_back(bullet);
            }
        }
    }

    for (const auto &asteroid: asteroids_to_delete) {
        asteroids.remove(asteroid);
    }

    for (const auto &bullet: bullets_to_delete) {
        bullets.remove(bullet);
    }
}

void drawGui() {
    int health_bar_width = 500;
    int health_bar_height = 50;
    auto health_bar_color = health > 50 ? GREEN : health > 25 ? YELLOW : RED;

    DrawText("Health", 50, 30, 28, WHITE);
    DrawRectangle(50, 70, health_bar_width / max_health * health, health_bar_height, health_bar_color);
    DrawRectangleLines(50, 70, health_bar_width, health_bar_height, LIGHTGRAY);

    DrawText("Score:", 50, 135, 28, WHITE);
    DrawText(std::to_string(score).c_str(), 150, 135, 28, WHITE);
}

void resetGame() {
    score = 0;
    health = max_health;
    player->position.x = static_cast<float>(screen_width) / 2.0f;
    player->position.y = static_cast<float>(screen_height) / 2.0f;
    asteroids.clear();
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    raylib::Window window(screen_width, screen_height, "");

    RenderTexture2D canvas = LoadRenderTexture(screen_width, screen_height);
    Rectangle render_rec;

    player = std::make_shared<Player>(static_cast<float>(screen_width) / 2.0f, static_cast<float>(screen_height / 2.0f));

    SetTargetFPS(60);

    while (!window.ShouldClose()) {
        BeginTextureMode(canvas);
        {
            ClearBackground(BLACK);

            if (health <= 0) {
                resetGame();
            }

            checkCollisions();

            if (GetRandomValue(0, 100) < 5) {
                spawnAsteroid();
            }

            player->update();
            player->draw();

            if (IsKeyDown(KEY_SPACE) && player->canShoot()) {
                bullets.push_back(player->shoot());
            }

            std::list<std::shared_ptr<Bullet>> bullets_to_delete;
            for (const auto &bullet: bullets_to_delete) {
                bullets.remove(bullet);
            }

            for (const auto &bullet: bullets) {
                bullet->update();
                bullet->draw();

                if (bullet->isOffScreen()) bullets_to_delete.push_back(bullet);
            }

            std::list<std::shared_ptr<Asteroid>> asteroids_to_delete;
            for (const auto &asteroid: asteroids_to_delete) {
                asteroids.remove(asteroid);
            }

            for (const auto &asteroid: asteroids) {
                asteroid->update();
                asteroid->draw();

                if (asteroid->isOffScreen()) asteroids_to_delete.push_back(asteroid);
            }

            drawGui();

        }
        EndTextureMode();

        BeginDrawing();
        {
            window.ClearBackground(CLITERAL(Color){15, 15, 15});

            float width_scale = static_cast<float>(GetScreenWidth()) / static_cast<float>(canvas.texture.width);
            float height_scale = static_cast<float>(GetScreenHeight()) / static_cast<float>(canvas.texture.height);
            float render_scale = std::min(width_scale, height_scale);
            render_rec.width = static_cast<float>(canvas.texture.width) * render_scale;
            render_rec.height = static_cast<float>(canvas.texture.height) * render_scale;
            render_rec.x = (static_cast<float>(GetScreenWidth()) - render_rec.width) / 2.0f;
            render_rec.y = (static_cast<float>(GetScreenHeight()) - render_rec.height) / 2.0f;

            auto source_width = static_cast<float>(canvas.texture.width);
            auto source_height = static_cast<float>(-canvas.texture.height);
            Rectangle source = Rectangle{0.0f, 0.0f, source_width, source_height};

            DrawTexturePro(canvas.texture, source, render_rec, {}, 0.0f, WHITE);
        }
        EndDrawing();
    }

    return 0;
}