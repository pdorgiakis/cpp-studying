#include "prop.h"
#include "raylib.h"
#include "raymath.h"

Prop::Prop(Vector2 position, Texture2D texture)
    : world_position(position), texture(texture) {}

void Prop::Render(Vector2 character_position) {
  Vector2 screen_position = Vector2Add(world_position, character_position);

  DrawTextureEx(texture, screen_position, 0.0f, scale, WHITE);
}
