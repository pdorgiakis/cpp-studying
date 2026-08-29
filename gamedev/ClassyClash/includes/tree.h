#include "prop.h"

class Tree : public Prop {
public:
  Tree(Vector2 position) : Prop(position) {
    texture = LoadTexture("./textures/nature_tileset/Tree.png");
    padding = {8, 20};
  };
};
