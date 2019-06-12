#pragma once
#include "ARect.h"

class ACell : public ARect
{
public:
  // square cell size equal for all cells
  static const int Size = 64;

  ACell()
  {
    SetSize(Size, Size);
  }

  // return true if a character can pass throught this cell
  virtual bool CanPass() const = 0;
};

