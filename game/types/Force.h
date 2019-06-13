#pragma once
#include "Types.h"

class Interval
{
public:
  Interval()
    : start(0)
    , stop(0)
  {}

  Interval(bb::Time _start, bb::Time _stop = bb::NEVER)
    : start(_start)
    , stop(_stop)
  {}

  mutable bb::Time  start;
  mutable bb::Time  stop;
};