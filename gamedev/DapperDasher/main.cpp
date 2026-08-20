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

void DrawWindow(int width, int height) {
  SetTargetFPS(60);
  InitWindow(width, height, "Dapper Dasher");
}

void GameLoop(int width, int height) {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
  CloseWindow();
}

int main(void) {
  const int window_width{800}, window_height{450};

  DrawWindow(window_width, window_height);
  GameLoop(window_width, window_height);
  CloseWindow();
  return 0;
}
