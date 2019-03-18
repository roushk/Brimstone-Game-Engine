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
  void resolveCollision(GameObject* obj);

  float radius = 0.5f;
  static cType type = ctCollider;
private:
  static unsigned nextComponentID;

};



#endif
