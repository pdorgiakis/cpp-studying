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
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // Logic Start
    float dt = GetFrameTime();

    Vector2 direction = GetMapDirection();
    if (Vector2Length(direction) != 0) {
      map_position = Vector2Add(
          map_position, Vector2Scale(direction, Config::movement_speed));

      map_position = Vector2Clamp(map_position, min_map_limit, max_map_limit);
    }
    DrawTextureEx(map_texture, map_position, 0.0f, Config::map_scale, WHITE);
    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
