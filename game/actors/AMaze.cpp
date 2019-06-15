#include "AMaze.h"
#include "ACellWall.h"
#include "ACellRoad.h"
#include "APlayer.h"
#include "foes/ARoamingFoe.h"

AMaze::AMaze()
  : m_size(23, 13)
  , m_player(nullptr)
{
  // build maze walls
  for (int i = 0; i < m_size.x; ++i)
  {
    for (int j = 0; j < m_size.y; ++j)
    {
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == m_size.x - 1 || j == m_size.y - 1 ||
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
  m_player = Spawn<APlayer>();
  m_player->SetMaze(this);
  m_player->SetPos(Pos(1, 1));

  // adapt maze walls before randomly spawning foe
  AdaptNewChildren();

  // spawn foe
  SpawnAtFreeCell<ARoamingFoe>();
}

ACell* AMaze::GetCell(Pos pos) const
{
  // check maze bounds
  if (!pos.IsIn(m_size))
    return nullptr;

  // get cell at target position
  return static_cast<ACell*>(GetActor(pos.x * m_size.y + pos.y));
}

ACell* AMaze::GetFreeCell() const
{
  std::vector<ACell*> free_cells;
  for (int i = 0; i < m_size.x; ++i)
  {
    for (int j = 0; j < m_size.y; ++j)
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