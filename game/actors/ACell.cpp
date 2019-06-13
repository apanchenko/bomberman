#include "ACell.h"

ACell::ACell()
  : solid(false)
{
  SetSize(Pos(Size, Size));
}

void ACell::Tick(Game& game)
{
  SetCoord(pos * Size + shift);
  Base::Tick(game);
}
