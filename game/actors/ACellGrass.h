#pragma once
#include "ACell.h"

class ACellGrass : public ACell
{
public:
  ACellGrass()
  {
    SetColor(35, 170, 45); // green grass color
    SetMaterial(Material::Grass);
  }
};

