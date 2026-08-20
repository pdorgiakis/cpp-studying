#include "raylib.h"

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
