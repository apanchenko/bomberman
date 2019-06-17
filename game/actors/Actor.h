#pragma once

#include "SDL.h"
#include <memory>
#include <vector>

class Actor;
typedef std::unique_ptr<Actor> UActor; 
class Game;

class Actor
{
public:
  // add new actor
  template<class A>
  A*            Spawn();

  // insert new actor removing old one at index
  template<class A>
  A*            SpawnAndReplace(int index);

  // get actor by index
  Actor*        GetActor(int index) const;

  // remove specific actor
  void          Remove(Actor* actor);

  // tick one more precious moment
  virtual void  Tick(Game& game);

protected:
  void          AdaptNewChildren();
  void          DiscardRemovedChildren();
  void          SubstututeChildren();

private:
  std::vector<UActor> actors;        // child actors
  std::vector<Actor*> remove_actors; // actors to delete on next tick
  std::vector<UActor> new_actors;    // actors to add on next tick
  std::vector<std::pair<int, UActor>> replace_actors; // actors to replace at index
};


// TODO: separate base and container actors

template<class A>
A* Actor::Spawn()
{
  new_actors.push_back(std::make_unique<A>());
  return static_cast<A*>(new_actors.back().get());
}

template<class A>
A* Actor::SpawnAndReplace(int index)
{
  replace_actors.push_back(std::make_pair(index, std::make_unique<A>()));
  return static_cast<A*>(replace_actors.back().second.get());
}