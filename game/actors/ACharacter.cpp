#include "ACharacter.h"
#include "AMaze.h"

bool ACharacter::GetCanMove(Dir dir)
{
  ACell* target = maze->GetCell(GetPos() + dir);
  if (target == nullptr)
    return false;

  return !target->IsSolid();
}

void ACharacter::Move(Dir dir, Uint32 duration)
{
  // displacement in 1000 pixels
  int path = duration * speed;

  // apply path to sub_shift in direction requested
  switch (dir)
  {
  case Dir::Up:    sub_shift.y -= path;    break;
  case Dir::Right: sub_shift.x += path;    break;
  case Dir::Down:  sub_shift.y += path;    break;
  case Dir::Left:  sub_shift.x -= path;    break;
  }

  // convert to pixels and move
  Shift(sub_shift / 1000);

  sub_shift %= 1000;
}

void ACharacter::Tick(Game& game)
{
  Base::Tick(game);
}