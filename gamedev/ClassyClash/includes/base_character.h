#include "raylib.h"
#pragma once

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
class BaseCharacter {
public:
  BaseCharacter();
  Vector2 GetWorldPosition() { return world_position; }
  virtual Vector2 GetScreenPosition() = 0;
  Rectangle GetCollisionRec() { return collision_rec; }
  void SetWorldPosition(Vector2 position) { world_position = position; }
  void UndoMovement() { world_position = previous_position; }
  virtual void Tick(float delta_time);
  void SetIsAlive(bool alive) { is_alive = alive; }
  virtual void Hit(float damage);
  float GetDamageDealt() { return damage; }

protected:
  Texture2D idle{};
  Texture2D run{};
  Texture2D texture{};
  Vector2 previous_position{};
  Vector2 world_position{};
  Vector2 padding{};
  Rectangle collision_rec{};

  const float scale{4.f};
  const float update_time{1.0f / 12.0f};
  const int max_frames{6};

  float movement_speed{4.f};
  // Facing right 1.0 - facing left -1.0
  float char_rotation{1.0};
  float running_time{};
  int frame{};
  float width{};
  float height{};
  bool is_alive{true};
  float max_health;
  float current_health;
  float damage{10.f};
  float invulnerability_time{0.f};
  float time_since_last_hit{0.f};
};
#endif
