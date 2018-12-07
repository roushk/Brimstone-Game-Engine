//***************************************************************************
// Filename: Physics.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef PHYSICS_H
#define PHYSICS_H

#include "Component.h"

class Physics : public Component
{
public:

  Physics() : Component() { ID = nextComponentID++; };
  ~Physics();
  void Update(float dt) override;
  void SetAcceleration(const glm::vec2& accel);
  void SetRotationalAcceleration(float rotationalAccel);


  glm::vec2 acceleration{0, 0};
  glm::vec2 velocity{0, 0};
  float drag = 0.99f;
  float rotationAcceleration = 0.0f;
  float rotationVelocity = 0.0f;
  float rotationDrag = 0.99f;
private:
  static unsigned nextComponentID;

  
};

#endif
