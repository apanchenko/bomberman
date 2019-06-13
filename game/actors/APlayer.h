#pragma once
#include "ACharacter.h"
#include <map>
#include "../types/Force.h"
#include <array>

class APlayer : public ACharacter
{
private:
  typedef ACharacter Base;

public:
  APlayer();
  virtual void  Tick(Game& game) override;

private:
  void          ProcessInputEvents(Game& game);
  void          ApplyForce(Game& game);
  Dir           GetDirection(SDL_KeyboardEvent key) const;

  std::array<Interval, bb::DIRCOUNT> forces;
};

