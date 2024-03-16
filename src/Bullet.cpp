#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float angle) : Entity(x, y, 10.0f) {
    this->rotation = angle;

    speed = 23;

    texture = raylib::Texture("res/laser.png");

    velocity.x = (float) sin(angle * (M_PI / 180)) * speed;
    velocity.y = (float) -cos(angle * (M_PI / 180)) * speed;
}

void Bullet::draw() const {
    raylib::Rectangle source(0, 0, (float) texture.GetWidth(), (float) texture.GetHeight());
    raylib::Rectangle dest((float) position.x, (float) position.y, (float) texture.GetWidth(), (float) texture.GetHeight());
    DrawTexturePro(texture, source, dest, Vector2{(float) texture.GetWidth() / 2, (float) texture.GetHeight() / 2},
                   (float) rotation, WHITE);
}