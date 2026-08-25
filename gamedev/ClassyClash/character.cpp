
#include "character.h"
#include "config.cpp"
#include "raylib.h"
#include "raymath.h"

Character::Character() {
  width = (float)texture.width / max_frames;
  height = texture.height;
}

void Character::SetScreenPosition() {
  screen_position = {
      ((float)Config::window_width / 2.0f) - 4.0f * (0.5f * width),
      ((float)Config::window_height / 2.0f) - 4.0f * (0.5f * height)};
}

void Character::Tick(float delta_time) {
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

    // world_position = Vector2Clamp(world_position, min_map_limit,
    // max_map_limit);

    if (direction.x > 0.f) {
      char_rotation = -1.f;
    } else if (direction.x < 0.f) {
      char_rotation = 1.f;
    }

    texture = run;
  } else {
    texture = idle;
  }

  // Animation
  running_time += delta_time;
  if (update_time < running_time) {
    frame++;
    running_time = 0.0f;

    if (frame > max_frames)
      frame = 0;
  }

  SetScreenPosition();
  Rectangle char_source_rectangle = {frame * (float)texture.width / 6, 0,
                                     char_rotation * width, height};

  Rectangle char_dest_rectangle = {screen_position.x, screen_position.y,
                                   4.0f * width, height * 4.0f};

  char_source_rectangle.x = (float)frame * (float)texture.width / 6.0f;
  DrawTexturePro(texture, char_source_rectangle, char_dest_rectangle, Vector2{},
                 char_rotation, WHITE);
}
