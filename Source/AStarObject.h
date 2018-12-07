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
private:
  bool computingPath = false;
  bool followPath = true;
  float movementSpeed = 200.0f;
};


#endif
