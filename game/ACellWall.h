#pragma once

#include "ACell.h"

class ACellWall : public ACell
{
public:
  ACellWall()
  {
    SetColor(193, 193, 193); // concrete color
  }

  virtual bool CanPass() const override
  {
    return false;
  }
};