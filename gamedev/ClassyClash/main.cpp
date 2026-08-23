#include "raylib.h"
struct Config {
  static const int window_width{384}, window_height{384};
};

void SetupWindow() {
  InitWindow(Config::window_width, Config::window_height, "Classy Clash");
  SetTargetFPS(60);
}

void GameLoop() {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);
    EndDrawing();
  }
}

int main() {
  SetupWindow();

  GameLoop();
  return 0;
}
