#include "AMaze.h"
#include "ACellWall.h"
#include "ACellRoad.h"
#include "APlayer.h"

AMaze::AMaze()
  : size(27, 13)
{
  for (int i = 0; i < size.x; ++i)
  {
    for (int j = 0; j < size.y; ++j)
    {
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == size.x - 1 || j == size.y - 1 ||
          (i % 2 == 0 && j % 2 == 0))
      {
        cell = AddActor<ACellWall>();
      }
      else
      {
        cell = AddActor<ACellRoad>();
      }
      cell->SetPos(Pos(i, j));
    }
  }

  AddActor<APlayer>();
}

ACell* AMaze::GetCell(Pos pos) const
{
  // check maze bounds
  if (pos.IsIn(size))
    return nullptr;

  // get cell at target position
  return static_cast<ACell*>(GetActor(pos.x * size.y + pos.y));
}