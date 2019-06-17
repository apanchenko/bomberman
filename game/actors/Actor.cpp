#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "actors/AMaze.h"

void Actor::Born(Game& game)
{
  game;
}

void Actor::Die(Game& game)
{
  game.GetScene<AMaze>()->Remove(this);
}

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

void Actor::AdaptNewChildren(Game& game)
{
  // move new children in separate cycle
  for (auto& actor : new_actors)
  {
    actor->Born(game);
    actors.push_back(std::move(actor));
  }
  new_actors.clear();
}

void Actor::SubstututeChildren(Game& game)
{
  for (auto& substitutor : replace_actors)
  {
    substitutor.second->Born(game);
    auto it = actors.erase(actors.begin() + substitutor.first);
    actors.insert(it, std::move(substitutor.second));
  }
  replace_actors.clear();
}

void Actor::Tick(Game& game)
{
  DiscardRemovedChildren();
  AdaptNewChildren(game);
  SubstututeChildren(game);

  // tick children
  for (const UActor& actor : actors)
  {
    actor.get()->Tick(game);
  }
}