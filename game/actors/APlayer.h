#pragma once
#include "ACharacter.h"
#include <map>
#include "../types/Force.h"
#include <array>

class APlayer : public ACharacter
{
private:
  typedef ACharacter Base;
  typedef std::array<Force, bb::DIRCOUNT> ForceArray;

  static const int Snap = Size / 1;

public:
  APlayer();
  virtual void  Tick(Game& game) override;

private:
  void          ProcessInputEvents(Game& game);
  void          ApplyForce(Game& game);
  void          ApplySnapForce(Game& game);
  Dir           GetDirection(SDL_KeyboardEvent key) const;
  bool          IsMoving(Game& game) const;

  ForceArray    forces;
};

