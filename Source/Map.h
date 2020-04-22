#ifndef MAP_H
#define MAP_H

#include "Need.h"
#include <vector>
#include <glm.hpp>
#include "GameObject.h"



//TODO move this to a Vector Tools .h file
template <typename T>
void AppendVector(std::vector<T>& toAppendTo, const std::vector<T>& toAppendFrom)
{
  toAppendTo.insert(toAppendTo.end(), toAppendFrom.begin(), toAppendFrom.end());

}


struct GridPos
{
  int row;
  int col;

  bool operator==(const GridPos &rhs) const
  {
    return row == rhs.row && col == rhs.col;
  }

  bool operator!=(const GridPos &rhs) const
  {
    return row != rhs.row || col != rhs.col;
  }
};

enum class MapNodeTypes : unsigned
{
  Ground = 0,
  Object = 1,  //resource or building, something that stops movement
  Water,
  OutOfBounds
};

enum class MazeGenerationMethod
{
  RandomizedPrims,

};

//we are using the NodeCoord
typedef std::pair<int, int> NodeCoord;

class MapNode : public GameObject
{
public:
  MapNode() : GameObject() {};
  MapNode(const MapNode& rhs)
  {

    //GameObject::GameObject(rhs);
    *this = rhs;
    type = rhs.type;
  }
  MapNodeTypes type = MapNodeTypes::OutOfBounds;
  GameObject* modifier = nullptr;
  //could be game obj ptr
  //glm::uvec2 pos;
};

enum class PrimsNodeType
{
  Unchecked,
  Wall,
  Floor
};


class PrimsNode
{
  
  int x = 0;
  int y = 0;
  PrimsNodeType type = PrimsNodeType::Unchecked;

};



class Map
{
public:
  Map(unsigned xSize, unsigned ySize);
  Map(std::string& file_string);

  void SaveMap(Map &map);

  void GenerateMaze(MazeGenerationMethod method);

  void setOffset(glm::vec2 pos)
  {
    setOffset(pos.x, pos.y);
  }


  std::vector<NodeCoord> GetAdjacent(const NodeCoord& node)
  {
    std::vector<NodeCoord> walls;
    //check edges
    if(node.first > 0)
    {
      walls.push_back({ node.first - 1, node.second });
    }
    if (node.second > 0)
    {
      walls.push_back({ node.first, node.second - 1 });
    }
    if (node.first < width - 1)
    {
      walls.push_back({ node.first + 1, node.second });
    }
    if (node.second < height - 1)
    {
      walls.push_back({ node.first, node.second + 1 });
    }
    return walls;
  }


  std::vector<NodeCoord> GetAdjacentWalls(const NodeCoord& node)
  {
    std::vector<NodeCoord> walls;
    //check edges
    if (node.first > 0)
    {
      walls.push_back({ node.first - 1, node.second });
    }
    if (node.second > 0)
    {
      walls.push_back({ node.first, node.second - 1 });
    }
    if (node.first < width - 1)
    {
      walls.push_back({ node.first + 1, node.second });
    }
    if (node.second < height - 1)
    {
      walls.push_back({ node.first, node.second + 1 });
    }
    return walls;
  }


  
  //Create an Iterate Over Every Grid func that passes a func over every 
  //grid pos and gives the func the x,y, grid space of the current position
  void setOffset(float x, float y)
  {
    offset.x = x;
    offset.y = y;
    for (unsigned i = 0; i < data.size(); ++i)
    {
      for (unsigned j = 0; j < data[i].size(); ++j)
      {
        data[i][j].GetComponent<Transform>()->SetTranslation({ i + x, j + y});
      }
    }

  }

  GridPos get_grid_position(const glm::vec2 &worldPos) const;


  bool is_valid_grid_position(int row, int col) const
  {
    return row >= 0 && row < height && col >= 0 && col < width;
  }

  glm::vec3 get_world_position(int row, int col) const
  {
    return glm::vec3(row + offset.x, col + offset.y, 0);
  }

  MapNode& getNode(glm::uvec2 pos)
  {
    return data[pos.x][pos.y];
  };

  MapNode& getNode(float x, float y)
  {
    return data[x][y];
  }




  std::string name = "MapName";
  std::vector<std::vector<MapNode>> data;
  std::map<Need, std::vector<GameObject*>> objects;

  float height, width;
  glm::vec2 offset{0,0};
  //float mapSizeInWorld;

};

Map GenerateEmptyMap(unsigned xSize, unsigned ySize);

#endif
