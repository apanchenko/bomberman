#include "ACharacter.h"

void ACharacter::MoveUp()
{

}

void ACharacter::MoveRight()
{

}

void ACharacter::MoveDown()
{

}

void ACharacter::MoveRight()
{

}

void ACharacter::Tick(Game& game, Uint32 delta)
{
  switch (momentum)
  {
    case Momentum::Up:
      AddShift(SDL_Point{ 0, - delta * speed / 1000 });
      break;
  }

  Base::Tick(game, delta);
}