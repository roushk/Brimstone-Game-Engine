#ifndef DUNGEON_GEN_H
#define DUNGEON_GEN_H

#include <vector>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "PointContainment.h"
#include "HalfPlane.h"
#include "Random.h"


enum DoorSetting
{
  dsDisconnected, //open to be connected to other room
  dsConnected,    //connected to other room
  dsNoDoor,       //no door at all
  dsOutOfBounds
};

enum RoomType
{
  rtRoom,
  rtStart,
  rtEnd,
  rtOufOfBounds
};

enum RoomDirections
{
  rdNorth,
  rdSouth,
  rdEast,
  rdWest,
  rdOutOfBounds
};

enum OrientationOfRoom
{
  oorNorth, //usually facing north
  oorEast,
  oorSouth,
  oorWest,
  oorOutOfBounds
};

class Tile : public glm::vec3 
{
public:
  char tile;
  void Set(char set)
  {tile = set;};
};
//a node is a door way
/*
class Node
{
public:
  glm::vec3 a;
  //glm::vec3 b;
};
*/

class Room : public glm::vec3
{
public:
  Room(int ID = 0, int newHeight = 5, int newWidth = 5, unsigned type = rtRoom)
  : ID(ID),height(newHeight), width(newWidth),roomType(type)
  {
    for(unsigned i = 0; i < rdOutOfBounds; ++i)
    {
      doors[i] = dsNoDoor;
    }
  };
  Room(std::string filename);
  int ID;
  int height;
  int width;
  unsigned orientation = 0;

  //bool if doorway there
  unsigned doors[rdOutOfBounds];

  //ptr to rooms like linked list of sorts
  Room* rooms[rdOutOfBounds];

  static unsigned oppositeSide(unsigned side)
  {
    return((side + 2) % 4);
  }
  bool linkRoom(Room& other, unsigned side)
  {
    //if doors[side] == disconnected
    if (doors[side] == dsDisconnected &&
      other.doors[oppositeSide(side)] == dsDisconnected)
    {
      rooms[side] = &other;
      other.rooms[oppositeSide(side)] = this;
      doors[side] = dsConnected;
      other.doors[oppositeSide(side)] = dsConnected;
      return true;
    }
    return false;
  }

  unsigned roomType;

  glm::vec3 UpperLeft()  {return glm::vec3(y + (height / 2.0f), x + (width / 2.0f),0);};
  glm::vec3 UpperRight() {return glm::vec3(y + (height / 2.0f), x - (width / 2.0f),0);};
  glm::vec3 LowerLeft()  {return glm::vec3(y - (height / 2.0f), x + (width / 2.0f),0);};
  glm::vec3 LowerRight() {return glm::vec3(y - (height / 2.0f), x - (width / 2.0f),0);};

  bool CollidesWith(Room& room);


  //std::vector<Tile> items;
};


class DungeonGen
{
public:
  DungeonGen();

  /*
  Tile* Above(Tile* tile){
    if(tile->y + 1 >= height)
      return NULL;
    return &map[tile->y + 1][tile->x];};
  Tile* Below(Tile* tile){
    if(tile->y - 1 < 0)
      return NULL;
    return &map[tile->y - 1][tile->x];};
  Tile* Left(Tile* tile){
    if(tile->x - 1 < 0)
      return NULL;
    return &map[tile->y][tile->x - 1];};
  Tile* Right(Tile* tile){
    if(tile->x + 1 >= width)
      return NULL;
    return &map[tile->y][tile->x + 1];};
  */
  
  bool GenerateRooms();
  

  void Generate(int seed);
  
  void AddRoom(Room room)
  {
    //add items
    //center + height / 2
  }

  void PrintDungeon(char* filename);

private:
  std::vector<Room> map;

  int currID = 0;
};

#endif