#include "AChasingFoe.h"
#include "Game.h"
#include "actors/AMaze.h"
#include "actors/APlayer.h"
#include <set>

AChasingFoe::AChasingFoe()
{
  SetColor(100, 0, 0);
  SetSpeed(90);
}

void AChasingFoe::Retarget()
{
  APlayer* player = Maze()->Player();
  if (player == nullptr)
  {
    // target not found - stop
    path.clear();
    return;
  }

  Pos target = player->GetPos();
  if (!path.empty() && path.back() == target)
  {
    // target position not changed - continue chasing
    return;
  }

  // target position changed - search new path
  path = SearchPath(GetPos(), target);
}

// A* search path algorithm node
struct Node
{
  Pos pos;
  Pos parent;
  int source_price;
  int target_price;

  Node(Pos pos, Pos parent, int src, int tgt)
    : pos(pos)
    , parent(parent)
    , source_price(src)
    , target_price(tgt)
  {}
  int Price() const { return source_price + target_price; }

  bool operator < (const Node& other) const
  {
    if (pos.x != other.pos.x)
      return pos.x < other.pos.x;
    return pos.y < other.pos.y;
  }

  Node Next(Dir dir, Pos target)
  {
    Pos next = pos + dir;
    return Node(next, pos, source_price + 1, next.DistanceTo(target));
  }
};

AChasingFoe::Path AChasingFoe::SearchPath(Pos source, Pos target) const
{
  if (source == target)
    return Path();

  std::set<Node> open;
  std::set<Node> closed;

  // helper to find node by position
  auto find_by_pos = [](std::set<Node>& list, Pos pos)
  {
    return std::find_if(list.begin(), list.end(), [pos](const Node& n) { return n.pos == pos; });
  };
  
  // insert starting position into open list
  Node node(source, source, 0, source.DistanceTo(target));
  open.insert(node);

  while (!open.empty())
  {
    // take best node from open list
    auto it = std::min_element(open.begin(), open.end(), [](const Node& a, const Node& b) { return a.Price() < b.Price(); });
    node = *it;
    open.erase(it);

    // consider all neighbors
    for (Dir dir : Dirs)
    {
      Node next = node.Next(dir, target);

      // wall detected
      if (Maze()->IsSolid(next.pos))
        continue;

      // if target reached - return path
      if (next.pos == target)
      {
        // complete closed list to trace path back
        closed.insert(node);
        std::list<Pos> new_path;
        do
        {
          new_path.push_front(next.pos);
          it = find_by_pos(closed, next.parent);
          if (it == closed.end())
          {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, __FUNCTION__ ". Failed to trace A* path back");
            return Path();
          }
          next = *it;
          if (next.pos == source)
            break;
          closed.erase(it); // ease closed list for faster trace
        } while (!closed.empty());
        return new_path;
      }

      // check if already have better path to this neighbour in open list
      it = find_by_pos(open, next.pos);
      if (it != open.end() && it->Price() < next.Price())
        continue;

      // check if already have better path to this neighbour in closed list
      it = find_by_pos(closed, next.pos);
      if (it != closed.end() && it->Price() < next.Price())
        continue;

      // consider this neighbor in main cycle later
      open.insert(next);
    }

    // node processed, archive
    closed.insert(node);
  }

  // path not found, return empty path
  return Path();
}

void AChasingFoe::Tick(Game& game)
{
  // if idle - update path to target
  if (GetShift().ToDir() == Dir::None)
  {
    Retarget();

    // start next step on path
    if (!path.empty() && path.front() == GetPos())
    {
      path.pop_front();
    }
  }

  // move in direction of next step in path
  if (!path.empty())
  {
    Dir dir = (path.front() - GetPos()).ToDir();
    Move(dir, game.GetFrameDuration(), true);
  }

  Base::Tick(game);
}