#include "includes/base_character.h"
#include <iostream>
BaseCharacter::BaseCharacter() {}

void BaseCharacter::Tick(float delta_time) {
  previous_position = world_position;
  if (invulnerability_time > time_since_last_hit)
    time_since_last_hit += delta_time;

  // Calculate collision rectangle
  collision_rec = {GetScreenPosition().x + padding.x * scale,
                   GetScreenPosition().y + padding.y * scale,
                   (width - padding.x * 2) * scale,
                   (height - padding.y) * scale};

  // Animate
  running_time += delta_time;
  if (update_time < running_time) {
    frame++;
    running_time = 0.0f;

    if (frame > max_frames)
      frame = 0;
  }

  // Draw
  Rectangle source_rectangle = {frame * width, 0, char_rotation * width,
                                height};

  Rectangle dest_rectangle = {GetScreenPosition().x, GetScreenPosition().y,
                              scale * width, height * scale};
  float health_ratio = current_health / max_health;
  // Total Health
  DrawRectangle(GetScreenPosition().x, GetScreenPosition().y - 10.f,
                dest_rectangle.width, 2., BLACK);
  // Current Health
  DrawRectangle(GetScreenPosition().x, GetScreenPosition().y - 10.f,
                dest_rectangle.width * health_ratio, 2, RED);
  Color color = invulnerability_time >= time_since_last_hit ? RED : WHITE;
  DrawTexturePro(texture, source_rectangle, dest_rectangle, Vector2{},
                 char_rotation, color);
  // DrawRectangleRec(collision_rec, RED);
}

void BaseCharacter::Hit(float damage) { current_health -= damage; }
