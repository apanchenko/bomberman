#pragma once

#include "SDL.h"

class Actor
{
public:
  virtual void Tick(Uint32 delta);
};