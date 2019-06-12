#pragma once
#include "Actor.h"

// basic math operators
SDL_Point operator * (SDL_Point rect, int mult) { return SDL_Point {rect.x * mult, rect.y * mult}; }
SDL_Point operator + (SDL_Point a, SDL_Point b) { return SDL_Point {a.x + b.x, a.y + b.y}; }
SDL_Point operator +=(SDL_Point a, SDL_Point b) { a.x += b.x; a.y += b.y; return a; }

// Rectangle actor
//  - has pixel coordinates and size
//  - has color
class ARect : public Actor
{
private:
  typedef Actor Base;

public:
  ARect();

  ARect&        SetCoord(SDL_Point coord);
  ARect&        SetSize(SDL_Point size);
  ARect&        SetColor(Uint8 r, Uint8 h, Uint8 b);

  virtual void  Tick(Game& game, Uint32 delta) override;

private:
  SDL_Rect      rect;
  Uint8         color_r = 0;
  Uint8         color_g = 0;
  Uint8         color_b = 0;
};

