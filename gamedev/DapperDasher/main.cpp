#include "raylib.h"
#include <iostream>

struct Config {
  static const int window_width{512}, window_height{380};
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
  data.pos.x = Config::window_width / 2 - data.rec.width / 2;
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
  data.velocity = -300;

  return data;
}

AnimData InitializeFirstLevelBackground(int x_offset = 0) {
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

AnimData InitializeSecondLevelBackground(int x_offset = 0) {
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

AnimData InitializeThirdLevelBackground(int x_offset = 0) {
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
  AnimData first_level_background[3];
  first_level_background[0] = InitializeFirstLevelBackground();
  first_level_background[1] =
      InitializeFirstLevelBackground(first_level_background[0].rec.width);

  AnimData second_level_background[3];
  second_level_background[0] = InitializeSecondLevelBackground();
  second_level_background[1] =
      InitializeSecondLevelBackground(second_level_background[0].rec.width);

  AnimData third_level_background[3];
  third_level_background[0] = InitializeThirdLevelBackground();
  third_level_background[1] =
      InitializeThirdLevelBackground(third_level_background[0].rec.width);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();
    // Start Drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Handle Objects movement
    ControlHero(&scarfy, dt);
    MoveEnemy(&enemy, dt);
    MoveEnemy(&enemy2, dt);
    for (int bg = 0; bg < 2; bg++) {
      AnimateBackground(&first_level_background[bg], dt);
    }
    for (int bg = 0; bg < 2; bg++) {
      AnimateBackground(&second_level_background[bg], dt);
    }
    for (int bg = 0; bg < 2; bg++) {
      AnimateBackground(&third_level_background[bg], dt);
    }

    // Draw Textures
    DrawBgs(third_level_background);
    DrawBgs(second_level_background);
    DrawBgs(first_level_background);
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
  for (int bg = 0; bg < 2; bg++) {
    UnloadTexture(first_level_background[bg].texture);
  }
}

int main(void) {
  DrawWindow();
  GameLoop();
  CloseWindow();
  return 0;
}
