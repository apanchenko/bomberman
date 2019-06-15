#include "Game.h"
#include "actors/AMaze.h"
#include <ctime>

const char* Game::TITLE = "Amazed Bomberman";

Game::~Game()
{
  if (renderer != nullptr)
    SDL_DestroyRenderer(renderer);

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
  if (window == nullptr)
  {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr)
  {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  // init random numbers
  ::srand((int) std::time(nullptr));

  screenSurface = SDL_GetWindowSurface(window);

  SwitchScene<AMaze>();
  return true;
}

void Game::Run()
{
  Uint32 time_last = SDL_GetTicks();
  while (!quit)
  {
    SDL_RenderClear(renderer);

    time_now = SDL_GetTicks();
    frame_duration = time_now - time_last;
    scene->Tick(*this);
    time_last = time_now;

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }
  SDL_Log(__FUNCTION__ ". End of the game");
}

void Game::Quit()
{
  SDL_Log(__FUNCTION__);
  quit = true;
}