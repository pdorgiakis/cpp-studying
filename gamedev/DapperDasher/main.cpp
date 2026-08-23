#include "raylib.h"
#include <iostream>

struct Config {
  static const int window_width{512}, window_height{380};
  // pixels per second per second
  static const int gravity{1200};
  // pixels per second
  static const int scarfy_jump_velocity{-600};
  static const int max_enemies{3};
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
  float scale{1.0f};

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
  data.pos.x = Config::window_width / 3 - data.rec.width / 2;
  data.pos.y = Config::window_height - data.rec.height - 20;
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
  data.pos.y = Config::window_height - data.rec.height - 20;
  data.update_time = 1.0f / 30.0f;
  data.velocity = -350;

  return data;
}

AnimData InitializeForeground(int x_offset = 0) {
  AnimData data;
  data.texture = LoadTexture("textures/foreground.png");
  data.rec.x = 0;
  data.rec.y = 0;
  data.scale = 2.0f;
  data.rec.width = data.texture.width * data.scale;
  data.rec.height = data.texture.height * data.scale;
  data.pos.x = x_offset;
  data.pos.y = Config::window_height - data.rec.height;
  data.velocity = -300;

  return data;
}

AnimData InitializedMiddleGround(int x_offset = 0) {
  AnimData data;
  data.texture = LoadTexture("textures/back-buildings.png");
  data.rec.x = 0;
  data.rec.y = 0;
  data.scale = 2.0f;
  data.rec.width = data.texture.width * data.scale;
  data.rec.height = data.texture.height * data.scale;
  data.pos.x = x_offset;
  data.pos.y = Config::window_height - data.rec.height;
  data.velocity = -100;

  return data;
}

AnimData InitializeBackground(int x_offset = 0) {
  AnimData data;
  data.texture = LoadTexture("textures/far-buildings.png");
  data.rec.x = 0;
  data.rec.y = 0;
  data.scale = 2.0f;
  data.rec.width = data.texture.width * data.scale;
  data.rec.height = data.texture.height * data.scale;
  data.pos.x = x_offset;
  data.pos.y = Config::window_height - data.rec.height;
  data.velocity = -30;

  return data;
}

void AnimateBackground(AnimData *data, float delta_time) {
  data->pos.x += data->velocity * delta_time;
  if (data->pos.x <= -data->rec.width) {
    data->pos.x = data->rec.width - 10;
  }
}

void DrawBgs(AnimData bgs[2]) {
  for (int i = 0; i < 2; i++) {
    DrawTextureEx(bgs[i].texture, bgs[i].pos, 0.0f, bgs[i].scale, WHITE);
  }
}

void DrawWindow() {
  InitWindow(Config::window_width, Config::window_height, "Dapper Dasher");
  SetTargetFPS(60);
}

bool IsTouchingTheGround(AnimData *hero) {
  if (hero->pos.y >= Config::window_height - hero->rec.height - 20) {
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

void MoveObject(AnimData *enemy, float delta_time) {
  enemy->pos.x += enemy->velocity * delta_time;
}

void GameLoop() {
  AnimData scarfy = InitializeScarfy();
  AnimData enemies[Config::max_enemies];
  for (int n = 0; n < Config::max_enemies; n++) {
    enemies[n] = InitializeEnemy(Config::window_width + n * 500);
  }

  float finish_line{enemies[Config::max_enemies - 1].pos.x};
  std::cout << finish_line << std::endl;
  bool collided = false;

  AnimData foregrounds[2];
  foregrounds[0] = InitializeForeground();
  foregrounds[1] = InitializeForeground(foregrounds[0].rec.width);

  AnimData middlegrounds[2];
  middlegrounds[0] = InitializedMiddleGround();
  middlegrounds[1] = InitializedMiddleGround(middlegrounds[0].rec.width);

  AnimData backgrounds[2];
  backgrounds[0] = InitializeBackground();
  backgrounds[1] = InitializeBackground(backgrounds[0].rec.width);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Handle Objects movement
    if (!collided) {
      ControlHero(&scarfy, dt);
      for (int i = 0; i < Config::max_enemies; i++) {
        MoveObject(&enemies[i], dt);
      }
      for (int bg = 0; bg < 2; bg++) {
        AnimateBackground(&foregrounds[bg], dt);
      }
      for (int bg = 0; bg < 2; bg++) {
        AnimateBackground(&middlegrounds[bg], dt);
      }
      for (int bg = 0; bg < 2; bg++) {
        AnimateBackground(&backgrounds[bg], dt);
      }
    }
    // Update finish line to move along with the last enemy
    finish_line += enemies[0].velocity * dt;

    // Check Collisions
    float pad{20.0f};
    Rectangle scarfy_rec{scarfy.pos.x + pad, scarfy.pos.y,
                         scarfy.rec.width - 2 * pad, scarfy.rec.height};
    for (AnimData enemy : enemies) {
      if (enemy.pos.x >= 0 && enemy.pos.x <= Config::window_width) {
        Rectangle enemy_rec{enemy.pos.x + pad, enemy.pos.y + pad,
                            enemy.rec.width - 2 * pad,
                            enemy.rec.height - 2 * pad};

        if (CheckCollisionRecs(scarfy_rec, enemy_rec)) {
          collided = true;
        }
      }
    }

    // Draw Textures
    DrawBgs(backgrounds);
    DrawBgs(middlegrounds);
    DrawBgs(foregrounds);
    if (!collided) {
      DrawRectangleRec(scarfy_rec, RED);
      scarfy.draw();
      for (int i = 0; i < Config::max_enemies; i++) {
        // DrawRectangle(enemies[i].pos.x, enemies[i].pos.y,
        // enemies[i].rec.width,
        //               enemies[i].rec.height, RED);
        enemies[i].draw();
      }
    } else {
      DrawText("Game Over",
               Config::window_width / 2 - MeasureText("Game Over", 40) / 2,
               Config::window_height / 2, 40, RED);
    }

    if (scarfy.pos.x >= finish_line) {
      DrawText("You Win",
               Config::window_width / 2 - MeasureText("You Win", 40) / 2,
               Config::window_height / 2, 40, RED);
      scarfy.velocity = 200.0f;
      if (IsTouchingTheGround(&scarfy)) {
        MoveObject(&scarfy, dt);
      }
    }

    // Update Times
    scarfy.running_time += dt;
    for (int i = 0; i < Config::max_enemies; i++) {
      enemies[i].running_time += dt;
    }

    // Animate
    if (IsTouchingTheGround(&scarfy)) {
      scarfy.next_frame();
    }
    for (int i = 0; i < Config::max_enemies; i++) {
      enemies[i].next_frame();
    }

    // Stop Drawing
    EndDrawing();
  }
  CloseWindow();

  // Unload Textures
  UnloadTexture(scarfy.texture);
  for (int i = 0; i < Config::max_enemies; i++) {
    UnloadTexture(enemies[i].texture);
  }
  for (int bg = 0; bg < 2; bg++) {
    UnloadTexture(foregrounds[bg].texture);
  }
}

int main(void) {
  DrawWindow();
  GameLoop();
  CloseWindow();
  return 0;
}
