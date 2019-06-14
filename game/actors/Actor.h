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
  A* Spawn()
  {
    new_actors.push_back(std::make_unique<A>());
    return static_cast<A*>(new_actors.back().get());
  }

  Actor* GetActor(int index) const
  {
    if (index < 0 || index >= actors.size())
      return nullptr;
    return actors[index].get();
  }

  virtual void  Tick(Game& game);

protected:
  void          AdaptNewChildren();

private:
  std::vector<UActor> actors;
  std::vector<UActor> new_actors;
};


// TODO: separate base and container actors

