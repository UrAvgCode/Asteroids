#include "Player.hpp"

#include <iostream>

Player::Player(float x, float y) : PhysicsObject(x, y, 100.0f) {
    angleSpeed = 0;
    speed = 15;

    thrust = 100;

    shootTimer = 0;

    for (int i = 0; i < 8; i++) {
        animation[i] = raylib::Texture("res/spaceship/spaceship_" + std::to_string(i) + ".png");
    }


    for (auto &animationFrame: animation) {
        int textureSize = 150;
        float ratio = (float) animationFrame.GetWidth() / (float) animationFrame.GetHeight();

        animationFrame.SetHeight(textureSize);
        animationFrame.SetWidth((int) ((float) textureSize * ratio));
        animationFrame.SetFilter(TEXTURE_FILTER_TRILINEAR);
    }
}

void Player::draw() const {
    int i = (frame / 2) % 8;
    raylib::Rectangle source(0, 0, (float) animation[i].GetWidth(), (float) animation[i].GetHeight());
    raylib::Rectangle dest((float) position.x, (float) position.y, (float) animation[i].GetWidth(),
                           (float) animation[i].GetHeight());
    DrawTexturePro(animation[i], source, dest,
                   Vector2{(float) animation[i].GetWidth() / 2, (float) animation[i].GetHeight() / 2}, rotation, WHITE);
}

void Player::update() {
    if (IsKeyDown(KEY_D))
        angleSpeed += 0.3;
    if (IsKeyDown(KEY_A))
        angleSpeed -= 0.3;

    if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        angleSpeed = approach(angleSpeed, 0, 0.4);

    if (angleSpeed > 5)
        angleSpeed = 5;
    if (angleSpeed < -5)
        angleSpeed = -5;

    raylib::Vector2 acceleration(0.0f, 0.0f);
    if (IsKeyDown(KEY_W)) {
        accelerate(raylib::Vector2{0.f, -thrust}.Rotate(DEG2RAD * rotation));
    } else {
        accelerate(acceleration);
    }

    rotation += angleSpeed;

    float screenWidth = 3840;
    float screenHeight = 2160;
    if (position.x > screenWidth)
        position.x = 0;
    if (position.x < 0)
        position.x = screenWidth;
    if (position.y > screenHeight)
        position.y = 0;
    if (position.y < 0)
        position.y = screenHeight;

    if (shootTimer > 0)
        shootTimer--;

    frame++;
}

bool Player::canShoot() const {
    return shootTimer <= 0;
}

Bullet *Player::shoot() {
    shootTimer = 10;

    float bulletX = position.x + (float) (sin(rotation * (M_PI / 180)) * animation[0].GetWidth() * 0.32);
    float bulletY = position.y - (float) (cos(rotation * (M_PI / 180)) * animation[0].GetWidth() * 0.32);

    return new Bullet(bulletX, bulletY, rotation);
}

float Player::approach(float value, float goal, float step) {
    if (value < goal && value + step < goal) {
        value += step;
    } else if (value > goal && value - step > goal) {
        value -= step;
    } else {
        value = goal;
    }
    return value;
}