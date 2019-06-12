#pragma once

#include "ACell.h"

class ACellWall : public ACell
{
public:
  ACellWall()
  {
    SetColor(193, 69, 64); // brick color
  }

  virtual bool CanPass() const override
  {
    return false;
  }
};