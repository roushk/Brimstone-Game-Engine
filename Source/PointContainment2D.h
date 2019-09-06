#pragma once


/*
 Simple point withing axis aligned bounding box/radius
 */
namespace PointContainment2D
{

  //2D collision using AABB for simple point containment
  bool AABBPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point, float mouseOmega = 0.001f);
  //2D collision detection using SAT instead of AABB for more accurate detection
  //TODO this lmao
  bool SATPointWithinSquare(glm::vec2 center, glm::vec2 scale, glm::vec2 point, float mouseOmega = 0.001f);

  bool PointWithinRadius(glm::vec2 center, float radius, glm::vec2 point);
  
}