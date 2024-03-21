#pragma once

#include "raylib-cpp.hpp"
#include <cmath>
#include <vector>

#include "PhysicsObject.hpp"
#include "Bullet.hpp"

class Player : public PhysicsObject
{
public:
    float angle_speed;
    float thrust;

    int shoot_timer;

    int frame = 0;

    raylib::Texture animation[8];

    Player(float x, float y);

    void draw() const override;

    void update() override;

    [[nodiscard]] bool canShoot() const;

    std::shared_ptr<Bullet> shoot();

    static float approach(float value, float goal, float step);
};