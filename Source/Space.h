//***************************************************************************
// Filename: Space.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef SPACE_H
#define SPACE_H
#include <vector>

class GameObject;
class Space
{
public:
  Space() { ID = nextUniqueComponentID++; };
  void AddObject(GameObject* obj);
  GameObject * GetObject(unsigned ID_) const;

  std::string name = "Space";
  int type;
  unsigned ID;


private:
  std::vector<GameObject*> objects;
  static unsigned nextUniqueComponentID;

  
};

#endif