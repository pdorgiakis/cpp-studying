#include "character.h"
#include "config.cpp"
#include "prop.h"
#include "raylib.h"
#include "raymath.h"
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

  // Props
  Texture2D bush_texture = LoadTexture("./textures/nature_tileset/Bush.png");
  Vector2 world_position = {0, 0};
  // {Config::map_scale * map_texture.width / 2,
  //                         Config::map_scale * map_texture.height / 2};
  Prop bush = {world_position, bush_texture};
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    // Logic Start
    // // Set World Bounds
    knight.SetWorldPosition(
        Vector2Clamp(knight.GetWorldPosition(), min_map_limit, max_map_limit));

    // Draw map
    DrawTextureEx(map_texture, knight.GetWorldPosition(), 0.0f,
                  Config::map_scale, WHITE);
    // Tick Hero
    knight.Tick(GetFrameTime());

    // Render Props
    bush.Render(knight.GetWorldPosition());

    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
