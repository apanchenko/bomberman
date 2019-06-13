#pragma once
#include "ACell.h"
#include "../types/Dir.h"
#include "../types/Types.h"

class AMaze;

// Character actor
//   - can move in maze
class ACharacter : public ACell
{
private:
  typedef ACell Base;

public:
  bool          GetCanMove(Pos to) const;

  void          SetMaze(AMaze* _maze)  { maze = _maze; }
  void          SetSpeed(Uint32 _speed) { speed = _speed; }
  bool          Move(Dir dir, bb::Time duration);

  virtual void  Tick(Game& game) override;

private:
  AMaze*        maze  = nullptr;  // space we are moving in
  Uint32        speed = 10;       // move speed in pixels/second
};