#pragma once

#include "ACell.h"

class ACellCarton : public ACell
{
public:
  ACellCarton()
  {
    SetColor(146, 143, 140); // concrete color
    SetMaterial(Material::Carton);
  }
};