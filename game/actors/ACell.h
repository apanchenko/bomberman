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

  void          SetSolid(bool _solid)   { is_solid = _solid; }
  void          SetPos(Pos _pos);
  void          SetShift(Pos _shift);

  Pos           GetPos() const          { return pos; }
  Pos           GetShift() const        { return shift; }
  bool          IsSolid() const         { return is_solid; }

  // square cell size equal for all cells
  static const int Size = 50;

  virtual void  Tick(Game& game) override;

private:
  Pos           pos;      // position in maze grid
  Pos           shift;    // shift from pos in pixels
  bool          is_solid; // characters can pass through this cell
};