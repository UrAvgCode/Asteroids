#include "../include/Asteroid.hpp"

Asteroid::Asteroid(float x, float y, float angle, float size) : Entity(x, y, size) {
    this->rotation = angle;

    speed = 5.0f;

    velocity.x = static_cast<float>(std::sin(angle * (M_PI / 180.0f)) * speed);
    velocity.y = static_cast<float>(-std::cos(angle * (M_PI / 180.0f)) * speed);

    texture = raylib::Texture("res/asteroid.png");

    float scale = size / static_cast<float>(texture.GetWidth());
    texture.SetWidth(static_cast<int>(size));
    texture.SetHeight(static_cast<int>(static_cast<float>(texture.GetHeight()) * scale));
}

void Asteroid::draw() const {
    auto width = static_cast<float>(texture.width);
    auto height = static_cast<float>(texture.height);
    raylib::Rectangle source(0.0f, 0.0f, width, height);
    raylib::Rectangle dest(position.x, position.y, width, height);
    DrawTexturePro(texture, source, dest, Vector2{width / 2.0f, height / 2.0f}, 0.0f, WHITE);
}

std::shared_ptr<Asteroid> Asteroid::split() const {
    float splitAngle = rotation + static_cast<float>(GetRandomValue(-45, 45));
    return std::make_shared<Asteroid>(position.x, position.y, splitAngle, size / 1.5f);
}

bool Asteroid::canSplit() const {
    return size > 100.0f;
}