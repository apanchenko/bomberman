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
  virtual void  SetPos(Pos pos) override;

  virtual void  Tick(Game& game) override;

private:
  void          ProcessInputEvents(Game& game);
  void          ApplyForce(Game& game);
  void          ApplySnap(Game& game);
  Dir           GetDirection(SDL_KeyboardEvent key) const;
  bool          IsMoving(Game& game) const;

  std::array<Force, Dirs.size()> forces;
};

// TODO: snap to nearest pos, not original