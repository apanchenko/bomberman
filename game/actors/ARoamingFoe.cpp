#include "ARoamingFoe.h"
#include "../Game.h"

ARoamingFoe::ARoamingFoe()
  : roam_dir(Dir::None)
{
  SetColor(30, 0, 0);
  SetSpeed(90);
}

void ARoamingFoe::Tick(Game& game)
{
  // if idle - select new roaming direction
  if (GetShift().ToDir() == Dir::None)
  {
    roam_dir = Dir(::rand() % bb::DIRCOUNT);
  }

  // move in random direction to the next pos
  Move(roam_dir, game.GetFrameDuration(), true);

  Base::Tick(game);
}