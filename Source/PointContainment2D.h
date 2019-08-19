#pragma once
#include <gtx/norm.inl>


/*
 Simple point withing axis aligned bounding box/radius
 */
namespace PointContainment2D
{

  //2D collision using AABB for simple point containment
  inline bool AABBPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point,  float mouseOmega = 0.001f)
  {
    return (point.x + mouseOmega >= -(center.x - scale.x) &&
            point.x + mouseOmega <=  (center.x + scale.x) &&
            point.y - mouseOmega >= -(center.x - scale.x) &&
            point.y + mouseOmega <=  (center.y + scale.y));

  }

  //2D collision detection using SAT instead of AABB for more accurate detection
  //TODO this lmao
  inline bool SATPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point, float mouseOmega = 0.001f)
  {
    return false;
  }

  inline bool PointWithinRadius(glm::vec2 center, float radius, glm::vec2 point)
  {
    //if the distance squared from the center to the point is less than the radius squared
    //than the point is within the radius 
    return(glm::distance2(center, point) < radius * radius);
  }
  
}