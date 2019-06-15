#include "APlayer.h"
#include "Game.h"
#include "actors/AMaze.h"
#include "actors/foes/ARoamingFoe.h"
#include "actors/foes/AChasingFoe.h"
#include <algorithm>

APlayer::APlayer()
{
  SetColor(255, 255, 0);
  SetSpeed(100);
}

void APlayer::SetPos(Pos pos)
{
  if (GetPos() != pos)
  {
    SDL_Log("New player position {%i, %i}", pos.x, pos.y);
  }
  Base::SetPos(pos);
}

void APlayer::Tick(Game& game)
{
  ProcessInputEvents(game);
  if (IsMoving(game))
    ApplyForce(game);
  else
    ApplySnap(game);
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
      else if (event.key.keysym.sym == SDLK_r)
      {
        Maze()->SpawnAtFreeCell<ARoamingFoe>();
      }
      else if (event.key.keysym.sym == SDLK_c)
      {
        Maze()->SpawnAtFreeCell<AChasingFoe>();
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
    bb::Time start = std::clamp(force.start, game.GetStartFrame(), game.Now());
    bb::Time stop  = std::clamp(force.stop, game.GetStartFrame(), game.Now());
    if (start < stop)
    {
      // apply force
      Move(force.dir, stop - start, false);
    }
  }
}

void APlayer::ApplySnap(Game& game)
{
  auto snap = [](int v, int dist, int& pos) -> int
  {
    if (v > 0)
    {
      if (v < Size / 2) // snap back to pos
      {
        v -= std::min(dist, v);
      }
      else // snap to next pos
      {
        pos++;
        v -= Size - std::min(dist, Size - v);
      }
    }
    else if (v < 0)
    {
      if (v > -Size / 2) // snap back to pos
      {
        v += std::min(dist, -v);
      }
      else // snap to lower next pos
      {
        pos--;
        v += Size - std::min(dist, Size + v);
      }
    }
    return v;
  };

  // max distance player can move in one frame
  int dist = game.GetFrameDuration() * GetSpeed() / 1000;
  Pos pos = GetPos();
  Pos shift = GetShift();

  shift.x = snap(shift.x, dist, pos.x);
  shift.y = snap(shift.y, dist, pos.y);

  SetPos(pos);
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
  // find non-finished force in available direction
  for (auto& force : forces)
  {
    if (force.stop > game.Now() && CanMove(force.dir))
      return true;
  }
  return false;
}
