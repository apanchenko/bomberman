#include "APlayer.h"
#include "../Game.h"
#include <algorithm>

APlayer::APlayer()
{
  SetColor(200, 100, 100);
  SetSpeed(300);
}

void APlayer::Tick(Game& game)
{
  ProcessInputEvents(game);
  ApplyForce(game);
  Base::Tick(game);
}

void APlayer::ProcessInputEvents(Game& game)
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0)
  {
    if (event.type == SDL_KEYDOWN)
    {
      Dir dir = GetDirection(event.key);
      if (dir != Dir::None)
      {
        forces[(int)dir] = Interval(event.key.timestamp);
      }
      else if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        game.Quit();
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      Dir dir = GetDirection(event.key);
      if (dir != Dir::None)
      {
        forces[(int)dir].stop = game.GetNow();
      }
    }
    else if (event.type == SDL_QUIT)
    {
      game.Quit();
    }
  }
}

void APlayer::ApplyForce(Game& game)
{
  for (int d = 0; d < bb::DIRCOUNT; ++d)
  {
    Interval& force = forces[d];
    
    // calculate force duration during last frame
    bb::Time start = std::max(force.start, game.GetStartFrame());
    bb::Time stop = std::min(force.stop, game.GetNow());
    if (start < stop)
    {
      // apply force
      Move((Dir)d, stop - start);
    }
  }
}

Dir APlayer::GetDirection(SDL_KeyboardEvent key) const
{
  if (key.repeat != 0)
    return Dir::None;
  
  switch (key.keysym.sym)
  {
  case SDLK_UP:
  case SDLK_w:    return Dir::Up;

  case SDLK_RIGHT:
  case SDLK_d:    return Dir::Right;

  case SDLK_DOWN:
  case SDLK_s:    return Dir::Down;

  case SDLK_LEFT:
  case SDLK_a:    return Dir::Left;
  }

  return Dir::None;
}