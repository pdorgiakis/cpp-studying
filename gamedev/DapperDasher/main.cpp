#include "raylib.h"

struct Config {
  static const int window_width{800}, window_height{450};
  static const int h_height{50}, h_width{50};
  constexpr static const float h_init_pos_x{window_width / 2},
      h_init_pos_y{window_height - 50};
  static const int jump_height{200};
  int velocity{0};
};
Config config;

void DrawWindow() {
  InitWindow(config.window_width, config.window_height, "Dapper Dasher");
  SetTargetFPS(60);
}

bool IsTouchingTheGround(Rectangle *hero) {
  if (hero->y >= Config::window_height - hero->height) {
    return true;
  }

  return false;
}

void ControlHero(Rectangle *hero) {
  hero->y -= config.velocity;

  if (hero->y < Config::window_height - Config::jump_height) {
    config.velocity = -config.velocity;
  }

  if (hero->y > config.window_height - 50.0f) {
    config.velocity = 0.0f;
    hero->y = config.window_height - 50.0f;
  }
  if (IsKeyDown(KEY_SPACE) && IsTouchingTheGround(hero)) {
    config.velocity = 10.0f;
  }
}

void GameLoop() {
  Rectangle hero =
      (Rectangle){Config::h_init_pos_x, Config::h_init_pos_y, 50, 50};

  while (!WindowShouldClose()) {
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    ControlHero(&hero);

    DrawRectangleRec(hero, RED);
    // Stop Drawing
    EndDrawing();
  }
  CloseWindow();
}

int main(void) {
  DrawWindow();
  GameLoop();
  CloseWindow();
  return 0;
}
