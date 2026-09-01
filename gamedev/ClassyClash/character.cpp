
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
  weapon = LoadTexture("./textures/characters/weapon_sword.png");
  padding = {4, 9};
  width = static_cast<float>(texture.width) / max_frames;
  height = texture.height;
  weapon_width = weapon.width * scale;
  weapon_height = weapon.height * scale;
}

void Character::Tick(float delta_time) {

  Vector2 direction{};
  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    direction.x -= 1;
  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    direction.x += 1;
  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    direction.y += 1;
  if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    direction.y -= 1;

  if (Vector2Length(direction) != 0) {
    world_position =
        Vector2Add(world_position, Vector2Scale(direction, movement_speed));

    // We don't use ternary because if the character moves up or down the x
    // results to 0 and the direction changes. We want the direction to change
    // only when the character "turns"
    if (direction.x > 0.f) {
      char_rotation = -1.f; // LEFT
    } else if (direction.x < 0.f) {
      char_rotation = 1.f; // RIGHT
    }

    texture = run;
  } else {
    texture = idle;
  }

  if (MovingRight()) {
    DrawWeapon();
    BaseCharacter::Tick(delta_time);
  } else if (MovingLeft()) {
    BaseCharacter::Tick(delta_time);
    DrawWeapon();
  } else {
    DrawWeapon();
    BaseCharacter::Tick(delta_time);
  }
}

Vector2 Character::GetScreenPosition() {
  return Vector2{(static_cast<float>(Config::window_width) / 2.0f) -
                     scale * (0.5f * width),
                 (static_cast<float>(Config::window_height) / 2.0f) -
                     scale * (0.5f * height)};
}

void Character::DrawWeapon() {
  float rotation{};
  Vector2 origin{};
  Vector2 offset{};
  // Moving Left
  if (MovingRight()) {
    origin = {0.f, weapon_height};
    offset = {25.f, 40.f};
    weapon_collision_rec = {GetScreenPosition().x + width + offset.x,
                            GetScreenPosition().y + offset.y + height -
                                weapon_height,
                            weapon_width, weapon_height};
    rotation = 35.f;
  } else if (MovingLeft()) {
    origin = {weapon_width, weapon_height};
    offset = {12.f, 40.f};
    weapon_collision_rec = {
        GetScreenPosition().x + width + offset.x - weapon_width,
        GetScreenPosition().y + offset.y + height - weapon_height, weapon_width,
        weapon_height};
    rotation = -35.f;
  }

  Rectangle weapon_source_rec = {0, 0, char_rotation * weapon.width,
                                 static_cast<float>(weapon.height)};

  Rectangle weapon_dest_rec = {GetScreenPosition().x + width + offset.x,
                               GetScreenPosition().y + offset.y + height,
                               weapon_width, weapon_height};

  DrawTexturePro(weapon, weapon_source_rec, weapon_dest_rec, origin, rotation,
                 WHITE);
  DrawRectangleLines(weapon_collision_rec.x, weapon_collision_rec.y,
                     weapon_collision_rec.width, weapon_collision_rec.height,
                     RED);
  // DrawRectanglePro(weapon_dest_rec, origin, 0.f, RED);
}

bool Character::MovingRight() {
  if (char_rotation > 0) {
    return true;
  }
  return false;
}

bool Character::MovingLeft() {
  if (char_rotation < 0) {
    return true;
  }
  return false;
}
