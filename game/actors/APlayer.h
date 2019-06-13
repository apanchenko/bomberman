#pragma once
#include "ACharacter.h"
#include <map>
#include "../types/Force.h"
#include <list>

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
  Dir           GetLastForce() const;

  // move actions 
  std::map<Dir, Force> forces;
  //std::list<Force>
};

