#pragma once

#include <raylib-cpp.hpp>
#include <cmath>

#include "Entity.hpp"

class Asteroid : public Entity
{
public:
    raylib::Texture texture;

    Asteroid(float x, float y, float angle, float size);

    void draw() const override;

    [[nodiscard]] Asteroid *split() const;

    [[nodiscard]] bool canSplit() const;
};