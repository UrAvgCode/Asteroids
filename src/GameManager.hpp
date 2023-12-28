#pragma once
#include <raylib-cpp.hpp>

#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"

class GameManager {
public:

    Player player;
    std::vector<Bullet *> bullets;
    std::vector<Asteroid *> asteroids;

    const int MAX_HEALTH = 100;
    int health = MAX_HEALTH;
    int score = 0;

    GameManager();

    void gameLoop();

    void checkCollisions();
};
