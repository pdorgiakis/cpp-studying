#pragma once
#ifndef CHARACTER_H
#include "base_character.h"
#include "raylib.h"

class Character : public BaseCharacter {
public:
  Character();
  virtual void Tick(float delta_time) override;
  virtual Vector2 GetScreenPosition() override;
  Rectangle GetWeaponCollisionRec() { return weapon_collision_rec; }

private:
  bool MovingLeft();
  bool MovingRight();
  void DrawWeapon();
  Texture2D weapon{};
  Rectangle weapon_collision_rec{};
  float weapon_width{0.f};
  float weapon_height{0.f};
};
#endif
