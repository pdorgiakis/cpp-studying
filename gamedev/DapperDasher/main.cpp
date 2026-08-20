#include "raylib.h"

struct Config {
  static const int window_width{800}, window_height{450};
  static const int h_height{50}, h_width{50};
  constexpr static const float h_init_pos_x{window_width / 2},
      h_init_pos_y{window_height - 50};
  // pixels per second per second
  static const int gravity{1000};
  // pixels per second
  constexpr static const float jump_velocity{-600.0f};
  int velocity{0};
};
Config config;

struct Scarfy {
  Texture2D scarfy_texture = LoadTexture("textures/scarfy.png");
  Rectangle scarfy_rec = {0, 0, float(scarfy_texture.width / 6),
                          float(scarfy_texture.height)};
  Vector2 scarfy_pos = {float(Config::window_width / 2 - scarfy_rec.width / 2),
                        float(Config::window_height - scarfy_rec.height)};
};

void DrawWindow() {
  InitWindow(config.window_width, config.window_height, "Dapper Dasher");
  SetTargetFPS(60);
}

bool IsTouchingTheGround(Scarfy *hero) {
  if (hero->scarfy_pos.y >= Config::window_height - hero->scarfy_rec.height) {
    return true;
  }

  return false;
}

void ControlHero(Scarfy *hero, float delta_time) {

  if (IsTouchingTheGround(hero)) {
    config.velocity = 0.0f;
  } else {
    config.velocity += config.gravity * delta_time;
  }

  if (IsKeyDown(KEY_SPACE) && IsTouchingTheGround(hero)) {
    config.velocity = config.jump_velocity;
  }

  hero->scarfy_pos.y += config.velocity * delta_time;
}

void GameLoop() {
  Scarfy scarfy;

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    ControlHero(&scarfy, dt);

    DrawTextureRec(scarfy.scarfy_texture, scarfy.scarfy_rec, scarfy.scarfy_pos,
                   WHITE);
    // Stop Drawing
    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(scarfy.scarfy_texture);
}

int main(void) {
  DrawWindow();
  GameLoop();
  CloseWindow();
  return 0;
}
