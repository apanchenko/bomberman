#pragma once
#include "ARect.h"

class AMaze;

class ACharacter : public ARect
{
public:
  void Move();

  ACharacter& SetMaze(AMaze* maze);

private:
  AMaze* maze;
};

