#include "ACell.h"

ACell::ACell()
  : is_solid(false)
{
  SetSize(Pos(Size, Size));
}

void ACell::Tick(Game& game)
{
  SetCoord(pos * Size + shift);
  Base::Tick(game);
}
