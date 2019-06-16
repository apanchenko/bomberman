#pragma once
#include "actors/ACell.h"
#include "actors/ALifespan.h"

// A bomb will explode devastating everything around
class ABomb : public ALifespan<ACell>
{
  typedef ALifespan<ACell> Base;

public:
  ABomb();

  virtual void  Die(Game& game) override;

private:
  void          SpawnBlast(Game& game, Pos pos);
};