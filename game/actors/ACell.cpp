#include "ACell.h"
#include "Game.h"
#include "actors/AMaze.h"

ACell::ACell()
  : m_material(Material::Grass)
{
  SetSize(Pos(Size, Size));
}

void ACell::SetMaterial(Material material)
{
  m_material = material;
}

void ACell::SetPos(Pos pos)
{
  m_pos = pos;
  SetCoord(m_pos * Size + m_shift);
}

void ACell::SetShift(Pos shift)
{
  m_shift = shift;
  SetCoord(m_pos * Size + m_shift);
}