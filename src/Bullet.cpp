#include "Bullet.hpp"

#include <cmath>

Bullet::Bullet(float x, float y, float rotation) : Entity(x, y, 10.0f) {
  this->rotation = rotation;

  speed = 23.0f;
  velocity += raylib::Vector2{0.0f, -speed}.Rotate(DEG2RAD * rotation);

  texture = raylib::Texture("res/laser.png");
}

void Bullet::draw() const {
  auto width = static_cast<float>(texture.width);
  auto height = static_cast<float>(texture.height);

  raylib::Rectangle source(0.0f, 0.0f, width, height);
  raylib::Rectangle dest(position.x, position.y, width, height);
  raylib::Vector2 origin = {width / 2.0f, height / 2.0f};
  DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
}