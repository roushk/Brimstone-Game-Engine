#pragma once
//TODO how does unity do their Color system??? like Color.
//using only a singe type
static class Color : glm::vec4
{
public:
  glm::vec4 Red = glm::vec4(1, 0, 0, 1);
  glm::vec4 Green = glm::vec4(0, 1, 0, 1);
  glm::vec4 Blue = glm::vec4(0, 0, 1, 1);

  glm::vec4 Yellow = glm::vec4(1, 1, 0, 1);
  glm::vec4 Purple = glm::vec4(1, 0, 1, 1);
  glm::vec4 green_blue = glm::vec4(0, 1, 1, 1);

  //glm::vec4 Red = glm::vec4(1, 0, 0, 1);
  //glm::vec4 Red = glm::vec4(1, 0, 0, 1);

} Color;

