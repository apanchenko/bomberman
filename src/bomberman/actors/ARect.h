#pragma once
#include "Actor.h"
#include "../types/Pos.h"

// Rectangle actor
//  - has pixel coordinates and size
//  - has color
class ARect : public Actor
{
  typedef Actor Base;

public:
  ARect();

  void          SetCoord(Pos coord);
  void          SetSize(Pos size);
  void          SetColor(Uint8 r, Uint8 g, Uint8 b);

  virtual void  Tick(Game& game) override;

private:
  SDL_Rect      rect;
  Uint8         color_r = 0;
  Uint8         color_g = 0;
  Uint8         color_b = 0;
};

