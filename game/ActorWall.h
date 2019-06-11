#pragma once

#include "Actor.h"

class ActorWall : public Actor
{
public:
  virtual void Tick(Uint32 delta);
};