#pragma once
#include "ARect.h"

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

  void          SetSolid(bool _solid)   { solid = _solid; }
  void          SetPos(Pos _pos)        { pos = _pos; }
  void          SetShift(Pos _shift)    { shift = _shift; }
  void          Shift(Pos _shift)       { shift += _shift; }

  // square cell size equal for all cells
  static const int Size = 64;

  virtual void  Tick(Game& game) override;

private:
  Pos           pos;    // position in maze grid
  Pos           shift;  // shift from pos in pixels
  bool          solid;  //
};