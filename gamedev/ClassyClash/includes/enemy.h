#include "raylib.h"

class Enemy {
public:
  Enemy(Vector2 position);
  Vector2 GetWorldPosition() { return world_position; }
  void SetWorldPosition(Vector2 position) { world_position = position; }
  void Tick(float delta_time, Vector2 character_position);
  Rectangle GetCollisionRec() { return collision_rec; }
  void UndoMovement() { world_position = previous_position; }

private:
  Texture2D idle{
      LoadTexture("./textures/characters/goblin_idle_spritesheet.png")};
  Texture2D run{
      LoadTexture("./textures/characters/goblin_run_spritesheet.png")};
  Texture2D texture{idle};
  Vector2 previous_position{};
  Vector2 world_position{};
  Vector2 screen_position{};
  Vector2 padding{4, 3};
  Rectangle collision_rec{};

  const float scale{4.f};
  const float movement_speed{6.0f};
  const float update_time{1.0f / 12.0f};
  const int max_frames{6};
  // Facing right 1.0 - facing left -1.0
  float char_rotation{1.0};
  float running_time{};
  int frame{};
  float width{};
  float height{};
};
