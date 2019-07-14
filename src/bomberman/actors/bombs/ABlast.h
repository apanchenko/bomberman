#pragma once
#include "actors/ACell.h"
#include "actors/ALifespan.h"

class ABlast : public ALifespan<ACell>
{
  typedef ALifespan<ACell> Base;

public:
  ABlast();
};

