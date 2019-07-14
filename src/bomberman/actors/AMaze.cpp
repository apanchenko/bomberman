#include "AMaze.h"
#include "ACellWall.h"
#include "ACellGrass.h"
#include "ACellCarton.h"
#include "APlayer.h"
#include "foes/ARoamingFoe.h"
#include "foes/AChasingFoe.h"

AMaze::AMaze(Game& game)
  : size(23, 13)
{
  Pos player_pos(1, 1);

  // build maze walls
  for (int i = 0; i < size.x; ++i)
  {
    for (int j = 0; j < size.y; ++j)
    {
      Pos pos(i, j);
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == size.x - 1 || j == size.y - 1 ||
          (i % 2 == 0 && j % 2 == 0))
      {
        cell = Spawn<ACellWall>();
      }
      else if (pos != player_pos && std::rand() % 100 < 30  // chance to spawn carton
            && pos.x > 3 && pos.y > 3)                      // space for player
      {
        cell = Spawn<ACellCarton>();
      }
      else
      {
        cell = Spawn<ACellGrass>();
      }
      cell->SetPos(pos);
    }
  }

  // spawn player
  APlayer* player = Spawn<APlayer>();
  player->SetMaze(this);
  player->SetPos(Pos(1, 1));

  // adapt maze walls before randomly spawning foe
  AdaptNewChildren(game);

  // spawn some foes
  SpawnAtFreeCell<ARoamingFoe>();
  SpawnAtFreeCell<ARoamingFoe>();
  SpawnAtFreeCell<AChasingFoe>();
}

ACell* AMaze::GetCell(Pos pos) const
{
  // check maze bounds
  if (!pos.IsIn(size))
    return nullptr;

  // get cell at target position
  return static_cast<ACell*>(GetActor(pos.ToIndex(size)));
}

ACell* AMaze::GetFreeCell() const
{
  std::vector<ACell*> free_cells;
  for (int i = 0; i < size.x; ++i)
  {
    for (int j = 0; j < size.y; ++j)
    {
      ACell* cell = GetCell(Pos(i, j));
      if (cell != nullptr && cell->GetMaterial()==Material::Grass)
        free_cells.push_back(cell);
    }
  }

  if (free_cells.empty())
    return nullptr;

  int index = ::rand() % free_cells.size();
  return free_cells[index];
}

Material AMaze::GetMaterial(Pos pos) const
{
  ACell* target = GetCell(pos);
  if (target == nullptr)
  {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __FUNCTION__ ". No cell at {%i, %i}", pos.x, pos.y);
    return Material::Concrete;
  }
    
  return target->GetMaterial();
}