#include "pch.h"

#include "Pathfinding.h"
#include <functional>
#

#define SQRT2ASTAR 1.41421356237

//initialize weight at beginning can be changed
float Node::weight = 1.0f;

float Node::getTotalCost() const
{
  //1.01 to break ties
  return givenCost * 1.001f + (heuristic * weight);
}

void Node::calcHeuristic(const GridPos& goal)
{
  float xDiff, yDiff;
  
  //assuming for GridPos row = x and col = y
  xDiff = abs(goal.row - x);
  yDiff = abs(goal.col - y);
  heuristic = std::min(xDiff,yDiff) * sqrt(2.0f)
    + std::max(xDiff, yDiff) - std::min(xDiff, yDiff);

}

//fill map structure
void AStarPather::precalcMap(Map* mapData)
{
  map.map.clear();
  //for width by height
  height = mapData->height;
  width = mapData->width;
  sizeInWorld = mapData->width;
  map.map.reserve(width);  //reserve max capacity
  for(unsigned x = 0; x < width; ++x)
  {
    std::vector<Node> mapSubVec;
    mapSubVec.reserve(height);
    for (unsigned y = 0; y < height; ++y)
    {
      if(mapData->is_valid_grid_position(y,x))
      {
        Node node(x, y);
        node.onList = olUncheckedNode;
        

        if (mapData->getNode(y, x).type == mntObject)
          node.onList = olWallNode;

        mapSubVec.push_back(node);
        
      }
    }
    map.map.push_back(mapSubVec);
  }
}

bool AStarPather::initialize()
{
  // handle any one-time setup requirements you have

  //Callback cb = std::bind(&AStarPather::precalcMap, this);
  //Messenger::listen_for_message(Messages::MAP_CHANGE, cb);
  

   return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
  /*
    Free any dynamically allocated memory or any other general house-
    keeping you need to do during shutdown.
  */
}

PathResult AStarPather::compute_path(PathRequest &request)
{
  //first time for every new request
  if(request.newRequest)
  {
    precalcMap(request.map);
    debugColoring = request.settings.debugColoring;
    rubberBanding = request.settings.rubberBanding;
    smoothing = request.settings.smoothing;
    start = request.map->get_grid_position(request.start);
    std::swap(start.row, start.col);

    goal = request.map->get_grid_position(request.goal);
    std::swap(goal.row, goal.col);

    //in the case that you click on yourself
    if(start == goal)
      return PathResult::COMPLETE;
    //have to invert start coords????
    /*
    if (debugColoring)
    {
      request.map->set_color(start.col, start.row, Colors::Green);
      request.map->set_color(goal.col, goal.row, Colors::Red);
    }
    */


    Node::weight = request.settings.weight;
    //need to reset open list...
    
    for(auto& mapVec: map.map)
    {
      for(auto& node: mapVec)
      {
        if(node.onList != olWallNode)
          node.onList = olUncheckedNode;
        node.xParent = 0;
        node.yParent = 0;
        node.givenCost = 0;
        
      }
    }
    openList.clear();
    finalList.clear();

    //Push Start Node onto the Open List

    map.getNode(start).onList = olOpenList;
    map.getNode(start).calcHeuristic(goal);

    openList.push_back(map.getNode(start));

  }

  //    While (Open List is not empty) 
  while(!openList.empty())
  {
    //this is the only copy of the node besides the map
    Node node = getCheapest();  //TODO 20%
    //Pop cheapest node off Open List (parent node)
    //openList.pop(); //popped in getCheapest();

    // If node is the Goal Node, then path found (RETURN “found”)


    //Place parent node on the Closed List (we’re done with it)
    node.onList = olClosedList;
    map.getNode(node).onList = olClosedList;
    //if (debugColoring)
    //   request.map->set_color(node.y, node.x, Colors::Yellow);

    //Path is "complete"
    if (goal.row == node.x && goal.col == node.y)
    {
      
      
      Node* nodePtr = &node;
      
      while(nodePtr->xParent != start.row || nodePtr->yParent != start.col)
      {
        finalList.push_front({ nodePtr->x, nodePtr->y });
        
        
        nodePtr = &map.getNode(nodePtr->xParent, nodePtr->yParent);
      }
      
      finalList.push_front({ nodePtr->x, nodePtr->y });
      finalList.push_front({ start.row, start.col });

      if(rubberBanding)
        Rubberbanding(finalList);

      if(smoothing)
      {
        
        std::list<glm::vec2> finalListVec3;
        for (auto& waypoint : finalList)
        {
          finalListVec3.push_back(request.map->get_world_position(waypoint.col, waypoint.row));
        }

        CalmullRomSpline(finalListVec3);
        request.path = finalListVec3;
      }
      else  //if not smoothing dont allot new list for no reason }
      {
        for (auto& waypoint : finalList)
        {
          request.path.push_back(request.map->get_world_position(waypoint.col, waypoint.row));
        }
      }


      return PathResult::COMPLETE; 
    }

    allNeighborNodes(map.getNode(node));  //60%
    if (request.settings.singleStep)
      return PathResult::PROCESSING;
  }

  return PathResult::IMPOSSIBLE;
}

