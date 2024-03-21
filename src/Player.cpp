#include "Player.hpp"

#include <cmath>
#include <string>
#include <vector>

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
    std::string filename = "spaceship_" + std::to_string(i) + ".png";
    animation[i] = raylib::Texture("res/spaceship/" + filename);
  }

  float texture_width = static_cast<float>(animation[0].width);
  float texture_height = static_cast<float>(animation[0].height);
  float ratio = texture_width / texture_height;
  float target_size = 150.0f;

  int height = static_cast<int>(target_size);
  int width = static_cast<int>(target_size * ratio);

  for (auto& animation_frame : animation) {
    animation_frame.SetWidth(width);
    animation_frame.SetHeight(height);
    animation_frame.SetFilter(TEXTURE_FILTER_TRILINEAR);
  }
}

void Player::draw() const {
  int index = (frame / 2) % animation_frame_count;
  float width = static_cast<float>(animation[index].width);
  float height = static_cast<float>(animation[index].height);

  raylib::Rectangle source(0, 0, width, height);
  raylib::Rectangle dest(position.x, position.y, width, height);
  raylib::Vector2 origin(width / 2, height / 2);
  DrawTexturePro(animation[index], source, dest, origin, rotation, WHITE);
}

void Player::update() {
  if (IsKeyDown(KEY_D)) {
    angle_speed += 0.3;
  }

  if (IsKeyDown(KEY_A)) {
    angle_speed -= 0.3;
  }

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

  float offset = static_cast<float>(animation[0].width) * 0.32f;
  float offset_x = std::sin(DEG2RAD * rotation) * offset;
  float offset_y = std::cos(DEG2RAD * rotation) * offset;

  float bullet_x = position.x + offset_x;
  float bullet_y = position.y - offset_y;

  return std::make_shared<Bullet>(bullet_x, bullet_y, rotation);
}

float Player::approach(float value, float goal, float step) {
  if (value < goal) {
    return std::min(value + step, goal);
  } else {
    return std::max(value - step, goal);
  }
}