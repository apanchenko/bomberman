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
  if (IsMoving(game))
    ApplyForce(game);
  else
    ApplySnapForce(game);
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
        forces[(int)dir] = Force(dir, event.key.timestamp);
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
        forces[(int)dir].stop = event.key.timestamp;
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
  auto copy = forces;
  std::sort(copy.begin(), copy.end(), [](const Force& a, const Force& b)
  {
    return a.start > b.start;
  });

  for (Force& force : copy)
  {    
    // calculate force duration during last frame
    bb::Time start = std::clamp(force.start, game.GetStartFrame(), game.GetNow());
    bb::Time stop  = std::clamp(force.stop, game.GetStartFrame(), game.GetNow());
    
    if (start < stop)
    {
      // apply force
      Move(force.dir, stop - start);
    }
  }
}

void APlayer::ApplySnapForce(Game& game)
{
  // max distance player can move in this frame
  int path = game.GetFrameDuration() * GetSpeed() / 1000;

  Pos shift = GetShift();
  if (shift.x > 0 && shift.x < Snap)
  {
    shift.x -= std::min(shift.x, path);
  }
  else if (shift.x < 0 && shift.x > -Snap)
  {
    shift.x += std::min(-shift.x, path);
  }

  if (shift.y > 0 && shift.y < Snap)
  {
    shift.y -= std::min(shift.y, path);
  }
  else if (shift.y < 0 && shift.y > -Snap)
  {
    shift.y += std::min(-shift.y, path);
  }

  SetShift(shift);
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

bool APlayer::IsMoving(Game& game) const
{
  // find non-finished force
  for (auto& force : forces)
  {
    if (force.stop > game.GetNow())
      return true;
  }
  return false;
}
