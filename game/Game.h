#pragma once

#include "SDL.h"
#include "Actor.h"

// Initialize and manage subsystems
class Game
{
public:
  virtual            ~Game();

  bool                Init();
  void                Run();
  void                Quit();

  template<class A>
  A*        SwitchScene()
  {
    scene = std::make_unique<A>();
    return static_cast<A*>(scene.get());
  }

  SDL_Renderer*       GetRenderer() { return renderer; }

private:
  struct SDL_Window*  window        = nullptr;
  struct SDL_Renderer* renderer     = nullptr;
  struct SDL_Surface* screenSurface = nullptr;
  UActor              scene;
  bool                quit          = false;

  static const char*  TITLE;
  static const int    SCREEN_WIDTH  = 900;
  static const int    SCREEN_HEIGHT = 600;
};