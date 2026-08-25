#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct Config {
  static const int window_width{384}, window_height{384};
  constexpr static const float map_scale{4.0f};
};

void SetupWindow() {
  InitWindow(Config::window_width, Config::window_height, "Classy Clash");
  SetTargetFPS(60);
}

class Character {
public:
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
};

void Character::SetScreenPosition() {
  screen_position = {((float)Config::window_width / 2.0f) -
                         4.0f * (0.5f * texture.width / 6.0f),
                     ((float)Config::window_height / 2.0f) -
                         4.0f * (0.5f * texture.height)};
}

void Character::Tick(float delta_time) {
  Vector2 direction{};
  if (IsKeyDown(KEY_RIGHT))
    direction.x -= 1;
  if (IsKeyDown(KEY_LEFT))
    direction.x += 1;
  if (IsKeyDown(KEY_UP))
    direction.y += 1;
  if (IsKeyDown(KEY_DOWN))
    direction.y -= 1;

  if (Vector2Length(direction) != 0) {
    world_position =
        Vector2Add(world_position, Vector2Scale(direction, movement_speed));

    // world_position = Vector2Clamp(world_position, min_map_limit,
    // max_map_limit);

    if (direction.x > 0.f) {
      char_rotation = -1.f;
    } else if (direction.x < 0.f) {
      char_rotation = 1.f;
    }

    texture = run;
  } else {
    texture = idle;
  }

  // Animation
  running_time += delta_time;
  if (update_time < running_time) {
    frame++;
    running_time = 0.0f;

    if (frame > max_frames)
      frame = 0;
  }

  SetScreenPosition();
  Rectangle char_source_rectangle = {frame * (float)texture.width / 6, 0,
                                     char_rotation * (float)texture.width / 6,
                                     (float)texture.height};

  Rectangle char_dest_rectangle = {screen_position.x, screen_position.y,
                                   4.0f * (float)texture.width / 6,
                                   (float)texture.height * 4.0f};

  char_source_rectangle.x = (float)frame * (float)texture.width / 6.0f;
  DrawTexturePro(texture, char_source_rectangle, char_dest_rectangle, Vector2{},
                 char_rotation, WHITE);
}

void GameLoop() {
  // Map Data
  Texture2D map_texture = LoadTexture("./textures/map.png");
  Vector2 map_position = {0, 0};
  Vector2 min_map_limit = {
      Config::window_width - map_texture.width * Config::map_scale,
      Config::window_height - map_texture.height * Config::map_scale};
  Vector2 max_map_limit = {0, 0};

  // Character Data
  Character knight;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // Logic Start
    // Draw map
    DrawTextureEx(map_texture, knight.GetWorldPosition(), 0.0f,
                  Config::map_scale, WHITE);
    // Tick Hero
    knight.Tick(GetFrameTime());

    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
