#include <stdio.h>
#include <windows.h>
#include "Game.h"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
  Game game;
  if (game.Init())
  {
    game.Run();
  }

	return 0;
}