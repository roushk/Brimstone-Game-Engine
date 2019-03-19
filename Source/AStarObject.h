#ifndef ASTAROBJECT_H
#define ASTAROBJECT_H

#include "GameObject.h"
#include "Pathfinding.h"

class AStarObject : public GameObject
{
public:
  AStarObject();
  void Update(float dt) override;

  PathRequest request;
  bool moving = false;  //is the current object following a path

  float movementSpeed = 200.0f;
private:
  bool followPath = true;

};


#endif
