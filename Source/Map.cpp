#include "pch.h"



Map::Map(std::string& file_string) 
{
  std::string fileStr = "Maps/";
  fileStr += file_string;
  std::string file = GetFile(fileStr);

  for(auto& ch: file)
  {
    if (ch == '\n')
      ch = ' ';
  }

  auto it = file.find_first_of(' ');
  name = file.substr(0, it);
  file.erase(0, it + 1);

  std::string heightStr;
  it = file.find_first_of(' ');
  heightStr = file.substr(0, it);
  height = std::atoi(heightStr.c_str());
  file.erase(0, it + 1);

  std::string widthStr;
  it = file.find_first_of(' ');
  widthStr = file.substr(0, it);
  width = std::atoi(widthStr.c_str());
  file.erase(0, it + 1);
  size_t ch = file.find_first_of(' ');


  while (ch != std::string::npos)
  {
    file.erase(ch, 1);
    ch = file.find_first_of(' ');
  }

  //std::string data = file;
  data.reserve(width);
  
  for (unsigned i = 0; i < width; ++i)
  {
    std::vector<MapNode> nodes;
    nodes.reserve(height);
    for (unsigned j = 0; j < height; ++j)
    {
      MapNode node;
      node.type = static_cast<MapNodeTypes>(file.at(j * height + i ) - 48);
      nodes.push_back(node);
      
    }
    std::reverse(nodes.begin(), nodes.end());
    data.push_back(nodes);
  }

  //std::reverse(data.begin(), data.end());

  for (unsigned i = 0; i < data.size(); ++i)
  {
    for (int j = 0; j < data[i].size(); ++j)
    {
      data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
      data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });
      data[i][j].SetLayer(GameObjectLayer::Floor);
      if(data[i][j].type == MapNodeTypes::Ground)
      {
        std::string grass = "grass";
        grass += std::to_string(RandomValue(0, 2));
        data[i][j].GetComponent<Sprite>()->SetTexure(grass);
        
      }
      else if (data[i][j].type == MapNodeTypes::Object)
      {
        data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
      }
    }
  }
}

//??? I assume its for serialization but no idea why it takes a map when its a method
void Map::SaveMap(Map &map)
{

}



//Generates of size X by Y and reserves the data for the map
Map::Map(unsigned xSize, unsigned ySize) : height(ySize), width(xSize)
{

  data.reserve(ySize);
  std::vector<MapNode> nodes;
  for (unsigned i = 0; i < xSize; ++i)
  {
    MapNode node;
    nodes.push_back(node);
  }

  nodes.reserve(xSize);

  for (unsigned i = 0; i < ySize; ++i)
  {
    data.push_back(nodes);
  }

}


//Gets the grid position of a world coordinate
GridPos Map::get_grid_position(const glm::vec2& worldPos) const
{
  const int row = static_cast<int>((worldPos.x + 0.5f - offset.x));
  const int col = static_cast<int>((worldPos.y + 0.5f - offset.y));

  //const int col = static_cast<int>((worldPos.z) / mapSizeInWorld * height);

  return GridPos{ row, col };
}


//Generates an empty map and returns it
Map GenerateEmptyMap(unsigned xSize, unsigned ySize)
{
  Map map(xSize, ySize);
  map.height = ySize;
  map.width = xSize;

  for (unsigned i = 0; i < map.data.size(); ++i)
  {
    for (unsigned j = 0; j < map.data[i].size(); ++j)
    {
      map.data[i][j].type = MapNodeTypes::Ground;
      map.data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f});
      std::string grass = "grass";
      grass += std::to_string(RandomValue(0, 2));
      map.data[i][j].GetComponent<Sprite>()->SetTexure(grass);
      map.data[i][j].GetComponent<Transform>()->SetTranslation({i, j});
      map.data[i][j].SetLayer(GameObjectLayer::Floor);
    }
  }
  return map;
}



