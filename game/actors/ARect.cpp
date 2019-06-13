#include "ARect.h"
#include "../Game.h"

ARect::ARect()
{
  rect.x = 0;
  rect.y = 0;
  rect.w = 0;
  rect.h = 0;
}

void ARect::SetCoord(Pos coord)
{
  rect.x = coord.x;
  rect.y = coord.y;
}

void ARect::SetSize(Pos size)
{
  rect.w = size.x;
  rect.h = size.y;
}

void ARect::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
  color_r = r;
  color_g = g;
  color_b = b;
}

void ARect::Tick(Game& game)
{
  Base::Tick(game);

  SDL_SetRenderDrawColor(game.GetRenderer(), color_r, color_g, color_b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(game.GetRenderer(), &rect);
} 