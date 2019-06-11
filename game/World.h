#pragma once

#include "SDL_Timer.h"
#include <memory.h>


class World
{
public:
  void Tick(Uint32 delta);

  template<class S>
  S* SetNextScene()
  {
    scene = std::make_unique<Scene>()
    return s.get();
  }

private:
  std::unique_ptr<Scene> scene;
};