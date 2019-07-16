#pragma once
#include <array>

enum class Dir
{
  Up    = 0,
  Right = 1,
  Down  = 2,
  Left  = 3,
  None
};

extern const std::array<Dir, 4> Dirs;

// TODO: initialize by default to None
// TODO: random_dir function