#pragma once
#include "Actor.h"

class AMaze : public Actor
{
public:
  AMaze();

  Pos           GetSize() const { return size; }
  ACell*        GetCell(Pos pos) const;

private:
  const Pos     size;
};