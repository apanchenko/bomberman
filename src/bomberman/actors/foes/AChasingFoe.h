#pragma once
#include "actors/ACharacter.h"
#include <list>

class APlayer;

class AChasingFoe : public ACharacter
{
  typedef ACharacter Base;

public:
  AChasingFoe();

  virtual void  Tick(Game& game) override;

private:
  // update current target position and search new path if need
  void          Retarget(APlayer* player);

  // define Path as a sequence of adjacent positions (source .. target]
  typedef std::list<Pos> Path;

  // search path from source to target using A* algorithm
  Path          SearchPath(Pos source, Pos target) const;

  // path to player position
  Path          path;
};