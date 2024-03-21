#include "Asteroid.hpp"

#include <cmath>

Asteroid::Asteroid(float x, float y, float rotation, float size)
    : Entity(x, y, size) {
  this->rotation = rotation;

  speed = 5.0f;
  velocity.x = static_cast<float>(std::sin(rotation * DEG2RAD) * speed);
  velocity.y = static_cast<float>(-std::cos(rotation * DEG2RAD) * speed);

  texture = raylib::Texture("res/asteroid.png");

  float texture_height = static_cast<float>(texture.height);
  float scale = size / texture_height;
  texture.SetWidth(static_cast<int>(size));
  texture.SetHeight(static_cast<int>(texture_height * scale));
}

void Asteroid::draw() const {
  float width = static_cast<float>(texture.width);
  float height = static_cast<float>(texture.height);

  raylib::Rectangle source(0.0f, 0.0f, width, height);
  raylib::Rectangle dest(position.x, position.y, width, height);
  raylib::Vector2 origin = {width / 2.0f, height / 2.0f};
  DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

std::shared_ptr<Asteroid> Asteroid::split() const {
  float angle = rotation + static_cast<float>(GetRandomValue(-45, 45));
  return std::make_shared<Asteroid>(position.x, position.y, angle, size / 1.5f);
}

bool Asteroid::canSplit() const {
  return size > 150.0f;
}