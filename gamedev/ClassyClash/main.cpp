#include "config.cpp"
#include "includes/character.h"
#include "includes/enemy.h"
#include "includes/rock.h"
#include "includes/tree.h"
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

  // Enemy Data
  Enemy goblin{Vector2{350.f, 300.f}};

  // Props
  Prop props[2]{Tree{Vector2{600.f, 300.f}}, Rock{Vector2{300.f, 600.f}}};

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
    float delta_time = GetFrameTime();
    knight.Tick(delta_time);
    goblin.Tick(delta_time, knight.GetWorldPosition());

    // Render Props
    for (auto prop : props) {
      prop.Render(knight.GetWorldPosition());

      bool collided =
          CheckCollisionRecs(prop.GetCollisionRec(), knight.GetCollisionRec());
      if (collided)
        knight.UndoMovement();
    }

    // Logic End
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
