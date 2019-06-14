#include "ACell.h"

ACell::ACell()
  : m_is_solid(false)
{
  SetSize(Pos(Size, Size));
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

void ACell::Tick(Game& game)
{
  Base::Tick(game);
}
