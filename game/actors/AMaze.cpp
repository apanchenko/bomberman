#include "AMaze.h"
#include "ACellWall.h"
#include "ACellGrass.h"
#include "ACellCarton.h"
#include "APlayer.h"
#include "foes/ARoamingFoe.h"
#include "foes/AChasingFoe.h"

AMaze::AMaze()
  : m_size(23, 13)
  , m_player(nullptr)
{
  Pos player_pos(1, 1);

  // build maze walls
  for (int i = 0; i < m_size.x; ++i)
  {
    for (int j = 0; j < m_size.y; ++j)
    {
      Pos pos(i, j);
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == m_size.x - 1 || j == m_size.y - 1 ||
          (i % 2 == 0 && j % 2 == 0))
      {
        cell = Spawn<ACellWall>();
      }
      else if (pos != player_pos && std::rand() % 100 < 30)
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
  m_player = Spawn<APlayer>();
  m_player->SetMaze(this);
  m_player->SetPos(Pos(1, 1));

  // adapt maze walls before randomly spawning foe
  AdaptNewChildren();

  // spawn some foes
  SpawnAtFreeCell<ARoamingFoe>();
  SpawnAtFreeCell<ARoamingFoe>();
  SpawnAtFreeCell<AChasingFoe>();
}

ACell* AMaze::GetCell(Pos pos) const
{
  // check maze bounds
  if (!pos.IsIn(m_size))
    return nullptr;

  // get cell at target position
  return static_cast<ACell*>(GetActor(pos.ToIndex(m_size)));
}

ACell* AMaze::GetFreeCell() const
{
  std::vector<ACell*> free_cells;
  for (int i = 0; i < m_size.x; ++i)
  {
    for (int j = 0; j < m_size.y; ++j)
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