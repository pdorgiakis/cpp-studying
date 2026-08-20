#include "raylib.h"

void build_window(int *window_width, int *window_height) {
  InitWindow(*window_width, *window_height, "Axe Game");
  SetTargetFPS(60);
}

Rectangle circle_edges(Vector2 *circle_position, int *circle_radius) {
  // x is left, y is right, z top, w is bottom
  Rectangle circle_edges =
      (Rectangle){float(circle_position->x - *circle_radius),
                  float(circle_position->y - *circle_radius),
                  float(*circle_radius * 2), float(*circle_radius * 2)};

  return circle_edges;
}

Rectangle axe_edges(Vector2 *axe_position, int *axe_length) {
  // x is upper left, y is upper right, z is bottom left, w is bottom right
  Rectangle axe_edges = (Rectangle){
      float(axe_position->x),
      float(axe_position->y),
      float(*axe_length),
      float(*axe_length),
  };

  return axe_edges;
}

void draw_window(int *window_width, int *window_height) {
  Vector2 circle_position =
      (Vector2){float(*window_width / 3), float(*window_height / 3)};
  int circle_radius = 25;

  int axe_length = 50;
  Vector2 axe_position =
      (Vector2){float(*window_width / 2), float(*window_height / 2)};

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) &&
        circle_position.y < *window_height - circle_radius) {
      circle_position.y++;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && circle_position.y > 0) {
      circle_position.y--;
    }

    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && circle_position.x > 0) {
      circle_position.x--;
    }
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) &&
        circle_position.x < *window_width) {
      circle_position.x++;
    }
    // DrawRectangleRec(circle_edges(&circle_position, &circle_radius),
    // MAGENTA); DrawRectangleRec(axe_edges(&axe_position, &axe_length),
    // MAGENTA);
    DrawCircle(circle_position.x, circle_position.y, circle_radius, GOLD);
    DrawRectangle(axe_position.x, axe_position.y, axe_length, axe_length, RED);

    if (CheckCollisionRecs(circle_edges(&circle_position, &circle_radius),
                           axe_edges(&axe_position, &axe_length))) {
      DrawText("You hit the axe!", 400, 200, 20, RED);
    }
    EndDrawing();
  }
}

int main(void) {
  int window_width{800};
  int window_height{540};

  build_window(&window_width, &window_height);
  draw_window(&window_width, &window_height);

  CloseWindow();
  return 0;
}
