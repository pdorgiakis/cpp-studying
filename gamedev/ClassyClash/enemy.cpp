#include "includes/enemy.h"
#include "config.cpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

Enemy::Enemy(Vector2 position) : world_position(position) {
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
}

void Enemy::Tick(float delta_time, Vector2 character_position) {
  previous_position = world_position;

  Vector2 screen_position = Vector2Add(world_position, character_position);

  collision_rec = {screen_position.x + padding.x * scale,
                   screen_position.y + padding.y * scale,
                   (width - padding.x * 2) * scale,
                   (height - padding.y) * scale};

  // Animate
  running_time += delta_time;
  if (update_time < running_time) {
    frame++;
    running_time = 0.0f;

    if (frame > max_frames)
      frame = 0;
  }

  Rectangle source_rectangle = {frame * width, 0, char_rotation * width,
                                height};

  Rectangle dest_rectangle = {screen_position.x, screen_position.y,
                              scale * width, height * scale};

  DrawTexturePro(texture, source_rectangle, dest_rectangle, Vector2{},
                 char_rotation, WHITE);
  // DrawRectangleRec(collision_rec, RED);
}
