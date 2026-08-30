
#include "includes/character.h"
#include "config.cpp"
#include "includes/base_character.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

Character::Character() {
  idle = LoadTexture("./textures/characters/knight_idle_spritesheet.png");
  run = LoadTexture("./textures/characters/knight_run_spritesheet.png");
  texture = idle;
  padding = {4, 9};
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
  screen_position = {(static_cast<float>(Config::window_width) / 2.0f) -
                         scale * (0.5f * width),
                     (static_cast<float>(Config::window_height) / 2.0f) -
                         scale * (0.5f * height)};
}

void Character::Tick(float delta_time) {
  BaseCharacter::Tick(delta_time);

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
}
