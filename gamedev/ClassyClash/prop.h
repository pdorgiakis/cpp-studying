#include "raylib.h"

class Prop {
public:
  Prop(Vector2 position, Texture2D texture);

private:
  Texture2D texture{};
  Vector2 world_position{};
  float scale;
};
