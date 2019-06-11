#pragma once

class Scene
{
public:
  A* AddActor<class A>()
  {
    actors.push_back(std::make_unique<Scene>())
    return actors.last()->get();
  }

private:
  std::vector<unique_ptr<Actor>> actors;
};