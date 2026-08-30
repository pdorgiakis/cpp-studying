#include "base_character.h"
#include "raylib.h"

class Enemy : public BaseCharacter {
public:
  Enemy(Vector2 position);
  void SetScreenPosition(Vector2 character_position);
  virtual void Tick(float delta_time) override;

protected:
  
};
