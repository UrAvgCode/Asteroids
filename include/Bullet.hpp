#pragma once

#include "Entity.hpp"

class Bullet : public Entity {
 public:
  raylib::Texture texture;

  Bullet(float x, float y, float angle);

  void draw() const override;
};