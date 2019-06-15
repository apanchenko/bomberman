#pragma once
#include "ACell.h"

class ACellRoad : public ACell
{
public:
  ACellRoad()
  {
    SetColor(35, 170, 45); // green grass color
    SetSolid(false);
  }
};

