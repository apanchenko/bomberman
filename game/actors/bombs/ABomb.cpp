#include "ABomb.h"
#include "ABlast.h"
#include "Game.h"

ABomb::ABomb()
{
  SetLifespan(3000);
  SetColor(0, 0, 0);
}

void ABomb::Die(Game& game)
{
  Base::Die(game);

  AMaze* maze = game.GetScene<AMaze>();
  for (Dir dir : Dirs)
  {
    Pos pos = GetPos() + dir;
    if (!maze->IsSolid(pos))
      SpawnBlast(game, pos);
  }
  SpawnBlast(game, GetPos());
}

void ABomb::SpawnBlast(Game& game, Pos pos)
{
  AMaze* maze = game.GetScene<AMaze>();
  ABlast* blast = maze->Spawn<ABlast>();
  blast->SetPos(pos);
  blast->Refresh(game);
}