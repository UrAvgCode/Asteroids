#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <raylib-cpp.hpp>

#include "Asteroid.hpp"
#include "Player.hpp"

const int canvas_width = 3840;
const int canvas_height = 2160;

std::list<std::shared_ptr<Asteroid>> asteroids;
std::list<std::shared_ptr<Bullet>> bullets;
std::shared_ptr<Player> player;

const int max_health = 100;
int health = max_health;
int score = 0;

void spawnAsteroid() {
  float x = static_cast<float>(GetRandomValue(0, canvas_width));
  float y = static_cast<float>(GetRandomValue(0, canvas_height));
  (GetRandomValue(0, 1) == 0) ? x = 0.0f : y = 0.0f;

  float delta_x = player->position.x - x;
  float delta_y = player->position.y - y;
  raylib::Vector2 direction_vector = raylib::Vector2{delta_x, delta_y};

  float angle_offset = static_cast<float>(GetRandomValue(-20, 20));
  direction_vector = direction_vector.Rotate(DEG2RAD * angle_offset);

  float size = static_cast<float>(GetRandomValue(150, 250));

  asteroids.push_back(std::make_shared<Asteroid>(x, y, direction_vector, size));
}

void checkCollisions() {
  std::list<std::shared_ptr<Asteroid>> asteroids_to_delete;
  std::list<std::shared_ptr<Bullet>> bullets_to_delete;

  for (const auto& asteroid : asteroids) {
    if (player->checkCollision(asteroid)) {
      health -= static_cast<int>(asteroid->size) / 10;
      asteroids_to_delete.push_back(asteroid);
    }

    for (const auto& bullet : bullets) {
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

  for (const auto& asteroid : asteroids_to_delete) {
    asteroids.remove(asteroid);
  }

  for (const auto& bullet : bullets_to_delete) {
    bullets.remove(bullet);
  }
}

void drawGui() {
  int health_bar_width = 500;
  int health_bar_height = 50;
  int health_width = health_bar_width / max_health * health;
  auto health_bar_color = health > 50 ? GREEN : health > 25 ? YELLOW : RED;

  DrawText("Health", 50, 30, 28, WHITE);
  DrawRectangle(50, 70, health_width, health_bar_height, health_bar_color);
  DrawRectangleLines(50, 70, health_bar_width, health_bar_height, LIGHTGRAY);

  DrawText("Score:", 50, 135, 28, WHITE);
  DrawText(std::to_string(score).c_str(), 150, 135, 28, WHITE);
}

void resetGame() {
  score = 0;
  health = max_health;
  player->position.x = static_cast<float>(canvas_width) / 2.0f;
  player->position.y = static_cast<float>(canvas_height) / 2.0f;
  asteroids.clear();
}

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
  raylib::Window window(canvas_width, canvas_height, "");

  RenderTexture2D canvas = LoadRenderTexture(canvas_width, canvas_height);
  Rectangle render_rec;

  float screen_center_x = static_cast<float>(canvas_width) / 2.0f;
  float screen_center_y = static_cast<float>(canvas_height) / 2.0f;
  player = std::make_shared<Player>(screen_center_x, screen_center_y);

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
      for (const auto& bullet : bullets_to_delete) {
        bullets.remove(bullet);
      }

      for (const auto& bullet : bullets) {
        bullet->update();
        bullet->draw();

        if (bullet->isOffScreen())
          bullets_to_delete.push_back(bullet);
      }

      std::list<std::shared_ptr<Asteroid>> asteroids_to_delete;
      for (const auto& asteroid : asteroids_to_delete) {
        asteroids.remove(asteroid);
      }

      for (const auto& asteroid : asteroids) {
        asteroid->update();
        asteroid->draw();

        if (asteroid->isOffScreen()) {
          asteroids_to_delete.push_back(asteroid);
        }
      }

      drawGui();
    }
    EndTextureMode();

    BeginDrawing();
    {
      window.ClearBackground(CLITERAL(Color){15, 15, 15});

      float display_width = static_cast<float>(GetScreenWidth());
      float canvas_width = static_cast<float>(canvas.texture.width);
      float width_scale = display_width / canvas_width;

      float display_height = static_cast<float>(GetScreenHeight());
      float canvas_height = static_cast<float>(canvas.texture.height);
      float height_scale = display_height / canvas_height;

      float render_scale = std::min(width_scale, height_scale);

      render_rec.width = canvas_width * render_scale;
      render_rec.height = canvas_height * render_scale;
      render_rec.x = (display_width - render_rec.width) / 2.0f;
      render_rec.y = (display_height - render_rec.height) / 2.0f;

      float source_width = static_cast<float>(canvas.texture.width);
      float source_height = static_cast<float>(-canvas.texture.height);
      raylib::Rectangle source = {0.0f, 0.0f, source_width, source_height};

      SetTextureFilter(canvas.texture, TEXTURE_FILTER_TRILINEAR);
      DrawTexturePro(canvas.texture, source, render_rec, {}, 0.0f, WHITE);
    }
    EndDrawing();
  }

  return 0;
}