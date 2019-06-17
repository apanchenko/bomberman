#include "Actor.h"
#include <algorithm>

Actor* Actor::GetActor(int index) const
{
  if (index < 0 || index >= actors.size())
    return nullptr;
  return actors[index].get();
}

void Actor::Remove(Actor* victim)
{
  remove_actors.push_back(victim);
}

void Actor::DiscardRemovedChildren()
{
  for (auto victim : remove_actors)
  {
    auto pred = [victim](auto& actor) { return actor.get() == victim; };

    auto it = std::find_if(actors.begin(), actors.end(), pred);
    if (it != actors.end())
    {
      actors.erase(it);
      continue;
    }

    it = std::find_if(new_actors.begin(), new_actors.end(), pred);
    if (it != new_actors.end())
    {
      new_actors.erase(it);
    }
  }
  remove_actors.clear();
}

void Actor::AdaptNewChildren()
{
  // move new children in separate cycle
  for (auto& actor : new_actors)
  {
    actors.push_back(std::move(actor));
  }
  new_actors.clear();
}

void Actor::SubstututeChildren()
{
  for (auto& substitutor : replace_actors)
  {
    auto it = actors.erase(actors.begin() + substitutor.first);
    actors.insert(it, std::move(substitutor.second));
  }
  replace_actors.clear();
}

void Actor::Tick(Game& game)
{
  DiscardRemovedChildren();
  AdaptNewChildren();
  SubstututeChildren();

  // tick children
  for (const UActor& actor : actors)
  {
    actor.get()->Tick(game);
  }
}