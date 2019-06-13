#pragma once
#include "Dir.h"
#include "Types.h"

class Force
{
public:
  Force()
    : dir(Dir::None)
    , start(0)
    , stop(0)
  {}

  Force(Dir _dir, bb::Time _start, bb::Time _stop = bb::NEVER)
    : dir(_dir)
    , start(_start)
    , stop(_stop)
  {}

  Dir       dir;
  mutable bb::Time  start;
  mutable bb::Time  stop;
};