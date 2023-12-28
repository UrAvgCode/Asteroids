#pragma once

#include <raylib-cpp.hpp>
#include <cmath>
#include <vector>

#include "Bullet.hpp"
#include "PhysicsObject.hpp"

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

    Bullet *shoot();

    Bullet *superShoot();

    static float approach(float value, float goal, float step);
};