//***************************************************************************
// Filename: Transform.h
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>


class Transform : public Component
{
public:
  friend GameObject;
  Transform();
  Transform(const Transform& transform);
  ~Transform() {};

  void SetTranslation(glm::vec2 translation_);
  void SetTranslation(glm::vec3 translation_);
  void SetScale(glm::vec2 scale_);
  void SetScale(float scale_);
  //rotation is in radians
  void SetRotation(float rotation_);

  glm::vec2 GetTranslation() const;
  glm::vec3 GetTranslation3D() const;
  glm::vec2 GetScale() const;
  float GetRotation() const;
  glm::mat4& GetMatrix();

  bool IsSameClassType(cType& rhs) const override
  { return rhs == type; };
  static cType type = ctTransform;

private:
  static unsigned nextComponentID;

  glm::vec3 translation{0, 0, 0};
  glm::vec2 scale{ 1.0f,1.0f };
  float rotation = 0;
  bool dirty = true;
  glm::mat4 matrix;
};


#endif