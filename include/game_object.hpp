#pragma once

#include <memory>
#include <raylib-cpp.hpp>

class GameObject {
 public:
  raylib::Vector2 position;
  raylib::Vector2 velocity;

  float size;
  float rotation;
  float speed;

  GameObject(float x, float y, float size);

  virtual void draw() const;

  virtual void update();

  void move(float x, float y);

  [[nodiscard]] bool isOffScreen() const;

  virtual bool checkCollision(const std::shared_ptr<GameObject>& other);
};
