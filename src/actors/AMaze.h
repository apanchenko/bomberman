#pragma once
#include "ACell.h"
#include "types/Pos.h"

class APlayer;

class AMaze : public Actor
{
public:
                AMaze(Game& game);

  Pos           GetSize()         const { return size; }
  ACell*        GetCell(Pos pos)  const;
  ACell*        GetFreeCell()     const;
  Material      GetMaterial(Pos pos) const;

  template<class Character>
  Character*    SpawnAtFreeCell();

private:
  const Pos     size;
};



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