#pragma once

class Game
{
public:
  virtual ~Game();
  bool Init();

  void Run();

private:
  struct SDL_Window*   window = nullptr;
  struct SDL_Surface*  screenSurface = nullptr;

  static const char*  TITLE;
  static const int    SCREEN_WIDTH = 900;
  static const int    SCREEN_HEIGHT = 600;
};