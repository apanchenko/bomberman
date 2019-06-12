#pragma once
#include "ACell.h"

class AMaze;

enum class Momentum { Idle, Up, Right, Down, Left };

// Character actor
//   - can move in maze
class ACharacter : public ACell
{
private:
  typedef ACell Base;

public:
  void          SetMaze(AMaze* _maze)  { maze = _maze; }
  void          SetSpeed(float _speed) { speed = _speed; }

  // start moving one cell in certain direction
  void          MoveUp();
  void          MoveRight();
  void          MoveDown();
  void          MoveRight();

  virtual void  Tick(Game& game, Uint32 delta) override;

private:
  //
  AMaze*        maze  = nullptr;

  // move speed in pixels/second
  float         speed = 10;

  // 
  Momentum      momentum;
};