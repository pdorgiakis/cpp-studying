#include "includes/prop.h"
#include "config.cpp"
#include "raylib.h"
#include "raymath.h"

// TODO: make props a base class for all props
Prop::Prop(Vector2 position) : world_position(position) {}

void Prop::Render(Vector2 character_position) {
  Vector2 screen_position = Vector2Add(world_position, character_position);

  collision_rec = {screen_position.x + padding.x * scale,
                   screen_position.y + padding.y * scale,
                   texture.width * scale - padding.x * 2 * scale,
                   texture.height * scale - padding.y * scale};

  DrawTextureEx(texture, screen_position, 0.0f, scale, WHITE);
  // DrawRectangleRec(collision_rec, RED);
}
