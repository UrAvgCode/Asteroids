#include "Entity.hpp"

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
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), 10.0f, RED);
}

void Entity::update() {
    position += velocity;
}

void Entity::move(float x, float y) {
    this->position.x += x;
    this->position.y += y;
}

bool Entity::isOffScreen() const {
    return position.x < 0.0f || position.x > screen_width || position.y < 0.0f || position.y > screen_height;
}

bool Entity::checkCollision(const std::shared_ptr<Entity> &other) {
    return (CheckCollisionCircles(Vector2{position.x, position.y}, size / 2.0f,
                                  Vector2{other->position.x, other->position.y}, other->size / 2.0f));
}
