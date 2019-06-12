#include "ARect.h"
#include "Game.h"

ARect::ARect()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;
}

ARect& ARect::SetPosition(int x, int y)
{
  rect.x = x;
  rect.y = y;
  return *this;
}

ARect& ARect::SetSize(int w, int h)
{
  rect.w = w;
  rect.h = h;
  return *this;
}

ARect& ARect::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
  color_r = r;
  color_g = g;
  color_b = b;
  return *this;
}

void ARect::Tick(Game& game, Uint32 delta)
{
  SDL_SetRenderDrawColor(game.GetRenderer(), color_r, color_g, color_b, SDL_ALPHA_OPAQUE);

  delta;
  SDL_RenderFillRect(game.GetRenderer(), &rect);
} 