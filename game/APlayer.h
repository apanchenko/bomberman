#pragma once
#include "ACharacter.h"

class APlayer : public ACharacter
{
private:
  typedef ACharacter Base;

public:
  virtual void Tick(Game& game, Uint32 delta) override;
};

