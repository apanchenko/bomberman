#pragma once
#include "actors/ACharacter.h"
#include <list>

class AChasingFoe : public ACharacter
{
  typedef ACharacter Base;

public:
  AChasingFoe();

  virtual void  Tick(Game& game) override;

private:
  void          Retarget();

  // define Path as a sequence of adjacent positions (source .. target]
  typedef std::list<Pos> Path;

  // A* 
  Path          SearchPath(Pos source, Pos target) const;


  Path          path; // path to player position
};