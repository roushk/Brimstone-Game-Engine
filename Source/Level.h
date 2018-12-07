//***************************************************************************
// Filename: Level.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef LEVEL_H
#define LEVEL_H
#include "SpaceTypes.h"
#include <string>
class GameObject;
class Space;
class Level
{
public:

  //void AddObject(GameObject* obj);
  Space * GetSpace(unsigned ID_) const;

  std::string name = "Level";
  int type;
private:
  Space * spaceList[steOutOfBounds];

};

#endif