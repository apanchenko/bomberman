#pragma once

// actor position in maze
struct Pos
{
  int i = 0;
  int j = 0;

  Coord operator * (int mult)     { return Coord(x * mult, y * mult); }

};

