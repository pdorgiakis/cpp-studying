#pragma once
#ifndef CHARACTER_H
#include "base_character.h"
#include "raylib.h"

class Character : public BaseCharacter {
public:
  Character();
  virtual void Tick(float delta_time) override;
};
#endif
