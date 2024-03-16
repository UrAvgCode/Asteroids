#pragma once

#include "Entity.hpp"

class PhysicsObject : public Entity {

public:
    float max_speed;
    float friction;

    PhysicsObject(float x, float y, float size);

    void update() override;

    void accelerate(raylib::Vector2 acceleration);
};
