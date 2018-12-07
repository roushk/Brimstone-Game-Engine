#include "pch.h"
#include "glm/gtx/norm.hpp"

AStarObject::AStarObject() : GameObject()
{
  moveable = true;
}

void AStarObject::Update(float dt)
{
  if (!computingPath)
  {
    if (request.path.size() > 0 && followPath)
    {
      color = { 0,0,0,1 };

      const auto &currPos = GetComponent<Transform>()->GetTranslation();
      auto delta = (request.path.front() - currPos);

      if (glm::length2(delta) <= 0.1f)
      {
        request.path.pop_front();
      }
      else
      {
        glm::normalize(delta);
        const auto movement = delta * (movementSpeed * dt / static_cast<float>(request.map->width));
       
        GetComponent<Transform>()->SetTranslation(currPos + movement);

        //const float yaw = std::atan2(delta.x, delta.z);
        //set_yaw(yaw);
      }
    }
  }
  else
  {
    request.newRequest = false;

    //process_request();
  }
}