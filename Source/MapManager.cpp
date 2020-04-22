//***************************************************************************
// Filename: MapManager.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"

MapManager::MapManager() : System()
{
  name = "Map Manager";
}

MapManager::~MapManager()
{

}

void MapManager::Update(float dt)
{
  UNREFERENCED_PARAMETER(dt);
  if(mapIncomplete)
  {
    if(GenerateMapUpdate())
    {
      mapFinished = true;
      mapIncomplete = false;
      maps.push_back(mapInProgress);
      engine.GetSystem<InputManager>()->map = &maps[maps.size() - 1];
    }

  }
}

void MapManager::GenerateMapLive(MazeGenerationMethod method)
{
  if(mapIncomplete == false)
  {
    mapIncomplete = true;
    mapFinished = false;
    currentMethod = method;

    if(method == MazeGenerationMethod::RandomizedPrims)
    {
      //init the map to a new map
      mapInProgress = Map(newWidth, newHeight);

      //generate it
      GenerateMazePrimsInit();
    }
  }
  else
  {
    std::cout << " Map Manager: Map Generation In Progress" << std::endl;
  }
}

//returns true when finished
bool MapManager::GenerateMapUpdate()
{
  if(currentMethod == MazeGenerationMethod::RandomizedPrims)
  {
    return GenerateMazePrimsStep();
  }
  return false;
}


void MapManager::GenerateMazePrimsInit()
{

  //Initialize the prims map with unchecked values
  //Do prims
  //Convert from prims nodes to either walls or floors


  //row length
  primsInProgress.primsMap.reserve(mapInProgress.data[0].size());
  std::vector<PrimsNode> nodes;
  for (unsigned i = 0; i < mapInProgress.data[0].size(); ++i)
  {
    PrimsNode node;
    nodes.push_back(node);
  }

  nodes.reserve(mapInProgress.data.size());

  //num rows
  for (unsigned i = 0; i < mapInProgress.data.size(); ++i)
  {
    primsInProgress.primsMap.push_back(nodes);
  }



 //Start with a grid full of walls
  for (unsigned i = 0; i < primsInProgress.primsMap.size(); ++i)
  {
    for (unsigned j = 0; j < primsInProgress.primsMap[0].size(); ++j)
    {
      primsInProgress.primsMap[i][j].type = PrimsNodeType::Unchecked;
      primsInProgress.primsMap[i][j].x = i;
      primsInProgress.primsMap[i][j].y = j;

      mapInProgress.data[i][j].type = MapNodeTypes::Object;
      mapInProgress.data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
      mapInProgress.data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
      mapInProgress.data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });
      mapInProgress.data[i][j].SetLayer(GameObjectLayer::Obstacles);
    }
  }

  /*
   Set to Wall
      


    Set to Ground

   */
   //pick a cell, were going to make sure the path starts at 1,1


   //The walls list is going to be a pair of ints representing the coordinates of the wall in the map



  primsInProgress.primsMap[1][1].type = PrimsNodeType::Floor;

  //Pick a cell, mark it as part of the maze
  primsInProgress.mazeList.push_back({ 1,1 });

  //Add the walls of the cell to the wall list.
  AppendVector(primsInProgress.wallList, mapInProgress.GetAdjacentWalls({ 1,1 }));

  //adding maze list to the visited list
  AppendVector(primsInProgress.visited, primsInProgress.mazeList);

  for (auto& val : primsInProgress.visited)
  {
    primsInProgress.primsMap[val.first][val.second].visited = true;
  }
  for (auto& val : primsInProgress.wallList)
  {
    primsInProgress.primsMap[val.first][val.second].type = PrimsNodeType::Wall;
  }
  for (auto& val : primsInProgress.mazeList)
  {
    primsInProgress.primsMap[val.first][val.second].type = PrimsNodeType::Floor;
  }

}

bool MapManager::GenerateMazePrimsStep()
{

  //While there are walls in the list:
  if (!primsInProgress.wallList.empty())
  {

    //Pick a random wall from the list.
    int randValue = RandomValue(0, primsInProgress.wallList.size() - 1);
    auto& node = primsInProgress.wallList[randValue];
    auto adjacent = mapInProgress.GetAdjacentWalls(node);
    int adjacentVisited = 0;

    primsInProgress.primsMap[node.first][node.second].visited = true;

    //get the number of adjacent visited
    for (auto& value : adjacent)
    {
      //search from the beginning to end of visited nodes and if its visited
      //then increment the number visited

      //Definitely can rewrite this to loop through visited once and then check if one of the
      //adjacent values
      if (primsInProgress.primsMap[value.first][value.second].visited == true)
      {
        adjacentVisited++;
      }
    }

    //If only one of the two cells that the wall divides is visited, then
    if (adjacentVisited < 2)
    {
      /*
        Make the wall a passage and mark the unvisited cell as part of the maze.
        Add the neighboring walls of the cell to the wall list.
      */
      //Make the wall a passage
      primsInProgress.primsMap[node.first][node.second].type = PrimsNodeType::Floor;
      mapInProgress.data[node.first][node.second].type = MapNodeTypes::Ground;
      mapInProgress.data[node.first][node.second].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
      mapInProgress.data[node.first][node.second].GetComponent<Sprite>()->SetTexure("grass1");
      mapInProgress.data[node.first][node.second].SetLayer(GameObjectLayer::Floor);

      //mark the unvisited cell as part of the maze.
      primsInProgress.mazeList.push_back({ node.first,node.second });

      std::sort(primsInProgress.mazeList.begin(), primsInProgress.mazeList.end());
      primsInProgress.mazeList.erase(std::unique(primsInProgress.mazeList.begin(), 
        primsInProgress.mazeList.end()), primsInProgress.mazeList.end());
      //Add the neighboring walls of the cell to the wall list.
      auto values = mapInProgress.GetAdjacent(node);
      for (auto& val : values)
      {
        if (primsInProgress.primsMap[val.first][val.second].visited == false)
        {
          primsInProgress.primsMap[val.first][val.second].type = PrimsNodeType::Wall;
          primsInProgress.wallList.push_back(val);
          //primsMap[val.first][val.second].visited = true;
        }
      }


    }
    //Remove the wall from the list
    primsInProgress.wallList.erase(primsInProgress.wallList.begin() + randValue);

    //Make unique
    //std::sort(wallList.begin(), wallList.end());
    //wallList.erase(unique(wallList.begin(), wallList.end()), wallList.end());

  }
  /*
  for (unsigned i = 0; i < primsInProgress.primsMap.size(); ++i)
  {
    for (unsigned j = 0; j < primsInProgress.primsMap[0].size(); ++j)
    {
      mapInProgress.data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
      mapInProgress.data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });

      if (primsInProgress.primsMap[i][j].type == PrimsNodeType::Wall ||
        primsInProgress.primsMap[i][j].type == PrimsNodeType::Unchecked)
      {
        mapInProgress.data[i][j].type = MapNodeTypes::Object;
        mapInProgress.data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
        mapInProgress.data[i][j].SetLayer(GameObjectLayer::Obstacles);
      }
      else if (primsInProgress.primsMap[i][j].type == PrimsNodeType::Floor)
      {
        mapInProgress.data[i][j].type = MapNodeTypes::Ground;
        std::string grass = "grass";
        grass += std::to_string(RandomValue(0, 2));
        mapInProgress.data[i][j].GetComponent<Sprite>()->SetTexure(grass);
        mapInProgress.data[i][j].SetLayer(GameObjectLayer::Floor);
      }
    }
  }
  */
  return primsInProgress.wallList.empty();

}

