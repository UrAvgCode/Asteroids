#include "Asteroid.hpp"

Asteroid::Asteroid(float x, float y, float angle, float size) : Entity(x, y, size) {
    this->rotation = angle;

    speed = 5;

    velocity.x = (float) sin(angle * (M_PI / 180)) * speed;
    velocity.y = (float) -cos(angle * (M_PI / 180)) * speed;

    texture = raylib::Texture("res/asteroid.png");

    float scale = size / (float) texture.GetWidth();
    texture.SetWidth((int) size);
    texture.SetHeight((int) ((float) texture.GetHeight() * scale));
}

void Asteroid::draw() const {
    auto width = (float) texture.GetWidth();
    auto height = (float) texture.GetHeight();
    raylib::Rectangle source(0, 0, width, height);
    raylib::Rectangle dest(position.x, position.y, width, height);
    DrawTexturePro(texture, source, dest, Vector2{width / 2, height / 2}, 0,WHITE);
}

std::shared_ptr<Asteroid> Asteroid::split() const {
    float splitAngle = rotation + (float) GetRandomValue(-45, 45);
    return std::make_shared<Asteroid>(position.x, position.y, splitAngle, size / 1.5f);
}

bool Asteroid::canSplit() const {
    return size > 100;
}