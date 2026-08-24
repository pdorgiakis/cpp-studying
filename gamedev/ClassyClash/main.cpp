#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct Config {
  static const int window_width{384}, window_height{384};
  constexpr static const float movement_speed{5.0f};
  constexpr static const float map_scale{4.0f};
};

void SetupWindow() {
  InitWindow(Config::window_width, Config::window_height, "Classy Clash");
  SetTargetFPS(60);
}

Vector2 GetMapDirection() {
  Vector2 direction{};
  if (IsKeyDown(KEY_RIGHT))
    direction.x -= 1;
  if (IsKeyDown(KEY_LEFT))
    direction.x += 1;
  if (IsKeyDown(KEY_UP))
    direction.y += 1;
  if (IsKeyDown(KEY_DOWN))
    direction.y -= 1;

  return direction;
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
  Texture2D run_texture =
      LoadTexture("./textures/characters/knight_run_spritesheet.png");
  Texture2D idle_texture =
      LoadTexture("./textures/characters/knight_idle_spritesheet.png");

  Texture2D active_texture = idle_texture;
  Vector2 char_origin = {((float)Config::window_width / 2.0f) -
                             4.0f * (0.5f * run_texture.width / 6.0f),
                         ((float)Config::window_height / 2.0f) -
                             4.0f * (0.5f * run_texture.height)};

  // Facing right 1.0 - facing left -1.0
  float char_rotation{1.0};

  float update_time{1.0f / 12.0f};
  float running_time{};
  int frame{};
  int max_frames{6};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // Logic Start
    float dt = GetFrameTime();
    running_time += dt;

    Vector2 direction = GetMapDirection();
    if (Vector2Length(direction) != 0) {
      map_position = Vector2Add(
          map_position, Vector2Scale(direction, Config::movement_speed));

      map_position = Vector2Clamp(map_position, min_map_limit, max_map_limit);

      if (direction.x > 0.f) {
        char_rotation = -1.f;
      } else if (direction.x < 0.f) {
        char_rotation = 1.f;
      }

      active_texture = run_texture;
    } else {
      active_texture = idle_texture;
    }
    DrawTextureEx(map_texture, map_position, 0.0f, Config::map_scale, WHITE);

    if (update_time < running_time) {
      frame++;
      running_time = 0.0f;

      if (frame > max_frames)
        frame = 0;
    }

    Rectangle char_source_rectangle = {frame * (float)run_texture.width / 6, 0,
                                       char_rotation *
                                           (float)run_texture.width / 6,
                                       (float)run_texture.height};

    Rectangle char_dest_rectangle = {char_origin.x, char_origin.y,
                                     4.0f * (float)run_texture.width / 6,
                                     (float)run_texture.height * 4.0f};

    char_source_rectangle.x = (float)frame * (float)run_texture.width / 6.0f;
    DrawTexturePro(active_texture, char_source_rectangle, char_dest_rectangle,
                   Vector2{}, char_rotation, WHITE);

    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
