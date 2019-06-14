#include "AMaze.h"
#include "ACellWall.h"
#include "ACellRoad.h"
#include "APlayer.h"
#include "ARoamingFoe.h"

AMaze::AMaze()
  : size(23, 13)
{
  for (int i = 0; i < size.x; ++i)
  {
    for (int j = 0; j < size.y; ++j)
    {
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == size.x - 1 || j == size.y - 1 ||
          (i % 2 == 0 && j % 2 == 0))
      {
        cell = Spawn<ACellWall>();
      }
      else
      {
        cell = Spawn<ACellRoad>();
      }
      cell->SetPos(Pos(i, j));
    }
  }

  // spawn player
  auto player = Spawn<APlayer>();
  player->SetMaze(this);
  player->SetPos(Pos(1, 1));

  // adapt maze walls before randomly spawning foe
  AdaptNewChildren();

  // spawn foe
  SpawnAtFreeCell<ARoamingFoe>();
}

ACell* AMaze::GetCell(Pos pos) const
{
  // check maze bounds
  if (!pos.IsIn(size))
    return nullptr;

  // get cell at target position
  return static_cast<ACell*>(GetActor(pos.x * size.y + pos.y));
}

ACell* AMaze::GetFreeCell() const
{
  std::vector<ACell*> free_cells;
  for (int i = 0; i < size.x; ++i)
  {
    for (int j = 0; j < size.y; ++j)
    {
      ACell* cell = GetCell(Pos(i, j));
      if (cell != nullptr && !cell->IsSolid())
        free_cells.push_back(cell);
    }
  }

  if (free_cells.empty())
    return nullptr;

  int index = ::rand() % free_cells.size();
  return free_cells[index];
}

bool AMaze::IsSolid(Pos pos) const
{
  ACell* target = GetCell(pos);
  return target == nullptr || target->IsSolid();
}

template<class Character>
Character* AMaze::SpawnAtFreeCell()
{
  ACell* free_cell = GetFreeCell();
  if (free_cell == nullptr)
  {
    SDL_Log(__FUNCTION__ ". No free cell to spawn");
    return nullptr;
  }

  Character* character = Spawn<Character>();
  if (character == nullptr)
  {
    SDL_Log(__FUNCTION__ ". Failed spawn character");
    return nullptr;
  }

  character->SetMaze(this);
  character->SetPos(free_cell->GetPos());

  SDL_Log(__FUNCTION__ ". Spawned character at {%i, %i}", character->GetPos().x, character->GetPos().y);
  return character;
}
