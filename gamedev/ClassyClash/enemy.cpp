#include "includes/enemy.h"
#include "config.cpp"
#include "includes/base_character.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>

Enemy::Enemy(Vector2 position) {
  SetWorldPosition(position);
  idle = LoadTexture("./textures/characters/goblin_idle_spritesheet.png");
  run = LoadTexture("./textures/characters/goblin_run_spritesheet.png");
  texture = idle;
  padding = {4, 3};
  movement_speed = 2.0f;
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
}

void Enemy::Tick(float delta_time) {

  if (!is_alive) {
    return;
  }

  if (target != nullptr) {
    if (Vector2Distance(target->GetScreenPosition(), GetScreenPosition()) <=
        300)
      aggroed = true;
    else
      aggroed = false;
  }

  if (aggroed) {
    texture = run;

    Vector2 towards_target = Vector2Normalize(
        Vector2Subtract(target->GetScreenPosition(), GetScreenPosition()));

    world_position = Vector2Add(world_position,
                                Vector2Scale(towards_target, movement_speed));
  }

  BaseCharacter::Tick(delta_time);
}

Vector2 Enemy::GetScreenPosition() {
  return Vector2Add(world_position, target->GetWorldPosition());
}
