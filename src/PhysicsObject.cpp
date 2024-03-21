
#include "PhysicsObject.hpp"

PhysicsObject::PhysicsObject(float x, float y, float size) : Entity(x, y, size) {
    max_speed = 20.0f;
    friction = 0.05f;
}

void PhysicsObject::update() {
    Entity::update();
}

void PhysicsObject::accelerate(raylib::Vector2 acceleration) {
    float dt = 1.0f / 60.0f;
    velocity += acceleration * dt;
    velocity -= velocity * friction;

    float speed = velocity.Length();
    if (speed > max_speed) {
        velocity *= max_speed / speed;
    }

    position += velocity;
}
