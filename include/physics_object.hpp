#pragma once

#include "game_object.hpp"

class PhysicsObject : public GameObject {
 public:
  float max_speed;
  float friction;

  PhysicsObject(float x, float y, float size);

  void update() override;

  void accelerate(raylib::Vector2 acceleration);
};
