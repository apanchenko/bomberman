#include "APlayer.h"
#include "Game.h"

void APlayer::Tick(Game& game, Uint32)
{
  SDL_Event event;

  if (SDL_PollEvent(&event) != 0)
  {
    if (event.type == SDL_QUIT)
    {
      game.Quit();
    }

    else if (event.type == SDL_KEYDOWN)
    {
      //switch (event.key.keysym)
      //{
      //  case 
      //}
    }
  }
}