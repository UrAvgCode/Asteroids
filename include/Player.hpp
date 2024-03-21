#pragma once

#include <array>

#include "Bullet.hpp"
#include "PhysicsObject.hpp"

class Player : public PhysicsObject {
 public:
  float angle_speed;
  float thrust;

  int shoot_timer;
  int frame = 0;

  std::array<raylib::Texture, 8> animation;

  Player(float x, float y);

  void draw() const override;

  void update() override;

  [[nodiscard]] bool canShoot() const;

  std::shared_ptr<Bullet> shoot();

  static float approach(float value, float goal, float step);
};