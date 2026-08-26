#include "raylib.h"

class Prop {
public:
  Prop(Vector2 position, Texture2D texture);
  void Render(Vector2 character_position);

private:
  Vector2 world_position{};
  Texture2D texture{};
  float scale{4.f};
};
