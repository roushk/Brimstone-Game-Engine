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
      node.type = file.at(j * height + i ) - 48;
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
      data[i][j].GetComponent<Transform>()->SetScale({ 1.0f, 1.0f });
      data[i][j].GetComponent<Transform>()->SetTranslation({ i, j });
      data[i][j].SetLayer(GameObjectLayer::golFloor);
      if(data[i][j].type == mntGround)
      {
        std::string grass = "grass";
        grass += std::to_string(PRNG.randomRange(0, 2));
        data[i][j].GetComponent<Sprite>()->SetTexure(grass);
        
      }
      else if (data[i][j].type == mntObject)
      {
        data[i][j].GetComponent<Sprite>()->SetTexure("Wall1");
      }
    }
  }
}

void Map::SaveMap(Map &map)
{

}


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

GridPos Map::get_grid_position(const glm::vec2& worldPos) const
{
  const int row = static_cast<int>((worldPos.x + 0.5f - offset.x));
  const int col = static_cast<int>((worldPos.y + 0.5f - offset.y));

  //const int col = static_cast<int>((worldPos.z) / mapSizeInWorld * height);

  return GridPos{ row, col };
}

Map GenerateEmptyMap(unsigned xSize, unsigned ySize)
{
  Map map(xSize, ySize);
  map.height = ySize;
  map.width = xSize;

  for (unsigned i = 0; i < map.data.size(); ++i)
  {
    for (unsigned j = 0; j < map.data[i].size(); ++j)
    {
      map.data[i][j].type = mntGround;
      map.data[i][j].GetComponent<Transform>()->SetScale({1.0f, 1.0f});
      std::string grass = "grass";
      grass += std::to_string(PRNG.randomRange(0, 2));
      map.data[i][j].GetComponent<Sprite>()->SetTexure(grass);
      map.data[i][j].GetComponent<Transform>()->SetTranslation({i, j});
      map.data[i][j].SetLayer(GameObjectLayer::golFloor);
    }
  }
  return map;
}


