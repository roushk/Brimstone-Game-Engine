#pragma once
#include <list>

#include "glm/vec2.hpp"
#include "Map.h"

class Map;

enum ONLIST
{
  olClosedList,
  olOpenList,
  olUncheckedNode,
  olWallNode,
  olINVALIDNODE
  
};
enum PathResult
{
  IMPOSSIBLE,
  COMPLETE,
  PROCESSING
};

struct PathRequest
{
  glm::vec2 start;
  glm::vec2 goal;
  Map* map;
  std::list<glm::vec2> path;

  struct Settings
  {
    float weight = 1.0f;
    bool smoothing = true;
    bool rubberBanding = true;
    bool singleStep = false;
    bool debugColoring = false;
  } settings;

  bool newRequest = true;
};

class Node
{
public:
  Node(unsigned short x_,
    unsigned short y_)
  {
    x = x_;
    y = y_;
  }
  Node(const GridPos& pos)
  {
    x = pos.row;
    y = pos.col;
  }
  bool operator!=(const Node& rhs)
  {
    if (x != rhs.x || y != rhs.y)
      return true;
    else
      return false;
  }
  bool operator==(const Node& rhs)
  {
    if (x == rhs.x && y == rhs.y)
      return true;
    else
      return false;
  }

  float getTotalCost() const;

  void calcHeuristic(const GridPos& goal);

  void setParent(const Node& node)
  {
    xParent = node.x;
    yParent = node.y;
  }
  //only 4 bits for ushort
  unsigned short x = 0;
  unsigned short y = 0;
  unsigned short xParent = -1;
  unsigned short yParent = -1;


  //Node* parent = nullptr;
  unsigned onList = olUncheckedNode;

  //heuristic = cost - given
  bool operator()(const Node& lhs, const Node& rhs)
  {
    return givenCost + heuristic > rhs.givenCost + heuristic;
  }
  
  static float weight;
  float givenCost = 0; //total cost
  float heuristic = 0;  //given cost
private:
};

class AStarMap
{
  public:
  //width then height
  Node& getNode(unsigned x, unsigned y) { return map[x][y]; };
  Node& getNode(const Node& node) { return map[node.x][node.y]; };
  Node& getParent(const Node& node) { return map[node.xParent][node.yParent]; };
  
  //TODO FIX THIS IS NOT DONE
  //make sure map is adding walls to the list as we are using the index as
  //the positon...
  std::vector<std::vector<Node>> map;
  //std::vector<std::vector<Node>> mapBackup; //much slower


};


inline glm::vec2 interpPos(glm::vec2 a, glm::vec2 b, float s)
{
  return (1.0f - s) * a + s * b;
}

inline glm::vec2 Vec3CatmullRom(glm::vec2 pV1, glm::vec2 pV2, glm::vec2 pV3, glm::vec2 pV4, float s)
{

  return pV1 * glm::vec2(-0.5*s*s*s + s * s - 0.5*s) +
    pV2 * glm::vec2(1.5*s*s*s + -2.5*s*s + 1.0) +
    pV3 * glm::vec2(-1.5*s*s*s + 2.0*s*s + 0.5*s) +
    pV4 * glm::vec2(0.5*s*s*s - 0.5*s*s);
}


class AStarPather
{
public:
  //type, container, 
  //std::priority_queue<Node, std::vector<Node>, Node> openList;
  //replaces other node with this one if there is the same node in the list
  Node getCheapest();

  void Rubberbanding(std::list<GridPos>& list);
  void CalmullRomSpline(std::list<glm::vec2>& list);

  GridPos start;
  GridPos goal;
  std::list<GridPos> finalList;

  bool debugColoring = false;
  bool rubberBanding = false;
  bool smoothing = false;
  float width, height, sizeInWorld;

  void allNeighborNodes(Node& node);

  std::vector<Node> openList;
  AStarMap map;
  /* 
      The class should be default constructible, so you may need to define a constructor.
      If needed, you can modify the framework where the class is constructed in the
      initialize functions of ProjectTwo and ProjectThree.
  */
  void precalcMap(Map* mapData);
  /* ************************************************** */
  // DO NOT MODIFY THESE SIGNATURES
  bool initialize();
  void shutdown();
  PathResult compute_path(PathRequest &request);
  /* ************************************************** */

  /*
      You should create whatever functions, variables, or classes you need.
      It doesn't all need to be in this header and cpp, structure it whatever way
      makes sense to you.
  */

};



/*
 void FloydWarshall()

{

for (k = 1 to n)

{

for each (i,j) in (1..n)

{

path[i][j] = min ( path[i][j],

path[i][k] + path[k][j] );

}

}

}
 */

