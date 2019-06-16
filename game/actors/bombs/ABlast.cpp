#include "ABlast.h"

ABlast::ABlast()
{
  SetLifespan(250);
  SetColor(0, 0, 0);
}

void ABlast::Die(Game& game)
{
  Base::Die(game);
}