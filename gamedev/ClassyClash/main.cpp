#include "character.h"
#include "config.cpp"
#include "raylib.h"
#include <iostream>

void SetupWindow() {
  InitWindow(Config::window_width, Config::window_height, "Classy Clash");
  SetTargetFPS(60);
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
