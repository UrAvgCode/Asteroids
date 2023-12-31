#include "Entity.hpp"

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
    return position.x < 0 || position.x > (float) GetScreenWidth() || position.y < 0 || position.y > (float) GetScreenHeight();
}

bool Entity::checkCollision(Entity *other) {
    return (CheckCollisionCircles(Vector2{(float) position.x, (float) position.y}, size / 2.0f,
                                  Vector2{(float) other->position.x, (float) other->position.y}, other->size / 2.0f));
}
