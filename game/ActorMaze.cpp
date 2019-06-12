#include "ActorMaze.h"
#include "ActorWall.h"

AMaze::AMaze()
{
  AddActor<ActorWall>();
}