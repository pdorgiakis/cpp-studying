#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "base_character.h"
#include "character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
public:
  Enemy(Vector2 position);
  virtual void Tick(float delta_time) override;
  void SetTarget(Character *character) { target = character; }
  virtual Vector2 GetScreenPosition() override;

private:
  Character *target;
  bool aggroed{false};
};
#endif
