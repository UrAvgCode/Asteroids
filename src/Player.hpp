#pragma once

#include <raylib-cpp.hpp>
#include <cmath>
#include <vector>

#include "PhysicsObject.hpp"
#include "Bullet.hpp"

class Player : public PhysicsObject
{
public:
    float angleSpeed;
    float thrust;

    int shootTimer;

    int frame = 0;

    raylib::Texture animation[8];

    Player(float x, float y);

    void draw() const;

    void update() override;

    [[nodiscard]] bool canShoot() const;

    std::shared_ptr<Bullet> shoot();

    static float approach(float value, float goal, float step);
};