void AStarPather::Rubberbanding(std::list<GridPos>& list)
{
  //NEED vector so that can iterate with i and not iterators as the size WILL change
  std::vector<GridPos> pos;
  for(auto& var: list)
  {
    pos.push_back(var);
  }
  //for each node
  //can we eliminate the middle node 
  //aka make square of first and third node and see if there are any walls in there
  //if so then erase that node and retry with the same first node
  for(unsigned i = 0; i < pos.size() - 2; ++i)
  {
    int xMax, xMin, yMax, yMin;
    xMin = std::min(pos[i].row, pos[i + 2].row);
    xMax = std::max(pos[i].row, pos[i + 2].row);

    yMin = std::min(pos[i].col, pos[i + 2].col);
    yMax = std::max(pos[i].col, pos[i + 2].col);
    bool valid = true;

    //Check in the square around the nodes
    for(int j = xMin; j <= xMax; ++j)
    {
      for (int k = yMin; k <= yMax; ++k)
      {
        if(map.getNode(j,k).onList == olWallNode 
          || map.getNode(j, k).onList == olINVALIDNODE)
        {
          valid = false;
          break;
        }
      }
      if (!valid)
        break;
    }
    if(valid)
    {
      pos.erase(pos.begin() + i + 1);
      --i;  //have to recheck next 3 nodes
      
    }
  }
  
  list.clear();
  for (auto& var : pos)
  {
    list.push_back(var);
  }
}

void AStarPather::CalmullRomSpline(std::list<glm::vec2>& list)
{
  std::vector<glm::vec2> pos;
  for (auto& var : list)
  {
    pos.push_back(var);
  }
  //Add points back in (when > 1.5) on smoothing side
  
  for (unsigned i = 0; i < pos.size() - 1; ++i)
  {
    float xDiff = abs(pos[i].x - pos[i + 1].x);
    float yDiff = abs(pos[i].y - pos[i + 1].y);
    float distance = sqrtf((xDiff * xDiff) + (yDiff * yDiff));
    if (distance > 1.5 * (sizeInWorld / height))
    {
      //inserts halfway between both points
      pos.insert(pos.begin() + i + 1, interpPos(pos[i], pos[i + 1], 0.5f));
      --i;
    }
  }

  if (pos.size() <= 2)
    return;
  //always is 3 points
  glm::vec2 first;
  glm::vec2 second;
  glm::vec2 third;
  glm::vec2 fourth;
  //isnt i < pos.size() - 2 because we have a case to handle the last part
  for (unsigned i = 0; i < pos.size() - 1; i += 4)
  {
    
    //if beginning
    if (i == 0)
    {
      first  = pos[0];
      second = pos[0];
      third  = pos[1];
      fourth = pos[2];


    }

    //if end
    else if (i == pos.size() - 2) //needs to be - 2 to stay in bounds
    {
      first  = pos[i - 4];
      second = pos[i + 0];
      third  = pos[i + 1];
      fourth = pos[i + 1];
    }
    //if any in the middle
    else
    {
      first  = pos[i - 4];
      second = pos[i + 0];
      third  = pos[i + 1];
      fourth = pos[i + 2];
      
    }
    glm::vec2 spline = Vec3CatmullRom(
      first, second, third, fourth,
      0.25f);
    pos.insert(pos.begin() + i + 1, spline);

    spline = Vec3CatmullRom(
      first, second, third, fourth,
      0.50f);
    pos.insert(pos.begin() + i + 2, spline);

    spline = Vec3CatmullRom(
      first, second, third, fourth,
      0.75f);
    pos.insert(pos.begin() + i + 3, spline);

  }

  list.clear();
  for (auto& var : pos)
  {

    list.push_back(var);
  }
}

