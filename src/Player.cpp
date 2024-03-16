#include "Player.hpp"

#include <iostream>

const int SCREEN_WIDTH = 3840;
const int SCREEN_HEIGHT = 2160;
const int ANIMATION_FRAMES = 8;
const int MAX_ANGLE_SPEED = 5;

Player::Player(float x, float y) : PhysicsObject(x, y, 100.0f) {
    angleSpeed = 0;
    speed = 15;
    thrust = 100;
    shootTimer = 0;

    for (int i = 0; i < ANIMATION_FRAMES; i++) {
        animation[i] = raylib::Texture("res/spaceship/spaceship_" + std::to_string(i) + ".png");
        int textureSize = 150;
        float ratio = (float) animation[i].GetWidth() / (float) animation[i].GetHeight();

        animation[i].SetHeight(textureSize);
        animation[i].SetWidth((int) ((float) textureSize * ratio));
        animation[i].SetFilter(TEXTURE_FILTER_TRILINEAR);
    }
}

void Player::draw() const {
    int i = (frame / 2) % ANIMATION_FRAMES;
    auto width = (float) animation[i].GetWidth();
    auto height = (float) animation[i].GetHeight();
    raylib::Rectangle source(0, 0, width, height);
    raylib::Rectangle dest((float) position.x, (float) position.y, width, height);
    DrawTexturePro(animation[i], source, dest, Vector2{width / 2, height / 2}, rotation, WHITE);
}

void Player::update() {
    if (IsKeyDown(KEY_D))
        angleSpeed += 0.3;
    if (IsKeyDown(KEY_A))
        angleSpeed -= 0.3;

    if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        angleSpeed = approach(angleSpeed, 0, 0.4);

    if (angleSpeed > MAX_ANGLE_SPEED)
        angleSpeed = MAX_ANGLE_SPEED;
    if (angleSpeed < -MAX_ANGLE_SPEED)
        angleSpeed = -MAX_ANGLE_SPEED;

    raylib::Vector2 acceleration(0.0f, 0.0f);
    if (IsKeyDown(KEY_W)) {
        accelerate(raylib::Vector2{0.f, -thrust}.Rotate(DEG2RAD * rotation));
    } else {
        accelerate(acceleration);
    }

    rotation += angleSpeed;

    if (position.x > SCREEN_WIDTH)
        position.x = 0;
    if (position.x < 0)
        position.x = SCREEN_WIDTH;
    if (position.y > SCREEN_HEIGHT)
        position.y = 0;
    if (position.y < 0)
        position.y = SCREEN_HEIGHT;

    if (shootTimer > 0)
        shootTimer--;

    frame++;
}

bool Player::canShoot() const {
    return shootTimer <= 0;
}

std::shared_ptr<Bullet> Player::shoot() {
    shootTimer = 10;

    float bulletX = position.x + (float) (sin(rotation * (M_PI / 180)) * animation[0].GetWidth() * 0.32);
    float bulletY = position.y - (float) (cos(rotation * (M_PI / 180)) * animation[0].GetWidth() * 0.32);

    return std::make_shared<Bullet>(bulletX, bulletY, rotation);
}

float Player::approach(float value, float goal, float step) {
    if (value < goal) {
        return std::min(value + step, goal);
    } else {
        return std::max(value - step, goal);
    }
}