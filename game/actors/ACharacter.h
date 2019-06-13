#pragma once
#include "ACell.h"
#include "../types/Dir.h"

class AMaze;



// Character actor
//   - can move in maze
class ACharacter : public ACell
{
private:
  typedef ACell Base;

public:
  void          SetMaze(AMaze* _maze)  { maze = _maze; }
  void          SetSpeed(Uint32 _speed) { speed = _speed; }

  // move in certain direction
  bool          GetCanMove(Dir dir);
  void          Move(Dir dir, Uint32 duration);

  virtual void  Tick(Game& game) override;

private:
  // space we are moving in
  AMaze*        maze  = nullptr;

  // move speed in pixels/second
  Uint32        speed = 10;

  // subpixel shift, will be utillized in future movement
  Pos           sub_shift;
};