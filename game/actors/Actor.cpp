#include "Actor.h"

void Actor::Tick(Game& game)
{
  for (auto& actor : actors)
  {
    actor->Tick(game);
  }
}