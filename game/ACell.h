#pragma once
#include "ARect.h"
#include "Pos.h"

// Cell actor
//   - has size in pixels
//   - has position in a grid
//   - pixel coordinates calculated by position and shift
class ACell : public ARect
{
private:
  typedef ARect Base;

public:
  ACell();

  ACell&        SetPos(SDL_Point pos);
  ACell&        SetShift(SDL_Point shift);
  void          AddShift(SDL_Point add_shift);

  // return true if a character can pass throught this cell
  virtual bool  CanPass() const = 0;

  // square cell size equal for all cells
  static const int Size = 64;

private:
  SDL_Point     pos;
  SDL_Point     shift;
};