//Generates a maze overwriting a map using a method
void Map::GenerateMaze(MazeGenerationMethod method)
{

  //Initialize the prims map with unchecked values
  //Do prims
  //Convert from prims nodes to either walls or floors

  std::vector<std::vector<PrimsNode>> primsMap;
  
  primsMap.reserve(data.size());
  std::vector<PrimsNode> nodes;
  for (unsigned i = 0; i < data.size(); ++i)
  {
    PrimsNode node;
    nodes.push_back(node);
  }

  nodes.reserve(data.size());

  for (unsigned i = 0; i < data[0].size(); ++i)
  {
    primsMap.push_back(nodes);
  }
  
  
  /*
    Start with a grid full of walls.
    Pick a cell, mark it as part of the maze. Add the walls of the cell to the wall list.
    While there are walls in the list:
      Pick a random wall from the list. If only one of the two cells that the wall divides is visited, then:
        Make the wall a passage and mark the unvisited cell as part of the maze.
        Add the neighboring walls of the cell to the wall list.
      Remove the wall from the list.
   */
  if(method == MazeGenerationMethod::RandomizedPrims)
  {
    /*
    Start with a grid full of walls.
    Pick a cell, mark it as part of the maze. Add the walls of the cell to the wall list.
    While there are walls in the list:
      Pick a random wall from the list. If only one of the two cells that the wall divides is visited, then:
        Make the wall a passage and mark the unvisited cell as part of the maze.
        Add the neighboring walls of the cell to the wall list.
      Remove the wall from the list.
   */

    //Start with a grid full of walls
    for (unsigned i = 0; i < primsMap.size(); ++i)
    {
      for (unsigned j = 0; j < primsMap[0].size(); ++j)
      {
        primsMap[i][j].type = PrimsNodeType::Unchecked;
        primsMap[i][j].x = i;
        primsMap[i][j].y = j;

      }
    }

    /*
     Set to Wall
        data[i][j].type = MapNodeTypes::Object;
        data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
        data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
        data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });
        data[i][j].SetLayer(GameObjectLayer::Obstacles);


      Set to Ground
        data[i][j].type = MapNodeTypes::Ground;
        data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
        data[i][j].GetComponent<Sprite>()->SetTexure("grass1");
        data[i][j].SetLayer(GameObjectLayer::Floor);
     */
    //pick a cell, were going to make sure the path starts at 1,1


    //The walls list is going to be a pair of ints representing the coordinates of the wall in the map
    std::vector<NodeCoord> wallList;
    std::vector<NodeCoord> mazeList;
    std::vector<NodeCoord> visited;


    primsMap[1][1].type = PrimsNodeType::Floor;

    //Pick a cell, mark it as part of the maze
    mazeList.push_back({ 1,1 });

    //Add the walls of the cell to the wall list.
    AppendVector(wallList, GetAdjacentWalls({ 1,1 }));

    //adding maze list to the visited list
    AppendVector(visited, mazeList);

    for(auto& val: visited)
    {
      primsMap[val.first][val.second].visited = true;
    }
    for (auto& val : wallList)
    {
      primsMap[val.first][val.second].type = PrimsNodeType::Wall;
    }
    for (auto& val : mazeList)
    {
      primsMap[val.first][val.second].type = PrimsNodeType::Floor;
    }

    //While there are walls in the list:
    while(!wallList.empty())
    {
      
      //Pick a random wall from the list.
      int randValue = RandomValue(0, wallList.size() - 1);
      auto& node = wallList[randValue];
      auto adjacent = GetAdjacentWalls(node);
      int adjacentVisited = 0;

      primsMap[node.first][node.second].visited = true;

      //get the number of adjacent visited
      for(auto& value: adjacent)
      {
        //search from the beginning to end of visited nodes and if its visited
        //then increment the number visited

        //Definitely can rewrite this to loop through visited once and then check if one of the
        //adjacent values
        if (primsMap[value.first][value.second].visited == true)
        {
          adjacentVisited++;
        }
      }

      //If only one of the two cells that the wall divides is visited, then
      if(adjacentVisited < 2)
      {
        /*
          Make the wall a passage and mark the unvisited cell as part of the maze.
          Add the neighboring walls of the cell to the wall list.
        */
        //Make the wall a passage
        primsMap[node.first][node.second].type = PrimsNodeType::Floor;

        //mark the unvisited cell as part of the maze.
        mazeList.push_back({ node.first,node.second });

        std::sort(mazeList.begin(), mazeList.end());
        mazeList.erase(unique(mazeList.begin(), mazeList.end()), mazeList.end());
        //Add the neighboring walls of the cell to the wall list.
        auto values = GetAdjacent(node);
        for(auto& val: values)
        {
          if(primsMap[val.first][val.second].visited == false)
          {
            primsMap[val.first][val.second].type = PrimsNodeType::Wall;
            wallList.push_back(val);
            //primsMap[val.first][val.second].visited = true;
          }
        }


      }
      //Remove the wall from the list
      wallList.erase(wallList.begin() + randValue);

      //Make unique
      //std::sort(wallList.begin(), wallList.end());
      //wallList.erase(unique(wallList.begin(), wallList.end()), wallList.end());
      
    }
    //set walls to wall
    /*

    for (unsigned i = 0; i < data.size(); ++i)
    {
      for (unsigned j = 0; j < data[i].size(); ++j)
      {
        if (i == 0 || j == 0 || i == data.size() - 1 || j == data[i].size() - 1)
        {
          //Pick a cell 
          data[i][j].type = MapNodeTypes::Object;
          data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
          data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
          data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });
          data[i][j].SetLayer(GameObjectLayer::Obstacles);
        }
      }
    }
    */
    for (unsigned i = 0; i < primsMap.size(); ++i)
    {
      for (unsigned j = 0; j < primsMap[0].size(); ++j)
      {
        data[i][j].GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
        data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });

        if(primsMap[i][j].type == PrimsNodeType::Wall || 
          primsMap[i][j].type == PrimsNodeType::Unchecked)
        {
          data[i][j].type = MapNodeTypes::Object;
          data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
          data[i][j].SetLayer(GameObjectLayer::Obstacles); 
        }
        else if (primsMap[i][j].type == PrimsNodeType::Floor)
        {
          data[i][j].type = MapNodeTypes::Ground;
          std::string grass = "grass";
          grass += std::to_string(RandomValue(0, 2));
          data[i][j].GetComponent<Sprite>()->SetTexure(grass);
          data[i][j].SetLayer(GameObjectLayer::Floor);
        }
      }
    }
  }
}



