#include "ARect.h"
#include "Game.h"

ARect::ARect()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;
}

ARect& ARect::SetCoord(SDL_Point coord)
{
  rect.x = coord.x;
  rect.y = coord.y;
  return *this;
}

ARect& ARect::SetSize(SDL_Point size)
{
  rect.w = size.x;
  rect.h = size.y;
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
  Base::Tick(game, delta);

  SDL_SetRenderDrawColor(game.GetRenderer(), color_r, color_g, color_b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(game.GetRenderer(), &rect);
} 