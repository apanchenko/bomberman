#include "ACell.h"

ACell::ACell()
  : is_solid(false)
{
  SetSize(Pos(Size, Size));
}

void ACell::SetPos(Pos _pos)
{
  pos = _pos;
  SetCoord(pos * Size + shift);
}

void ACell::SetShift(Pos _shift)
{
  shift = _shift;
  SetCoord(pos * Size + shift);
}

void ACell::Tick(Game& game)
{
  Base::Tick(game);
}
