#include "prop.h"

class Rock : public Prop {
public:
  Rock(Vector2 position) : Prop(position) {
    texture = LoadTexture("./textures/nature_tileset/Rock.png");
  };

protected:
  Vector2 padding{20, 20};
};
