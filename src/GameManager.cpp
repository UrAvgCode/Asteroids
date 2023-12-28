#include "GameManager.hpp"

GameManager::GameManager()
        : player((float) GetScreenWidth() / 2.0f, (float) GetScreenHeight() / 2.0f) {
}

void GameManager::gameLoop() {
    // spawn asteroids
    if (GetRandomValue(0, 100) < 5) {
        auto x = (float) GetRandomValue(0, GetScreenWidth());
        auto y = (float) GetRandomValue(0, GetScreenHeight());

        if (GetRandomValue(0, 1) == 0)
            x = 0;
        else
            y = 0;

        auto angle = (float) (atan((x - player.position.x) / (player.position.y - y)) * (180 / M_PI));

        if (player.position.y - y > 0)
            angle += 180;

        angle += (float) GetRandomValue(-45, 45);

        asteroids.push_back(new Asteroid(x, y, angle, 150));
    }

    // player movement
    player.update();
    player.draw();

    // player shooting
    if (IsKeyDown(KEY_SPACE) && player.canShoot()) {
        bullets.push_back(player.shoot());
        bullets.push_back(player.superShoot());
    }

    checkCollisions();

    // bullet off-screen
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->isOffScreen()) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }

    // bullet draw and update
    for (auto &bullet: bullets) {
        bullet->update();
        bullet->draw();
    }

    // asteroid movement
    for (int i = 0; i < asteroids.size(); i++) {
        if (asteroids[i]->isOffScreen()) {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
        }
    }

    for (auto &asteroid: asteroids) {
        asteroid->update();
        asteroid->draw();
    }

    // Healthbar
    int healthbarWidth = 400;
    int healthbarHeight = 40;
    auto healthbarColor = health > 50 ? GREEN : health > 25 ? YELLOW : RED;

    DrawText("Health", 50, 20, 20, WHITE);
    DrawRectangle(50, 50, healthbarWidth / MAX_HEALTH * health, healthbarHeight, healthbarColor);
    DrawRectangleLines(50, 50, healthbarWidth, healthbarHeight, LIGHTGRAY);

    // Score
    DrawText("Score:", 50, 100, 20, WHITE);
    DrawText(std::to_string(score).c_str(), 125, 100, 20, WHITE);
}

void GameManager::checkCollisions() {
    // collision detection between bullets and asteroids
    for (int i = 0; i < asteroids.size(); i++) {
        for (int j = 0; j < bullets.size(); j++) {
            if (bullets[j]->checkCollision(asteroids[i])) {
                if (asteroids[i]->canSplit()) {
                    Asteroid *originalAsteroid = asteroids[i];

                    asteroids[i] = originalAsteroid->split();
                    asteroids.push_back(originalAsteroid->split());

                    delete originalAsteroid;
                } else {
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);

                    score += 1;
                }

                delete bullets[j];
                bullets.erase(bullets.begin() + j);

                break;
            }
        }
    }

    // collision detection between player and asteroids
    for (int i = 0; i < asteroids.size(); i++) {
        if (player.checkCollision(asteroids[i])) {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);

            health -= 10;

            break;
        }
    }
}
