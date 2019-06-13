#pragma once

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
};
