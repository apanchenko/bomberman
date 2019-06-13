#pragma once
#include "ACell.h"

class ACellRoad : public ACell
{
public:
  ACellRoad()
  {
    SetColor(44, 176, 55); // green grass color
    SetSolid(false);
  }
};

