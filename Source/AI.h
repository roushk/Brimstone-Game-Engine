//***************************************************************************
// Filename: AI.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef AI_H
#define AI_H

#include "Component.h"

class AI : public Component
{
public:

  AI() : Component() { ID = nextComponentID++; };

private:
  static unsigned nextComponentID;
};

#endif
