#pragma once
#include "Dir.h"

// 2D position coordinates
struct Pos
{
  int x;
  int y;

  // constructors
  Pos() : x(0), y(0) {}
  Pos(int _x, int _y) : x(_x), y(_y) {}

  // basic math operators
  Pos operator * (int mult)   { return Pos(x * mult, y * mult); }
  Pos operator / (int div)    { return Pos(x / div, y / div); }
  Pos operator %=(int mod)    { x %= mod; y %= mod; return *this; }
  Pos operator + (Pos other)  { return Pos(x + other.x, y + other.y); }
  Pos operator +=(Pos other)  { x += other.x; y += other.y; return *this; }

  // do one step in direction
  Pos operator + (Dir dir)
  {
    switch (dir)
    {
    case Dir::Up:     return Pos(x, y - 1);
    case Dir::Right:  return Pos(x + 1, y);
    case Dir::Down:   return Pos(x, y + 1);
    case Dir::Left:   return Pos(x - 1, y);
    }
    return *this;
  }

  // check if this pos is inside zero based rectangle with size
  bool IsIn(Pos size)
  {
    return x >= 0 && y >= 0 && x < size.x && y < size.y;
  }
};
