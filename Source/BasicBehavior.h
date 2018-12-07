//***************************************************************************
// Filename: BasicBehavior.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef BASIC_BEHAVIOR_H
#define BASIC_BEHAVIOR_H

#include "Component.h"

class BasicBehavior : public Component
{
public:

  BasicBehavior() : Component() { ID = nextComponentID++; };

private:
  static unsigned nextComponentID;
};

#endif
