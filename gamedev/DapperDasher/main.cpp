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

  static const int ground{window_height - 50};
};

struct Scarfy {
  Texture2D scarfy_texture = LoadTexture("textures/scarfy.png");
  int frame{0};
  const int max_frames{6};
  Rectangle scarfy_rec = {0, 0, float(scarfy_texture.width / max_frames),
                          float(scarfy_texture.height)};
  Vector2 scarfy_pos = {float(Config::window_width / 2 - scarfy_rec.width / 2),
                        float(Config::ground - scarfy_rec.height)};
  int velocity{0};
  constexpr static const float jump_velocity{-500.0f};

  void next_frame() {
    scarfy_rec.x = frame * scarfy_rec.width;
    frame++;
    if (frame >= max_frames) {
      frame = 0;
    }
  }
};

struct Enemy {
  Texture2D enemy_texture = LoadTexture("textures/Creature_16x16.png");
  int frame{0};
  const int max_frames{4};
  const int initial_frame_pos{64};
  Rectangle enemy_rec = {64, 128, 16.0f, 16.0f};
  Rectangle enemy_resize_rec = {Config::window_width, Config::ground,
                                enemy_rec.width * 5.0f,
                                enemy_rec.height * 5.0f};
  Vector2 enemy_pos = {enemy_resize_rec.width, enemy_resize_rec.height};
  int velocity{-300};

  void next_frame() {
    enemy_rec.x = initial_frame_pos + frame * enemy_rec.width;
    frame++;
    if (frame >= max_frames) {
      frame = 0;
    }
  }
};

void DrawWindow() {
  InitWindow(Config::window_width, Config::window_height, "Dapper Dasher");
  SetTargetFPS(60);
}

bool IsTouchingTheGround(Scarfy *hero) {
  if (hero->scarfy_pos.y >= Config::ground - hero->scarfy_rec.height) {
    return true;
  }

  return false;
}

void ControlHero(Scarfy *hero, float delta_time) {

  if (IsTouchingTheGround(hero)) {
    hero->velocity = 0.0f;
  } else {
    hero->velocity += Config::gravity * delta_time;
  }

  if (IsKeyDown(KEY_SPACE) && IsTouchingTheGround(hero)) {
    hero->velocity = hero->jump_velocity;
  }

  hero->scarfy_pos.y += hero->velocity * delta_time;
}

void MoveEnemy(Enemy *enemy, float delta_time) {
  if (enemy->enemy_resize_rec.x < 0) {
    enemy->enemy_resize_rec.x = Config::window_width;
  }
  enemy->enemy_resize_rec.x += enemy->velocity * delta_time;
}

void GameLoop() {
  Scarfy scarfy;
  Enemy enemy;
  int scarfy_frame = 1;

  float update_time = 1.0f / 5.0f;
  float running_time{0.0f};

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Handle Objects movement
    ControlHero(&scarfy, dt);
    MoveEnemy(&enemy, dt);

    // Draw Textures
    DrawTextureRec(scarfy.scarfy_texture, scarfy.scarfy_rec, scarfy.scarfy_pos,
                   WHITE);
    DrawTexturePro(enemy.enemy_texture, enemy.enemy_rec, enemy.enemy_resize_rec,
                   enemy.enemy_pos, 0.0f, WHITE);

    if (CheckCollisionRecs(scarfy.scarfy_rec, enemy.enemy_rec)) {
      DrawText("You hit the axe!", 400, 200, 20, RED);
    }

    running_time += dt;

    // Animate
    if (running_time >= update_time) {
      if (IsTouchingTheGround(&scarfy)) {
        scarfy.next_frame();
      }
      enemy.next_frame();

      running_time = 0.0f;
    }

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
