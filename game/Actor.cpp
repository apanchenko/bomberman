#include "Actor.h"

void Actor::Tick(Game& game, Uint32 delta)
{
  for (auto& actor : actors)
  {
    actor->Tick(game, delta);
  }
}