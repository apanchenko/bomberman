#pragma once

#include "SDL.h"
#include <memory>
#include "actors/APlayer.h"

// Initialize and manage subsystems
class Game
{
public:
  virtual            ~Game();
  bool                Init();
  void                Run();

  SDL_Renderer*       GetRenderer() { return renderer; }

  // frame timing
  Uint32              GetStartFrame()     const { return time_now - frame_duration; }
  Uint32              Now()               const { return time_now; }
  Uint32              GetFrameDuration()  const { return frame_duration; }

  // scene
  template<class A>
  A*                  GetScene()          const;

  // input controller
  void                SetPlayer(APlayer* _player) { player = _player; }
  APlayer*            Player()            const { return player; }

private:
  void                ProcessInputEvents();

  static const char*  TITLE;
  static const int    SCREEN_WIDTH = 1150;
  static const int    SCREEN_HEIGHT = 650;

  struct SDL_Window*  window        = nullptr;
  struct SDL_Renderer* renderer     = nullptr;
  struct SDL_Surface* screenSurface = nullptr;
  UActor              scene;
  APlayer*            player        = nullptr; // the only event handler
  bool                quit          = false;
  Uint32              time_now      = 0;
  Uint32              frame_duration = 0;
};


template<class A>
A* Game::GetScene() const
{
  return static_cast<A*>(scene.get());
}
