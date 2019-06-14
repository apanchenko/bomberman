#include "Actor.h"

void Actor::AdaptNewChildren()
{
  // move new children in separate cycle
  for (auto& actor : new_actors)
  {
    actors.push_back(std::move(actor));
  }
  new_actors.clear();
}

void Actor::Tick(Game& game)
{
  AdaptNewChildren();

  // tick children
  for (const UActor& actor : actors)
  {
    actor.get()->Tick(game);
  }
}