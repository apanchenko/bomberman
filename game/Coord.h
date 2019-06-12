#pragma once

// pixel coordinate
struct Coord
{
  int x = 0;
  int y = 0;

  Coord(int _x, int _y)
    : x(_x), y(_y)
  {}

  Coord operator * (int mult)     { return Coord(x * mult, y * mult); }
  Coord operator + (Coord other)  { return Coord(x + other.x, y + other.y); }
};

