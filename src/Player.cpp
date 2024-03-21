#include "../include/Player.hpp"

#include <iostream>

const int screen_width = 3840;
const int screen_height = 2160;
const int animation_frame_count = 8;
const float max_angle_speed = 5.0f;

Player::Player(float x, float y) : PhysicsObject(x, y, 100.0f) {
    angle_speed = 0.0f;
    speed = 15.0f;
    thrust = 100.0f;
    shoot_timer = 0;

    for (int i = 0; i < animation_frame_count; i++) {
        animation[i] = raylib::Texture("res/spaceship/spaceship_" + std::to_string(i) + ".png");
        int texture_size = 150;
        float ratio = static_cast<float>(animation[i].width) / static_cast<float>(animation[i].height);

        animation[i].SetHeight(texture_size);
        animation[i].SetWidth(static_cast<int>(static_cast<float>(texture_size) * ratio));
        animation[i].SetFilter(TEXTURE_FILTER_TRILINEAR);
    }
}

void Player::draw() const {
    int i = (frame / 2) % animation_frame_count;
    auto width = static_cast<float>(animation[i].width);
    auto height = static_cast<float>(animation[i].height);
    raylib::Rectangle source(0, 0, width, height);
    raylib::Rectangle dest(position.x, position.y, width, height);
    DrawTexturePro(animation[i], source, dest, Vector2{width / 2, height / 2}, rotation, WHITE);
}

void Player::update() {
    if (IsKeyDown(KEY_D))
        angle_speed += 0.3;
    if (IsKeyDown(KEY_A))
        angle_speed -= 0.3;

    if (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
        angle_speed = approach(angle_speed, 0, 0.4);

    if (angle_speed > max_angle_speed) {
        angle_speed = max_angle_speed;
    } else if (angle_speed < -max_angle_speed) {
        angle_speed = -max_angle_speed;
    }

    raylib::Vector2 acceleration(0.0f, 0.0f);
    if (IsKeyDown(KEY_W)) {
        accelerate(raylib::Vector2{0.f, -thrust}.Rotate(DEG2RAD * rotation));
    } else {
        accelerate(acceleration);
    }

    rotation += angle_speed;

    if (position.x > screen_width) {
        position.x -= screen_width;
    } else if (position.x < 0.0f) {
        position.x += screen_width;
    }
        
    if (position.y > screen_height) {
        position.y -= screen_height;
    } else if (position.y < 0.0f) {
        position.y += screen_height;
    }

    if (shoot_timer > 0) {
        shoot_timer--;
    }

    frame++;
}

bool Player::canShoot() const {
    return shoot_timer <= 0;
}

std::shared_ptr<Bullet> Player::shoot() {
    shoot_timer = 10;

    float bullet_x = position.x + static_cast<float>(std::sin(rotation * (M_PI / 180.0f)) * animation[0].width * 0.32f);
    float bullet_y = position.y - static_cast<float>(std::cos(rotation * (M_PI / 180.0f)) * animation[0].height * 0.32f);

    return std::make_shared<Bullet>(bullet_x, bullet_y, rotation);
}

float Player::approach(float value, float goal, float step) {
    if (value < goal) {
        return std::min(value + step, goal);
    } else {
        return std::max(value - step, goal);
    }
}