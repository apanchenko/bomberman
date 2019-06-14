#pragma once

#include "SDL.h"
#include <memory>
#include "actors/Actor.h"

// Initialize and manage subsystems
class Game
{
public:
  virtual            ~Game();

  bool                Init();
  void                Run();
  void                Quit();

  Uint32              GetStartFrame()     const { return time_now - frame_duration; }
  Uint32              Now()            const { return time_now; }
  Uint32              GetFrameDuration()  const { return frame_duration; }

  template<class A>
  A*                  SwitchScene()
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
  Uint32              time_now      = 0;
  Uint32              frame_duration = 0;

  static const char*  TITLE;
  static const int    SCREEN_WIDTH  = 1150;
  static const int    SCREEN_HEIGHT = 650;
};