#include "pch.h"
#include "DungeonGen.h"



Room::Room(std::string filename)
{
  /*
    Room filetype
    type (0,1,2)
    height
    width
    north
    south
    east
    west
   */
}

bool Room::CollidesWith(Room& room)
{
  bool collision = false;
  //upper left glm::vec3
  if (pointInTriangle(UpperLeft(), room.UpperLeft(), room.UpperRight(), room.LowerRight())
    || pointInTriangle(UpperLeft(), room.UpperLeft(), room.UpperRight(), room.LowerLeft()))
  {
    collision = true;
  }
  //upper right glm::vec3
  else if (pointInTriangle(UpperRight(), room.UpperLeft(), room.UpperRight(), room.LowerRight())
    || pointInTriangle(UpperRight(), room.UpperLeft(), room.UpperRight(), room.LowerLeft()))
  {
    collision = true;
  }
  //lower left glm::vec3
  else if (pointInTriangle(LowerLeft(), room.UpperLeft(), room.UpperRight(), room.LowerRight())
    || pointInTriangle(LowerLeft(), room.UpperLeft(), room.UpperRight(), room.LowerLeft()))
  {
    collision = true;
  }
  //lower right glm::vec3
  else if (pointInTriangle(LowerRight(), room.UpperLeft(), room.UpperRight(), room.LowerRight())
    || pointInTriangle(LowerRight(), room.UpperLeft(), room.UpperRight(), room.LowerLeft()))
  {
    collision = true;
  }
  return collision;
};


DungeonGen::DungeonGen()
{

}

bool DungeonGen::GenerateRooms()
{
  Room startRoom(currID++);
  Room endRoom(currID++);

  startRoom.doors[rdSouth] = dsDisconnected;
  startRoom.doors[rdNorth] = dsDisconnected;
  
  endRoom.doors[rdSouth] = dsDisconnected;
  endRoom.doors[rdNorth] = dsDisconnected;

  map.push_back(startRoom);
  map.push_back(endRoom);

  Room randomRoom(currID++, 5, 5, rtRoom);
  randomRoom.doors[rdSouth] = dsDisconnected;
  randomRoom.doors[rdNorth] = dsDisconnected;

  if (startRoom.linkRoom(randomRoom, rdNorth))
  {
    if (randomRoom.linkRoom(endRoom, rdNorth))
      return true;
  }
  return false;
  //newRoom.x = RandomValue(-20, 20);
  //newRoom.y = RandomValue(-20, 20);

}

void DungeonGen::Generate(int seed)
{
  //data structures
  //list of rooms
  //graph of rooms

  //generate rooms
  //pick rooms to use (currently just moving the rooms instead of creating more)
    //using horizonal fighting generally so generate longer width than height 
    //pick main rooms above height/width ratio

  GenerateRooms();



}

void DungeonGen::PrintDungeon(char* filename)
{

}

