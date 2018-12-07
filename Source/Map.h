#ifndef MAP_H
#define MAP_H

#include <vector>
#include <glm.hpp>
#include "GameObject.h"

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

enum MapNodeTypes
{
  mntGround,
  mntObject,  //resource or building, something that stops movement
  mntWater,
  mntOutOfBounds
};

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
  unsigned type = mntOutOfBounds;
  GameObject* modifier = nullptr;
  //could be game obj ptr
  //glm::uvec2 pos;
};

class Map
{
public:
  Map(unsigned xSize, unsigned ySize);
  Map(std::string& file_string);

  void setOffset(glm::vec2 pos)
  {
    setOffset(pos.x, pos.y);
  }
  
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

  void SaveMap(Map &map);

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
  float height, width;
  glm::vec2 offset{0,0};
  //float mapSizeInWorld;

};

Map GenerateEmptyMap(unsigned xSize, unsigned ySize);
#endif
