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

private:
  const Pos     size;
};