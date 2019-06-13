#include "ACharacter.h"
#include "AMaze.h"

bool ACharacter::GetCanMove(Pos to) const
{
  ACell* target = maze->GetCell(to);
  return target != nullptr && !target->IsSolid();
}

bool ACharacter::Move(Dir dir, bb::Time duration)
{
  Pos pos = GetPos();
  Pos shift = GetShift();

  if (!GetCanMove(pos + dir))
    return false;

  Dir shift_dir = shift.ToDir();
  if (dir != shift_dir && !GetCanMove(pos + shift_dir + dir))
    return false;

  // displacement in pixels
  int path = duration * speed / 1000;

  // apply path in direction requested
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
}

void ACharacter::Tick(Game& game)
{
  Base::Tick(game);
}