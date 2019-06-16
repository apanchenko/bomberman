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

  template<class A>
  A*            Spawn();
  Actor*        GetActor(int index) const;
  void          Remove(Actor* actor);
  virtual void  Tick(Game& game);

protected:
  void          AdaptNewChildren();
  void          DiscardRemovedChildren();

private:
  std::vector<UActor> actors;        // children actors
  std::vector<Actor*> remove_actors; // actors to delete on next tick
  std::vector<UActor> new_actors;    // actors too add on next tick
};


// TODO: separate base and container actors

template<class A>
A* Actor::Spawn()
{
  new_actors.push_back(std::make_unique<A>());
  return static_cast<A*>(new_actors.back().get());
}