#include "ABomb.h"
#include "ABlast.h"
#include "Game.h"
#include "actors/ACellGrass.h"

ABomb::ABomb()
{
  SetLifespan(3000);
  SetColor(0, 0, 0);
}

void ABomb::Die(Game& game)
{
  Base::Die(game);

  AMaze* maze = game.GetScene<AMaze>();
  Pos maze_size = maze->GetSize();
  for (Dir dir : Dirs)
  {
    Pos pos = GetPos() + dir;
    ACell* cell = maze->GetCell(pos);
    if (cell == nullptr)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __FUNCTION__ ". No cell at {%i, %i}", pos.x, pos.y);
      continue;
    }

    if (cell->GetMaterial() == Material::Carton)
    {
      ACellGrass* grass = maze->SpawnAndReplace<ACellGrass>(pos.ToIndex(maze_size));
      grass->SetPos(pos);
    }
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