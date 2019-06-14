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
  Pos operator * (int mult)  const { return Pos(x * mult, y * mult); }
  Pos operator / (int div)   const { return Pos(x / div, y / div); }
  Pos operator %=(int mod)         { x %= mod; y %= mod; return *this; }
  Pos operator + (Pos other) const { return Pos(x + other.x, y + other.y); }
  Pos operator +=(Pos other)       { x += other.x; y += other.y; return *this; }

  // do one step in direction
  Pos operator + (Dir dir) const
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

  Dir ToDir() const
  {
    if (x > 0) return Dir::Right;
    if (x < 0) return Dir::Left;
    if (y > 0) return Dir::Down;
    if (y < 0) return Dir::Up;
    return Dir::None;
  }

  // check if this pos is inside zero based rectangle with size
  bool IsIn(Pos size)
  {
    return x >= 0 && y >= 0 && x < size.x && y < size.y;
  }
};
