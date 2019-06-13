#include "AMaze.h"
#include "ACellWall.h"
#include "ACellRoad.h"
#include "APlayer.h"

AMaze::AMaze()
{
  for (int i = 0; i < Width; ++i)
  {
    for (int j = 0; j < Height; ++j)
    {
      ACell* cell = nullptr;
      if (i == 0 || j == 0 || i == Width - 1 || j == Height - 1 ||
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