#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float angle) : Entity(x, y, 10.0f) {
    this->rotation = angle;

    speed = 23.0f;

    texture = raylib::Texture("res/laser.png");

    velocity.x = static_cast<float>(std::sin(angle * (M_PI / 180.0f)) * speed);
    velocity.y = static_cast<float>(-std::cos(angle * (M_PI / 180.0f)) * speed);
}

void Bullet::draw() const {
    auto width = static_cast<float>(texture.width);
    auto height = static_cast<float>(texture.height);

    raylib::Rectangle source(0.0f, 0.0f, width, height);
    raylib::Rectangle dest(position.x, position.y, width, height);
    DrawTexturePro(texture, source, dest, Vector2{width / 2.0f, height / 2.0f}, rotation, WHITE);
}