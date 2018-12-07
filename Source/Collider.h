//***************************************************************************
// Filename: Collider.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

class Collider : public Component
{
public:

  Collider() : Component() { ID = nextComponentID++; };

private:
  static unsigned nextComponentID;

};

#endif
