#include "ACell.h"

ACell::ACell()
{
  SetSize(SDL_Point{ Size, Size });
}

ACell& ACell::SetPos(SDL_Point _pos)
{
  pos = _pos;
  SetCoord(pos * Size + shift);
}

ACell& ACell::SetShift(SDL_Point _shift)
{
  shift = _shift;
  SetCoord(pos * Size + shift);
}

void ACell::AddShift(SDL_Point add_shift)
{
  shift += add_shift;
  SetCoord(pos * Size + shift);
}