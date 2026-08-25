#include "raylib.h"

class Character {
public:
  Character();
  Vector2 GetWorldPosition() { return world_position; }
  void SetScreenPosition();
  void Tick(float delta_time);

private:
  Texture2D idle{
      LoadTexture("./textures/characters/knight_idle_spritesheet.png")};
  Texture2D run{
      LoadTexture("./textures/characters/knight_run_spritesheet.png")};
  Texture2D texture{idle};
  Vector2 world_position{};
  Vector2 screen_position{};
  const float movement_speed{4.0f};
  const float update_time{1.0f / 12.0f};
  const int max_frames{6};
  // Facing right 1.0 - facing left -1.0
  float char_rotation{1.0};
  float running_time{};
  int frame{};
  float width{};
  float height{};
};
