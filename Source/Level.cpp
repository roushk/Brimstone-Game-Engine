//***************************************************************************
// Filename: Level.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"


Space* Level::GetSpace(unsigned ID_) const
{
  for(auto & space : spaceList)
  {
    if (space->ID == ID_)
      return space;
  }
  return nullptr;
}
