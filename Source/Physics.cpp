#include "pch.h"


Physics::~Physics()
{

}

void Physics::SetAcceleration(const glm::vec2& accel)
{
  acceleration = accel;
}

void Physics::SetRotationalAcceleration(float rotationalAccel)
{
  rotationAcceleration = rotationalAccel;
}


void Physics::Update(float dt)
{
  auto position = parent->GetComponent<Transform>()->GetTranslation();
  auto rotation = parent->GetComponent<Transform>()->GetRotation();
  
  //Update velocity
  velocity = (dt * acceleration) + velocity;
  rotationVelocity = (dt * rotationAcceleration) + rotationVelocity;
  //Update position
  position = (((0.5f) * (dt * dt) * (acceleration)) + (dt * velocity) + position);
  rotation = (((0.5f) * (dt * dt) * (rotationAcceleration)) + (dt * rotationVelocity) + rotation);

  parent->GetComponent<Transform>()->SetTranslation(position);
  parent->GetComponent<Transform>()->SetRotation(rotation);

  //drag
  velocity = drag * velocity;
  rotationVelocity = rotationDrag * rotationVelocity;

}

