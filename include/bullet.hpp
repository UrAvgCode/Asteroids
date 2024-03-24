#pragma once

#include "game_object.hpp"

class Bullet : public Entity {
 public:
  raylib::Texture texture;

  Bullet(float x, float y, float rotaton);

  void draw() const override;
};