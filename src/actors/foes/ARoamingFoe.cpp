#include "ARoamingFoe.h"
#include "Game.h"

ARoamingFoe::ARoamingFoe()
  : roam_dir(Dir::None)
{
  SetColor(0, 0, 100);
  SetSpeed(90);
}

void ARoamingFoe::Tick(Game& game)
{
  // if idle - select new roaming direction
  if (GetShift().ToDir() == Dir::None)
  {
    roam_dir = Dir(std::rand() % Dirs.size());
  }

  // move in random direction to the next pos
  Move(roam_dir, game.GetFrameDuration(), true);

  Base::Tick(game);
}