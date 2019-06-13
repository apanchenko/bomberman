#include "APlayer.h"
#include "../Game.h"

APlayer::APlayer()
{
  SetColor(200, 100, 100);
  SetSpeed(150);
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
        forces.push_front(Force(dir, event.key.timestamp));
      }
    }
    else if (event.type == SDL_KEYUP)
    {
      Dir dir = GetDirection(event.key);
      if (dir != Dir::None)
      {
        forces.remove_if([dir](auto force) { return force.dir == dir; });
        if (!forces.empty())
        {
          forces.front().start = game.GetNow();
        }
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
  // find force in valid direction by largest timestamp (last)
  for (auto force : forces)
  {
    if (GetCanMove(force.dir))
    {
      // apply force during time passed
      const Force& force = forces.front();
      Move(force.dir, game.GetNow() - force.start);
      // update force start moment
      force.start = game.GetNow();
      break;
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