//***************************************************************************
// Filename: Space.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"

void Space::AddObject(GameObject* obj)
{
  objects.push_back(obj);
}


GameObject* Space::GetObject(unsigned ID_) const
{
  for(auto & obj : objects)
  {
    if (obj->ID == ID_)
      return obj;
  }
  return nullptr;
}
