
#include "includes/character.h"
#include "config.cpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

Character::Character() {
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
  screen_position = {(static_cast<float>(Config::window_width) / 2.0f) -
                         scale * (0.5f * width),
                     (static_cast<float>(Config::window_height) / 2.0f) -
                         scale * (0.5f * height)};
}

void Character::Tick(float delta_time) {
  previous_position = world_position;

  Vector2 direction{};
  if (IsKeyDown(KEY_RIGHT))
    direction.x -= 1;
  if (IsKeyDown(KEY_LEFT))
    direction.x += 1;
  if (IsKeyDown(KEY_UP))
    direction.y += 1;
  if (IsKeyDown(KEY_DOWN))
    direction.y -= 1;

  if (Vector2Length(direction) != 0) {
    world_position =
        Vector2Add(world_position, Vector2Scale(direction, movement_speed));

    // We don't use ternary because if the character moves up or down the x
    // results to 0 and the direction changes. We want the direction to change
    // only when the character "turns"
    if (direction.x > 0.f) {
      char_rotation = -1.f;
    } else if (direction.x < 0.f) {
      char_rotation = 1.f;
    }

    texture = run;
  } else {
    texture = idle;
  }

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

  Rectangle char_source_rectangle = {frame * width, 0, char_rotation * width,
                                     height};

  Rectangle char_dest_rectangle = {screen_position.x, screen_position.y,
                                   scale * width, height * scale};
  // Draw
  DrawTexturePro(texture, char_source_rectangle, char_dest_rectangle, Vector2{},
                 char_rotation, WHITE);
  DrawRectangleRec(collision_rec, RED);
}
