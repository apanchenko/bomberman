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
  A* AddActor()
  {
    actors.push_back(std::make_unique<A>());
    return static_cast<A*>(actors.back().get());
  }

  virtual void Tick(Game& game, Uint32 delta);

private:
  std::vector<UActor> actors;
};

