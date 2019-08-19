//***************************************************************************
// Filename: Transform.cpp
// Author  : Coleman Jonas
// Description: Use this as a basic layout for all c++ files in the proj.
//***************************************************************************
#include "pch.h"

using namespace glm;
 

//allow to use only x,y for translation
glm::vec2 Transform::GetTranslation() const
{
  vec2 newTranslation;
  newTranslation.x = translation.x;
  newTranslation.y = translation.y;
  return translation;
}

glm::vec3 Transform::GetTranslation3D() const
{
  return translation;
}

glm::vec2 Transform::GetScale() const
{
  return scale;
}

float Transform::GetRotation() const
{
  return rotation;
}

Transform::Transform(const Transform& transform) : Component()
{
  name = "Transform";
  ID = nextComponentID++;

  translation = transform.translation;
  scale = transform.scale;
  rotation = transform.rotation;
  dirty = transform.dirty;
  matrix = transform.matrix;
  dirty = true;
}

Transform::Transform() : Component()
{
  name = "Transform"; 
  ID = nextComponentID++;
}

//allow to use only x,y for translation
void Transform::SetTranslation(glm::vec2 translation_)
{
  translation.x = translation_.x;
  translation.y = translation_.y;
  dirty = true;
}
void Transform::SetTranslation(float x_,float y_)
{
  translation.x = x_;
  translation.y = y_;
  dirty = true;
}

void Transform::SetTranslation(float x_, float y_, float z_)
{
  translation.x = x_;
  translation.y = y_;
  translation.z = z_;

  dirty = true;
}

void Transform::SetTranslation(glm::vec3 translation_)
{
  translation = translation_;
  dirty = true;
}

void Transform::SetScale(float scale_)
{
  scale = { scale_ , scale_ };
  dirty = true;
}
void Transform::SetScale(glm::vec2 scale_)
{
  scale = scale_;
  dirty = true;
}

void Transform::SetRotation(float rotation_)
{
  rotation = rotation_;
  dirty = true;
}

glm::mat4& Transform::GetMatrix()
{
  //scale has 1 in the z
  //rotated around the z = 1 vector
  if(dirty)
  {
    matrix = translate(translation) * 
      rotate(rotation, vec3{ 0,0,1 }) * 
      glm::scale(vec3(scale, 1.0f));
    dirty = false;
  }
  return matrix;

}
