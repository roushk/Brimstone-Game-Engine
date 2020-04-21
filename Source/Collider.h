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

  Collider(float mass_) : Component()
  {
    if (mass == 0)
      invMass = 0;
    else
      invMass = 1 / mass;
    ID = nextComponentID++;
  };
  Collider() : Component()
  {
    mass = 0; 
    invMass = 0;
    ID = nextComponentID++;
  };

  bool isColliding(const Collider& rhs);
  void resolveCollision(GameObject* obj);

  float mass = 0;
  float invMass = 0;
  float radius = 0.5f;
  float restitution = 0;
  static cType type = ctCollider;
private:
  static unsigned nextComponentID;

};



#endif
