#include "raylib.h"
#include <iostream>

struct Config {
  static const int window_width{800}, window_height{450};
  static const int h_height{50}, h_width{50};
  constexpr static const float h_init_pos_x{window_width / 2},
      h_init_pos_y{window_height - 50};
  // pixels per second per second
  static const int gravity{1000};
  // pixels per second

  static const int scarfy_jump_velocity{-500};
};

struct AnimData {
  Texture2D texture;
  Rectangle rec;
  Vector2 pos;
  Vector2 initial_frame_pos = {0, 0};
  int frame{0};
  int max_frames;
  int velocity{0};
  float update_time;
  float running_time{0.0f};

  void next_frame() {
    if (update_time > running_time) {
      return;
    }
    rec.x = initial_frame_pos.x + frame * rec.width;
    frame++;
    if (frame >= max_frames) {
      frame = 0;
    }
    running_time = 0.0f;
  }
  void draw() { DrawTextureRec(texture, rec, pos, WHITE); }
};

AnimData InitializeScarfy() {
  AnimData data;
  data.texture = LoadTexture("textures/scarfy.png");
  data.max_frames = 6;
  data.rec.x = data.initial_frame_pos.x;
  data.rec.y = data.initial_frame_pos.y;
  data.rec.width = data.texture.width / data.max_frames;
  data.rec.height = data.texture.height;
  data.pos.x = Config::window_width / 2 - data.rec.width / 2;
  data.pos.y = Config::window_height - data.rec.height;
  data.update_time = 1.0f / 12.0f;

  return data;
}

AnimData InitializeEnemy(int x_offset) {
  AnimData data;
  data.texture = LoadTexture("textures/12_nebula_spritesheet.png");
  data.max_frames = 8;
  data.rec.x = data.initial_frame_pos.x;
  data.rec.y = data.initial_frame_pos.y;
  data.rec.width = data.texture.width / data.max_frames;
  data.rec.height = data.texture.height / 8;
  data.pos.x = Config::window_width + x_offset;
  data.pos.y = Config::window_height - data.rec.height;
  data.update_time = 1.0f / 30.0f;
  data.velocity = -300;

  return data;
}

void DrawWindow() {
  InitWindow(Config::window_width, Config::window_height, "Dapper Dasher");
  SetTargetFPS(60);
}

bool IsTouchingTheGround(AnimData *hero) {
  if (hero->pos.y >= Config::window_height - hero->rec.height) {
    return true;
  }

  return false;
}

void ControlHero(AnimData *hero, float delta_time) {

  if (IsTouchingTheGround(hero)) {
    hero->velocity = 0.0f;
  } else {
    hero->velocity += Config::gravity * delta_time;
  }

  if (IsKeyDown(KEY_SPACE) && IsTouchingTheGround(hero)) {
    hero->velocity = Config::scarfy_jump_velocity;
  }

  hero->pos.y += hero->velocity * delta_time;
}

void MoveEnemy(AnimData *enemy, float delta_time) {
  if (enemy->pos.x < -enemy->rec.width) {
    enemy->pos.x = Config::window_width;
  }
  enemy->pos.x += enemy->velocity * delta_time;
}

void GameLoop() {
  AnimData scarfy = InitializeScarfy();
  AnimData enemy = InitializeEnemy(0);
  AnimData enemy2 = InitializeEnemy(300);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Handle Objects movement
    ControlHero(&scarfy, dt);
    MoveEnemy(&enemy, dt);
    MoveEnemy(&enemy2, dt);

    // Draw Textures
    scarfy.draw();
    enemy.draw();
    enemy2.draw();

    // Update Times
    scarfy.running_time += dt;
    enemy.running_time += dt;
    enemy2.running_time += dt;

    // Animate
    if (IsTouchingTheGround(&scarfy)) {
      scarfy.next_frame();
    }
    enemy.next_frame();
    enemy2.next_frame();

    // Stop Drawing
    EndDrawing();
  }
  CloseWindow();
  UnloadTexture(scarfy.texture);
}

int main(void) {
  DrawWindow();
  GameLoop();
  CloseWindow();
  return 0;
}
