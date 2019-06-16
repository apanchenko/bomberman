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

  void          SetSolid(bool solid)    { m_is_solid = solid; }
  virtual void  SetPos(Pos pos);
  void          SetShift(Pos shift);

  Pos           GetPos() const          { return m_pos; }
  Pos           GetShift() const        { return m_shift; }
  bool          IsSolid() const         { return m_is_solid; }

  // square cell size equal for all cells
  static const int Size = 50;

private:
  Pos           m_pos;      // position in maze grid
  Pos           m_shift;    // shift from pos in pixels
  bool          m_is_solid; // characters can pass through this cell
};