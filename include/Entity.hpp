#pragma once

#include "raylib-cpp.hpp"
#include <memory>

class Entity {
public:
    raylib::Vector2 position;
    raylib::Vector2 velocity;

    float size;
    float rotation;
    float speed;

    Entity(float x, float y, float size);

    virtual void draw() const;

    virtual void update();

    void move(float x, float y);

    [[nodiscard]] bool isOffScreen() const;

    virtual bool checkCollision(const std::shared_ptr<Entity> &other);
};
