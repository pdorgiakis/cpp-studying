#include "raylib.h"
#include "raymath.h"
#include <iostream>

struct Config {
  static const int window_width{384}, window_height{384};
};

void SetupWindow() {
  InitWindow(Config::window_width, Config::window_height, "Classy Clash");
  SetTargetFPS(60);
}

Vector2 GetMapDirection() {
  Vector2 direction{};
  if (IsKeyDown(KEY_RIGHT))
    direction.x -= 10;
  if (IsKeyDown(KEY_LEFT))
    direction.x += 10;
  if (IsKeyDown(KEY_UP))
    direction.y += 10;
  if (IsKeyDown(KEY_DOWN))
    direction.y -= 10;

  return direction;
}

void GameLoop() {
  // Map Data
  Texture2D map_texture = LoadTexture("./textures/map.png");
  Vector2 map_position = {0, 0};
  Vector2 min_map_limit = {Config::window_width - map_texture.width * 4.0f,
                           Config::window_height - map_texture.height * 4.0f};
  Vector2 max_map_limit = {0, 0};
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // Logic Start
    float dt = GetFrameTime();
    Vector2 direction = GetMapDirection();
    if (Vector2Length(direction) != 0) {
      map_position = Vector2Add(map_position, direction);
      map_position = Vector2Clamp(map_position, min_map_limit, max_map_limit);
    }
    DrawTextureEx(map_texture, map_position, 0.0f, 4.0f, WHITE);
    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
