//***************************************************************************
// Filename: Collider.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef COLLIDER_H
#define COLLIDER_H

#include "Component.h"

enum class ColliderType : unsigned
{
  Player,
  Wall,
  Floor,
  Object,
  
};

class Collider : public Component
{
public:

  Collider() : Component() { ID = nextComponentID++; };

  bool isColliding(const Collider& rhs);

  float radius;
private:
  static unsigned nextComponentID;

};

#endif
