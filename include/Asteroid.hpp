#pragma once

#include "Entity.hpp"

class Asteroid : public Entity {
 public:
  raylib::Texture texture;

  Asteroid(float x, float y, raylib::Vector2 dir, float size);

  void draw() const override;

  [[nodiscard]] std::shared_ptr<Asteroid> split() const;

  [[nodiscard]] bool canSplit() const;
};