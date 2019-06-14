#pragma once
#include "ACharacter.h"

class ARoamingFoe : public ACharacter
{
  typedef ACharacter Base;

public:
  ARoamingFoe();

  virtual void  Tick(Game& game) override;

private:
  Dir           roam_dir; // roaming direction, selected randomly
};

// TODO: prefer not selecting backward direction