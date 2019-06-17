#include "ABomb.h"
#include "ABlast.h"
#include "Game.h"
#include "actors/ACellGrass.h"
#include "actors/ACharacter.h"

ABomb::ABomb()
{
  SetLifespan(3000);
  SetColor(0, 0, 0);
}

void ABomb::Die(Game& game)
{
  Base::Die(game);

  for (Dir dir : Dirs)
  {
    Explode(game, GetPos() + dir);
  }

  Explode(game, GetPos());
}

void ABomb::Explode(Game& game, Pos pos)
{
  AMaze* maze = game.GetScene<AMaze>();

  // destroy carton walls
  ACell* cell = maze->GetCell(pos);
  if (cell == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __FUNCTION__ ". No cell at {%i, %i}", pos.x, pos.y);
    return;
  }
  if (cell->GetMaterial() == Material::Carton)
  {
    int index = pos.ToIndex(maze->GetSize());
    ACellGrass* grass = maze->SpawnAndReplace<ACellGrass>(index);
    grass->SetPos(pos);
  }

  // destroy characters
  std::vector<ACharacter*> victims = maze->FindAll<ACharacter>();
  for (auto victim : victims)
  {
    Pos vicpos = victim->GetPos();
    Dir vicdir = victim->GetShift().ToDir();
    if (vicpos == pos || vicpos + vicdir == pos)
    {
      maze->Remove(victim);
    }
  }

  // spawn explosion
  ABlast* blast = maze->Spawn<ABlast>();
  blast->SetPos(pos);
  blast->Refresh(game);
}