#include "game_object.hpp"

float screen_width = 3840;
float screen_height = 2160;

Entity::Entity(float x, float y, float size) {
  position = raylib::Vector2(x, y);
  velocity = raylib::Vector2(0.0f, 0.0f);

  this->size = size;
  rotation = 0.0f;
  speed = 0.0f;
}

void Entity::draw() const {
  int x = static_cast<int>(position.x);
  int y = static_cast<int>(position.y);
  DrawCircle(x, y, 10.0f, RED);
}

void Entity::update() {
  position += velocity;
}

void Entity::move(float x, float y) {
  this->position.x += x;
  this->position.y += y;
}

bool Entity::isOffScreen() const {
  bool off_screen_x = position.x < 0.0f || position.x > screen_width;
  bool off_screen_y = position.y < 0.0f || position.y > screen_height;
  return off_screen_x || off_screen_y;
}

bool Entity::checkCollision(const std::shared_ptr<Entity>& other) {
  float radius = size / 2.0f;
  float other_radius = other->size / 2.0f;
  return CheckCollisionCircles(position, radius, other->position, other_radius);
}
