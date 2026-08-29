#pragma once

#include "raylib.h"

class Prop {
public:
  Prop(Vector2 position);
  void Render(Vector2 character_position);
  Rectangle GetCollisionRec() { return collision_rec; }
  void SetCollisionRec(Vector2 screen_position);

protected:
  float scale{4.f};
  Vector2 padding{};
  Rectangle collision_rec{};
  Texture2D texture{};
  Vector2 world_position{};
};
