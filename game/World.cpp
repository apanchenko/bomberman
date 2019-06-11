#include "World.h"
#include "SDL.h"

void World::Tick(Uint32 delta)
{
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);
}