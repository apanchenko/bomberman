#pragma once
#include "Actor.h"
#include "../types/Pos.h"

class ACell;

class AMaze : public Actor
{
public:
  AMaze();

  Pos           GetSize() const { return size; }
  ACell*        GetCell(Pos pos) const;
  ACell*        GetFreeCell() const;
  bool          IsSolid(Pos pos) const;

  template<class Character>
  Character*    SpawnAtFreeCell();

private:
  const Pos     size;
};