Node AStarPather::getCheapest()
{
  float cheapest = openList.front().getTotalCost();
  unsigned nodeNum = 0;
  for (unsigned i = 0; i < openList.size(); ++i)
  {
    //openList.at(i).calcHeuristicAndCost(goal, heur);
    float cost = openList.at(i).getTotalCost();
    if (cost < cheapest)
    {
      nodeNum = i;
      cheapest = cost;
    }
  }
  Node cheap = openList.at(nodeNum);
  //swaps back node with cheapest and pops cheapest
  std::swap(openList.back(), openList.at(nodeNum));
  openList.pop_back();
  return cheap;
}


void AStarPather::allNeighborNodes(Node& node)
{

  //i = x, j = y
  
  int x = map.getNode(node).x;
  int y = map.getNode(node).y;
  for(int i = -1; i <= 1; ++i)
  {
    for (int j = -1; j <= 1; ++j)
    {
  //Node newNode;
      bool diagonal = false;
      //node = map.getNode(x,y)
      //if neighbor is outside map
      if (i == 0 && j == 0)
        continue;
      if(x + i < 0 || y + j < 0 
        || x + i >= width || y + j >= height)
      {
        continue;
      }
      if ((abs(i) == 1 && abs(j) == 1))
        diagonal = true;

      //if diagonal and not valid
      if (diagonal 
       && (map.getNode(x + i, y).onList == olWallNode
       || map.getNode(x, y + j).onList == olWallNode))
      {
        //will skip if diagonal and an invalid node
        continue;
      }
      
      if (map.getNode(x + i, y + j).onList == olWallNode)
      {
        continue;
      }
      //Compute its cost, f(x) = g(x) + h(x)
      if(map.getNode(x + i, y + j).onList == olUncheckedNode)
      {
        map.getNode(x + i, y + j).calcHeuristic(goal);
      }

      //If child node isn’t on Open or Closed list, put it on Open List.
      if(map.getNode(x + i, y + j).onList != olWallNode 
        && map.getNode(x + i, y + j).onList != olClosedList)
      {
        float cost = 1;
        if (diagonal)
          cost = SQRT2ASTAR;
        map.getNode(x + i, y + j).setParent(map.getNode(x, y));
        map.getNode(x + i, y + j).givenCost = map.getNode(x, y).givenCost + cost;

        //add neighbor to open_list
        //moving this get parent line to here instead of the if above 
        //made it better
        if (map.getNode(x + i, y + j).onList != olOpenList)
        {
          map.getNode(x + i, y + j).onList = olOpenList;

          openList.push_back(map.getNode(x + i, y + j));

          //if (debugColoring)
          //  request.map->set_color(y + j, x + i,  Colors::Blue);


        }
        //  else
        else 
        {
          for(auto& openNode:openList)
          {
            //if neighbor is cheaper than open list
            if(openNode == map.getNode(x + i, y + j))
            {
              if (map.getNode(x + i, y + j).getTotalCost() < openNode.getTotalCost())
              {

                openNode.givenCost = map.getNode(x + i, y + j).givenCost;
                openNode.xParent = map.getNode(x + i, y + j).xParent;
                openNode.yParent = map.getNode(x + i, y + j).yParent;

              }
              else
              {
                map.getNode(x + i, y + j).givenCost = openNode.givenCost;
                map.getNode(x + i, y + j).xParent = openNode.xParent;
                map.getNode(x + i, y + j).yParent = openNode.yParent;
              }

            }
              
          }
        }
      }
    }
  }
  return;
}
