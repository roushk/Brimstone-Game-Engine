//***************************************************************************
// Filename: SpaceManager.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SPACE_MANAGER_H
#define SPACE_MANAGER_H

#include "System.h"
#include "SpaceTypes.h"
#include <vector>
#include <map>

//Forward Defenitions
class Space;

class GameObject;

class SpaceManager : public System
{
public:
  SpaceManager() : System()
  {
    name = "Space Manager";
  };
  //set active space 
  //pass type same as systems and components??
  void Update(float dt) override;

  std::map<std::string,Space*> inactiveList;
  Space* activeList[steOutOfBounds];
private:
};

#endif