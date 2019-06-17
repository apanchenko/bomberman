#pragma once
#include "Dir.h"

// 2D position coordinates
struct Pos
{
  int x;
  int y;

  // constructors
  Pos() : x(0), y(0) {}
  Pos(int v) : x(v), y(v) {}
  Pos(int x, int y) : x(x), y(y) {}

  // basic operators
  bool operator ==(Pos other) const { return x == other.x && y == other.y; }
  bool operator !=(Pos other) const { return x != other.x || y != other.y; }
  Pos  operator * (int mult)  const { return Pos(x * mult, y * mult); }
  Pos  operator / (int div)   const { return Pos(x / div, y / div); }
  Pos  operator + (Pos other) const { return Pos(x + other.x, y + other.y); }
  Pos  operator - (Pos other) const { return Pos(x - other.x, y - other.y); }
  Pos  operator +=(Pos other)       { x += other.x; y += other.y; return *this; }
  Pos  operator %=(int mod)         { x %= mod; y %= mod; return *this; }

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

  // convert to direction
  Dir ToDir() const
  {
    if (x > 0) return Dir::Right;
    if (x < 0) return Dir::Left;
    if (y > 0) return Dir::Down;
    if (y < 0) return Dir::Up;
    return Dir::None;
  }

  // calculate 1D array index of this position in 2D grid
  int ToIndex(Pos grid_size) const
  {
    return x * grid_size.y + y;
  }

  // Manhattan distance
  int DistanceTo(Pos other) const
  {
    return std::abs(x - other.x) + std::abs(y - other.y);
  }

  // check if this pos is inside zero based rectangle with size
  bool IsIn(Pos size) const
  {
    return x >= 0 && y >= 0 && x < size.x && y < size.y;
  }

  // check if this pos is inside rectangle defined by two corners
  bool IsIn(Pos low, Pos high) const
  {
    return x >= low.x && y >= low.y && x < high.x && y < high.y;
  }

  // clamp vector in rectangle defined by two corners
  Pos Clamp(Pos low, Pos high) const
  {
    return Pos(std::clamp(x, low.x, high.x),
               std::clamp(y, low.y, high.y));
  }
};
