#pragma once

#include "ACell.h"

class ACellWall : public ACell
{
public:
  ACellWall()
  {
    SetColor(193, 193, 193); // concrete color
    SetMaterial(Material::Concrete);
  }
};