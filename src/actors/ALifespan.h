#pragma once
#include "types/Types.h"
#include "Game.h"

template<class A>
class ALifespan : public A
{
  typedef A Base;

public:
  ALifespan()
    : lifespan(3000)
    , death_moment(bb::NEVER)
  {}

  virtual void  Die(Game& game) override        { Base::Die(game); }

  void          SetLifespan(bb::Time _lifespan) { lifespan = _lifespan; }
  void          Refresh(Game& game)             { death_moment = game.Now() + lifespan; }

  virtual void  Tick(Game& game) override;

private:
  bb::Time      lifespan;     // life expectancy
  bb::Time      death_moment; // known future moment of death
};


template<class A>
void ALifespan<A>::Tick(Game& game)
{
  if (game.Now() >= death_moment)
  {
    Die(game);
  }
  Base::Tick(game);
}