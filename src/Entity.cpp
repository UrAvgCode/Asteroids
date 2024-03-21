#include "../include/Entity.hpp"

float screen_width = 3840;
float screen_height = 2160;

Entity::Entity(float x, float y, float size) {
    position = raylib::Vector2(x, y);
    velocity = raylib::Vector2(0.0, 0.0);

    this->size = size;
    rotation = 0;
    speed = 0;
}

void Entity::draw() const {
    DrawCircle((int) position.x, (int) position.y, 10.0f, RED);
}

void Entity::update() {
    position += velocity;
}

void Entity::move(float x, float y) {
    this->position.x += x;
    this->position.y += y;
}

bool Entity::isOffScreen() const {
    return position.x < 0 || position.x > screen_width || position.y < 0 || position.y > screen_height;
}

bool Entity::checkCollision(const std::shared_ptr<Entity> &other) {
    return (CheckCollisionCircles(Vector2{(float) position.x, (float) position.y}, size / 2.0f,
                                  Vector2{(float) other->position.x, (float) other->position.y}, other->size / 2.0f));
}
