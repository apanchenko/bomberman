#pragma once
#include "Actor.h"

// rectangle actor
class ARect : public Actor
{
public:
  ARect();
  ARect& SetPosition(int x, int y);
  ARect& SetSize(int w, int h);
  ARect& SetColor(Uint8 r, Uint8 h, Uint8 b);

  virtual void Tick(Game& game, Uint32 delta) override;

private:
  SDL_Rect  rect;
  Uint8     color_r = 0;
  Uint8     color_g = 0;
  Uint8     color_b = 0;
};

