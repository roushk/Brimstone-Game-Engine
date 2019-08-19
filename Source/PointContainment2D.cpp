#include "pch.h"

bool PointContainment2D::AABBPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point, float mouseOmega)
{
  return  (point.x + mouseOmega) >= (center.x - scale.x) &&
          (point.x - mouseOmega) <= (center.x + scale.x) &&
          (point.y + mouseOmega) >= (center.y - scale.y) &&
          (point.y - mouseOmega) <= (center.y + scale.y);

}


bool PointContainment2D::SATPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point, float mouseOmega)
{
  return false;
}


bool PointContainment2D::PointWithinRadius(glm::vec2 center, float radius, glm::vec2 point)
{
  //if the distance squared from the center to the point is less than the radius squared
  //than the point is within the radius 
  return(glm::distance2(center, point) < radius * radius);
}


