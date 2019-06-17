#pragma once
#include "ARect.h"

enum class Material
{
  Grass,
  Carton,
  Concrete
};

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

  void          SetMaterial(Material material);
  virtual void  SetPos(Pos pos);
  void          SetShift(Pos shift);

  Pos           GetPos() const          { return m_pos; }
  Pos           GetShift() const        { return m_shift; }
  Material      GetMaterial() const     { return m_material; }
  
  // square cell size equal for all cells
  static const int Size = 50;

private:
  Pos           m_pos;        // position in maze grid
  Pos           m_shift;      // shift from pos in pixels
  Material      m_material;   // cell material type
};