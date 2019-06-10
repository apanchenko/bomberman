#include "Game.h"
#include <SDL.h>

const char* Game::TITLE = "Bomberman";

Game::~Game()
{
  if (window != nullptr)
    SDL_DestroyWindow(window);

  SDL_Quit();
}

bool Game::Init()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_Log(__FUNCTION__ "SDL could not initialize: %s", SDL_GetError());
    return false;
  }

  // Create window
  window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL)
  {
    SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
  }

  screenSurface = SDL_GetWindowSurface(window);
  return true;
}

void Game::Run()
{
  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);

  SDL_Delay(5000);

  SDL_Log("SDL OK!");
}