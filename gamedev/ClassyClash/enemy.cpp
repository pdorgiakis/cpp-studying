#include "includes/enemy.h"
#include "config.cpp"
#include "includes/base_character.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

Enemy::Enemy(Vector2 position) {
  SetWorldPosition(position);
  idle = LoadTexture("./textures/characters/goblin_idle_spritesheet.png");
  run = LoadTexture("./textures/characters/goblin_run_spritesheet.png");
  texture = idle;
  padding = {4, 3};
  movement_speed = 6.0f;
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
}

void Enemy::Tick(float delta_time) { BaseCharacter::Tick(delta_time); }

void Enemy::SetScreenPosition(Vector2 character_position) {
  screen_position = Vector2Add(world_position, character_position);
}
