#include "ACharacter.h"
#include "AMaze.h"

bool ACharacter::CanMove(Dir dir) const
{
  Pos pos = GetPos();
  Pos shift = GetShift();
  Dir shift_dir = shift.ToDir();

  bool opposite = dir != shift_dir && ((int)dir % 2) == ((int)shift_dir % 2);

  if (!opposite && maze->IsSolid(pos + dir))
    return false;

  if (dir != shift_dir && maze->IsSolid(pos + shift_dir + dir))
    return false;

  return true;
}

bool ACharacter::Move(Dir dir, bb::Time duration)
{
  if (!CanMove(dir))
    return false;

  // displacement in pixels
  int path = duration * speed / 1000;

  // apply path in direction requested
  Pos pos = GetPos();
  Pos shift = GetShift();
  while (path > 0)
  switch (dir)
  {
  case Dir::Up:
    if (path - shift.y < Size)
    {
      shift.y -= path;
      path = 0;
    }
    else
    {
      pos.y -= 1;
      shift.y = 0;
      path -= Size + shift.y;
    }
    break;

  case Dir::Right:
    if (path + shift.x < Size)
    {
      shift.x += path;
      path = 0;
    }
    else
    {
      pos.x += 1;
      shift.x = 0;
      path -= Size - shift.x;
    }
    break;

  case Dir::Down:
    if (path + shift.y < Size)
    {
      shift.y += path;
      path = 0;
    }
    else
    {
      pos.y += 1;
      shift.y = 0;
      path -= Size - shift.y;
    }
    break;

  case Dir::Left:
    if (path - shift.x < Size)
    {
      shift.x -= path;
      path = 0;
    }
    else
    {
      pos.x -= 1;
      shift.x = 0;
      path -= Size + shift.x;
    }
    break;
  }

  SetShift(shift);
  SetPos(pos);
  return true;
}

void ACharacter::Tick(Game& game)
{
  Base::Tick(game);
}