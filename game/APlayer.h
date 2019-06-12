#pragma once
#include "ACharacter.h"

class APlayer : public ACharacter
{
public:
  virtual void Tick(Game& game, Uint32 delta) override;
};

